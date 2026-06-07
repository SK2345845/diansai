#ifndef __OLED_TASK_H
#define __OLED_TASK_H

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include <stdint.h>

/* 消息类型枚举 */
typedef enum {
    OLED_MSG_CLEAR = 0,
    OLED_MSG_SHOW_CHAR,
    OLED_MSG_SHOW_STRING,
    OLED_MSG_SHOW_NUM,
    OLED_MSG_SHOW_SIGNED_NUM,
    OLED_MSG_SHOW_HEX_NUM,
    OLED_MSG_SHOW_BIN_NUM
} OledMsgType_e;

/* OLED 消息结构体 */
typedef struct {
    OledMsgType_e type;
    uint8_t line;
    uint8_t column;
    uint8_t length;     // 用于数字显示的长度
    union {
        char ch;
        char str[17];   // 最大支持一行16个字符 + 结束符
        uint32_t num;
        int32_t snum;
    } data;
} OledMsg_t;

/* 外部队列句柄 */
extern QueueHandle_t xOledQueue;

/* 函数声明 */
void Oled_FreeRTOS_Init(void);
void vTaskOledDisplay(void *pvParameters);

/* 快捷投递消息的 API */
void Oled_Queue_Clear(void);
void Oled_Queue_ShowChar(uint8_t Line, uint8_t Column, char Char);
void Oled_Queue_ShowString(uint8_t Line, uint8_t Column, const char *String);
void Oled_Queue_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void Oled_Queue_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void Oled_Queue_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void Oled_Queue_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif /* __OLED_TASK_H */
