#include "as201.h"
#include "ti_msp_dl_config.h"
#include "targetConfigs/oled/OLED_Task.h"

QueueHandle_t xAs201RxQueue = NULL;

typedef enum {
    STATE_HEADER_0,
    STATE_HEADER_1,
    STATE_HEADER_2,
    STATE_HEADER_3,
    STATE_ADDR,
    STATE_CMD,
    STATE_OFFSET_LSB,
    STATE_OFFSET_MSB,
    STATE_LEN_LSB,
    STATE_LEN_MSB,
    STATE_DATA,
    STATE_CHECKSUM
} parse_state_t;

void As201_FreeRTOS_Init(void) {
    // 1. 创建串口接收队列 (深度 256)
    xAs201RxQueue = xQueueCreate(256, sizeof(uint8_t));
    configASSERT(xAs201RxQueue != NULL);

    // 2. 创建解析任务
    xTaskCreate(vTaskAs201Parse, 
                "As201ParseTask", 
                512, 
                NULL, 
                tskIDLE_PRIORITY + 3, // 高优先级确保不丢包
                NULL);
    
    // 3. 使能 MCU UART0 中断
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
}

// UART0 中断服务函数
void UART0_IRQHandler(void) {
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_RX:
            {
                uint8_t data = DL_UART_Main_receiveData(UART_0_INST);
                BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                xQueueSendFromISR(xAs201RxQueue, &data, &xHigherPriorityTaskWoken);
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
            break;
        default:
            break;
    }
}

// 处理雷达测距数据包
static void process_packet(uint8_t cmd, uint8_t *buf, uint16_t len) {
    if (cmd == 0x02 && len >= 184) {
        LidarPoint_t *points = (LidarPoint_t *)buf;
        
        int16_t distance = points[0].distance;
        uint8_t confidence = points[0].confidence;
        
        static TickType_t last_update = 0;
        TickType_t now = xTaskGetTickCount();
        if (now - last_update >= pdMS_TO_TICKS(100)) {
            last_update = now;
            // 置信度有效才显示在第一行
            if (confidence > 30 && distance > 0) {
                Oled_Queue_ShowString(1, 1, "Dist: ");
                Oled_Queue_ShowNum(1, 7, (uint32_t)distance, 4);
                Oled_Queue_ShowString(1, 11, " mm  ");
            } else {
                Oled_Queue_ShowString(1, 1, "Dist: ---- mm");
            }
        }
    }
}

// 解析状态机任务
void vTaskAs201Parse(void *pvParameters) {
    uint8_t byte;
    parse_state_t state = STATE_HEADER_0;
    
    static uint8_t dev_addr = 0;
    static uint8_t cmd_code = 0;
    static uint16_t block_offset = 0;
    static uint16_t data_len = 0;
    static uint16_t data_idx = 0;
    static uint8_t data_buf[256];
    static uint8_t checksum = 0;
    static uint8_t calculated_sum = 0;
    
    // 初始化时，第一行显示等待数据
    Oled_Queue_ShowString(1, 1, "Dist: Wait...");
    
    while (1) {
        if (xQueueReceive(xAs201RxQueue, &byte, portMAX_DELAY) == pdTRUE) {
            if (state > STATE_HEADER_3 && state < STATE_CHECKSUM) {
                calculated_sum += byte;
            }
            
            switch (state) {
                case STATE_HEADER_0:
                    if (byte == 0xAA) state = STATE_HEADER_1;
                    break;
                case STATE_HEADER_1:
                    state = (byte == 0xAA) ? STATE_HEADER_2 : STATE_HEADER_0;
                    break;
                case STATE_HEADER_2:
                    state = (byte == 0xAA) ? STATE_HEADER_3 : STATE_HEADER_0;
                    break;
                case STATE_HEADER_3:
                    if (byte == 0xAA) {
                        state = STATE_ADDR;
                        calculated_sum = 0;
                    } else {
                        state = STATE_HEADER_0;
                    }
                    break;
                case STATE_ADDR:
                    dev_addr = byte;
                    state = STATE_CMD;
                    break;
                case STATE_CMD:
                    cmd_code = byte;
                    state = STATE_OFFSET_LSB;
                    break;
                case STATE_OFFSET_LSB:
                    block_offset = byte;
                    state = STATE_OFFSET_MSB;
                    break;
                case STATE_OFFSET_MSB:
                    block_offset |= ((uint16_t)byte << 8);
                    state = STATE_LEN_LSB;
                    break;
                case STATE_LEN_LSB:
                    data_len = byte;
                    state = STATE_LEN_MSB;
                    break;
                case STATE_LEN_MSB:
                    data_len |= ((uint16_t)byte << 8);
                    if (data_len > sizeof(data_buf)) {
                        state = STATE_HEADER_0;
                    } else if (data_len == 0) {
                        state = STATE_CHECKSUM;
                    } else {
                        data_idx = 0;
                        state = STATE_DATA;
                    }
                    break;
                case STATE_DATA:
                    data_buf[data_idx++] = byte;
                    if (data_idx >= data_len) {
                        state = STATE_CHECKSUM;
                    }
                    break;
                case STATE_CHECKSUM:
                    checksum = byte;
                    if (checksum == calculated_sum) {
                        process_packet(cmd_code, data_buf, data_len);
                    } else {
                        // Debug: 打印校验和错误
                        static TickType_t last_err_time = 0;
                        TickType_t now = xTaskGetTickCount();
                        if (now - last_err_time >= pdMS_TO_TICKS(500)) {
                            last_err_time = now;
                            Oled_Queue_ShowString(1, 1, "Dist: ChkErr ");
                        }
                    }
                    state = STATE_HEADER_0;
                    break;
            }
        }
    }
}
