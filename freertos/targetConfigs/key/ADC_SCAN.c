#include "ADC_SCAN.h"
#include <string.h>

/* 伪代码/注释占位：引入MSPM0库头文件 */
#include "ti_msp_dl_config.h" 
#include "targetConfigs/oled/OLED_Task.h"
#include "targetConfigs/mainTask/main_task.h"

/* 队列句柄定义 */
QueueHandle_t xKeyQueue = NULL;

/**
 * @brief  根据 12位 ADC值（0~4095）判断按键ID
 * @note   硬件设计参考（分压原理）：
 * - 未按下：ADC引脚接上拉电阻到 VCC(3.3V)，ADC理论值 = 4095
 * - 按键1：按下后分压得到约 0V，ADC理论值 = 0                      中
 * - 按键2：按下后分压得到约 1.65V，ADC理论值 = 2048                左
 * - 按键3：按下后分压得到约 2.2V，ADC理论值 = 2730                 右
 * - 按键4：按下后分压得到约 2.475V，ADC理论值 = 3072               上
 * - 按键5：按下后分压得到约 2.64V，ADC理论值 = 3277                下

 * @param  adc_val: 12位ADC采样值
 * @return key_id_t: 识别到的按键ID
 */
key_id_t get_key_from_adc(uint16_t adc_val) {
    // 容错带宽度定为 ±150 LSB
    const uint16_t range = 100; 
    
    if ((adc_val >= (0 - range))  && (adc_val <= (0 + range)))  return KEY_1;
    if ((adc_val >= (2048 - range)) && (adc_val <= (2048 + range))) return KEY_2;
    if ((adc_val >= (2730 - range)) && (adc_val <= (2730 + range))) return KEY_3;
    if ((adc_val >= (3072 - range)) && (adc_val <= (3072 + range))) return KEY_4;
    if ((adc_val >= (3277 - range)) && (adc_val <= (3277 + range))) return KEY_5;
    
    // 如果没有匹配到上述区间，且电压接近 3.3V (未按下状态)，或者落在盲区，均返回 KEY_NONE
    return KEY_NONE;
}

/**
 * @brief  ADC 梯级按键扫描任务 (周期 20ms)
 */
void vTaskKeyScan(void *pvParameters) {
    TickType_t xLastWakeTime;
    const TickType_t xBlockTime = pdMS_TO_TICKS(20); // 20ms 周期
    
    // 内部状态机变量
    key_state_t current_state = KEY_STATE_IDLE;
    key_id_t sample_key = KEY_NONE;
    key_id_t verified_key = KEY_NONE;
    uint8_t display_div = 0;
    
    // 初始化最后唤醒时间
    xLastWakeTime = xTaskGetTickCount();
    
    while (1) {

        
        // 使用 vTaskDelayUntil 保证精确的 20ms 扫描周期
        vTaskDelayUntil(&xLastWakeTime, xBlockTime);
        
        uint16_t adc_raw_value = 4095; // 默认为未按下状态
        
        /* ============ MSPM0G3507 ADC 软件单次触发采样 ============ */
#ifndef ADC12_0_INST
#define ADC12_0_INST ADC0
#endif

        // 强行用代码配置 ADC，彻底排除 SysConfig 隐藏坑
        static uint8_t adc_configured = 0;
        if (!adc_configured) {
            adc_configured = 1;
            DL_ADC12_disableConversions(ADC12_0_INST);
            DL_ADC12_initSingleSample(ADC12_0_INST,
                DL_ADC12_REPEAT_MODE_ENABLED, 
                DL_ADC12_SAMPLING_SOURCE_AUTO,
                DL_ADC12_TRIG_SRC_SOFTWARE,
                DL_ADC12_SAMP_CONV_RES_12_BIT,
                DL_ADC12_SAMP_CONV_DATA_FORMAT_UNSIGNED);
            DL_ADC12_setSampleTime0(ADC12_0_INST, 32000);
            DL_ADC12_enableConversions(ADC12_0_INST);
        }

        DL_ADC12_startConversion(ADC12_0_INST);
        // 加入一个防卡死机制，防止 while 陷入死循环
        uint32_t timeout = 100000;
        while ((DL_ADC12_getStatus(ADC12_0_INST) & DL_ADC12_STATUS_CONVERSION_ACTIVE) && timeout-- > 0);
        
        adc_raw_value = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);
        /* ============================================================= */

        // 将读取到的 ADC 电压转换为按键 ID
        sample_key = get_key_from_adc(adc_raw_value);
        
        // 每 100ms 刷新一次
        if (++display_div >= 5) {
            display_div = 0;
            
            // 右下角闪烁点，证明系统没死机
            static uint8_t dot_state = 0;
            dot_state = !dot_state;
            Oled_Queue_ShowChar(4, 16, dot_state ? '.' : ' ');
            
            //Oled_Queue_ShowString(2, 1, "ADC Val: ");
            //Oled_Queue_ShowNum(2, 10, adc_raw_value, 4);
            Oled_Queue_ShowString(3, 1, "Key Idx: ");
            Oled_Queue_ShowNum(3, 10, sample_key, 2);
        }
        
        // 软件消抖与触发状态机
        switch (current_state) {
            case KEY_STATE_IDLE:
                if (sample_key != KEY_NONE) {
                    // 检测到有键按下，暂存该键值，进入消抖阶段
                    verified_key = sample_key;
                    current_state = KEY_STATE_DEBOUNCE;
                }
                break;
                
            case KEY_STATE_DEBOUNCE:
                // 经历 20ms 延时后再次进行检测
                if (sample_key == verified_key) {
                    // 两次键值一致，确认为有效短按，立即向队列发送键值
                    uint8_t key_msg = (uint8_t)verified_key;
                    
                    // 严格按照需求：阻塞时间为 0，发送后无论成功与否立即返回
                    xQueueSend(xKeyQueue, &key_msg, 0);
                    
                    // 进入等待松手状态，防止长按时重复发送
                    current_state = KEY_STATE_WAIT_RELEASE;
                } else {
                    // 两次键值不一致，判定为噪声抖动，回到空闲状态
                    current_state = KEY_STATE_IDLE;
                }
                break;
                
            case KEY_STATE_WAIT_RELEASE:
                // 在按键未完全松开（不等于 KEY_NONE）期间，保持当前状态
                // 注意：对于摇杆来说，如果一直推着不放，就会一直卡在这里！
                if (sample_key == KEY_NONE) {
                    // 完全松手，回到空闲状态，允许下一次按键触发
                    current_state = KEY_STATE_IDLE;
                }
                break;
                
            default:
                current_state = KEY_STATE_IDLE;
                break;
        }
    }
}

/**
 * @brief  专门的按键后效处理任务（与OLED显示联动）
 */
void vTaskKeyLogic(void *pvParameters) {
    uint8_t received_key_id = KEY_NONE;
    
    // 初始化显示屏幕框架
    
    while (1) {
        // 无限期阻塞等待按键有效按下消息（消抖并松手后才触发下一轮）
        if (xQueueReceive(xKeyQueue, &received_key_id, portMAX_DELAY) == pdTRUE) {
            // 当确实检测到有效按键时，在第四行打印触发的动作
            Oled_Queue_ShowString(4, 1, "Trigger: ");
            Oled_Queue_ShowNum(4, 10, received_key_id, 2);
            
            // 将按键值也传给 vTaskMainBrain (senderID 填 1 表示按键)
            Main_SendKeyEvent(received_key_id, 1);
        }
    }
}

