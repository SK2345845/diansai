#include "OLED_Task.h"
#include "OLED.h"
#include <string.h>

/* 队列句柄定义 */
QueueHandle_t xOledQueue = NULL;

/**
 * @brief  初始化 OLED 任务和队列
 */
void Oled_FreeRTOS_Init(void) {
    // 1. 初始化底层 OLED
    OLED_Init();

    // 2. 创建 OLED 消息队列（队列深度设为 10，可根据实际刷新频率调整）
    xOledQueue = xQueueCreate(10, sizeof(OledMsg_t));
    configASSERT(xOledQueue != NULL);
    
    // 3. 创建 OLED 显示任务
    xTaskCreate(vTaskOledDisplay, 
                "OledTask", 
                256, 
                NULL, 
                tskIDLE_PRIORITY + 2, 
                NULL);
}

/**
 * @brief  OLED 固定频率刷新任务 (周期 50ms)
 */
void vTaskOledDisplay(void *pvParameters) {
    TickType_t xLastWakeTime;
    const TickType_t xBlockTime = pdMS_TO_TICKS(50); // 50ms (20FPS)
    OledMsg_t msg;
    
    // 初始化最后唤醒时间
    xLastWakeTime = xTaskGetTickCount();
    
    while (1) {
        // 使用 vTaskDelayUntil 保证精确的刷新周期
        vTaskDelayUntil(&xLastWakeTime, xBlockTime);
        
        // 把在这个 50ms 周期内积压在队列里的显示指令一口气执行完
        while (xQueueReceive(xOledQueue, &msg, 0) == pdPASS) {
            switch (msg.type) {
                case OLED_MSG_CLEAR:
                    OLED_Clear();
                    break;
                case OLED_MSG_SHOW_CHAR:
                    OLED_ShowChar(msg.line, msg.column, msg.data.ch);
                    break;
                case OLED_MSG_SHOW_STRING:
                    OLED_ShowString(msg.line, msg.column, msg.data.str);
                    break;
                case OLED_MSG_SHOW_NUM:
                    OLED_ShowNum(msg.line, msg.column, msg.data.num, msg.length);
                    break;
                case OLED_MSG_SHOW_SIGNED_NUM:
                    OLED_ShowSignedNum(msg.line, msg.column, msg.data.snum, msg.length);
                    break;
                case OLED_MSG_SHOW_HEX_NUM:
                    OLED_ShowHexNum(msg.line, msg.column, msg.data.num, msg.length);
                    break;
                case OLED_MSG_SHOW_BIN_NUM:
                    OLED_ShowBinNum(msg.line, msg.column, msg.data.num, msg.length);
                    break;
                default:
                    break;
            }
        }
    }
}

/* ========================================================== */
/* 下面是一些提供给其他业务任务的快捷 API 函数，方便直接投递消息   */
/* ========================================================== */

// 清除显示
void Oled_Queue_Clear(void) {
    OledMsg_t msg;
    msg.type = OLED_MSG_CLEAR;
    xQueueSend(xOledQueue, &msg, 0);
}
// 显示字符
// @param Line 行号
// @param Column 列号
// @param Char 字符
void Oled_Queue_ShowChar(uint8_t Line, uint8_t Column, char Char) {
    OledMsg_t msg;
    msg.type = OLED_MSG_SHOW_CHAR;
    msg.line = Line;
    msg.column = Column;
    msg.data.ch = Char;
    xQueueSend(xOledQueue, &msg, 0);
}
// 显示字符串
// @param Line 行号
// @param Column 列号
// @param String 字符串
// @param Length 显示长度
void Oled_Queue_ShowString(uint8_t Line, uint8_t Column, const char *String) {
    OledMsg_t msg;
    msg.type = OLED_MSG_SHOW_STRING;
    msg.line = Line;
    msg.column = Column;
    strncpy(msg.data.str, String, 16);
    msg.data.str[16] = '\0'; // 确保字符串以 null 结尾
    xQueueSend(xOledQueue, &msg, 0);
}
// 显示无符号整数
// @param Line 行号
// @param Column 列号
// @param Number 无符号整数
// @param Length 显示长度
void Oled_Queue_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length) {
    OledMsg_t msg;
    msg.type = OLED_MSG_SHOW_NUM;
    msg.line = Line;
    msg.column = Column;
    msg.length = Length;
    msg.data.num = Number;
    xQueueSend(xOledQueue, &msg, 0);
}
// 显示有符号整数
// @param Line 行号
// @param Column 列号
// @param Number 有符号整数
// @param Length 显示长度
void Oled_Queue_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length) {
    OledMsg_t msg;
    msg.type = OLED_MSG_SHOW_SIGNED_NUM;
    msg.line = Line;
    msg.column = Column;
    msg.length = Length;
    msg.data.snum = Number;
    xQueueSend(xOledQueue, &msg, 0);
}
// 显示十六进制数
// @param Line 行号
// @param Column 列号
// @param Number 十六进制数
// @param Length 显示长度
void Oled_Queue_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length) {
    OledMsg_t msg;
    msg.type = OLED_MSG_SHOW_HEX_NUM;
    msg.line = Line;
    msg.column = Column;
    msg.length = Length;
    msg.data.num = Number;
    xQueueSend(xOledQueue, &msg, 0);
}
// 显示二进制数
// @param Line 行号
// @param Column 列号
// @param Number 二进制数
// @param Length 显示长度
void Oled_Queue_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length) {
    OledMsg_t msg;
    msg.type = OLED_MSG_SHOW_BIN_NUM;
    msg.line = Line;
    msg.column = Column;
    msg.length = Length;
    msg.data.num = Number;
    xQueueSend(xOledQueue, &msg, 0);
}
