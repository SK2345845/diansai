#ifndef __ADC_SCAN_H__
#define __ADC_SCAN_H__
//
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

/* 1. 按键 ID 枚举定义 */
typedef enum {
    KEY_NONE = 0,   // 无按键按下
    KEY_1,          // 按键 1 （中键）
    KEY_2,          // 按键 2 （左键）
    KEY_3,          // 按键 3 （右键）
    KEY_4,          // 按键 4 （上键）
    KEY_5,          // 按键 5 （下键）
    KEY_MAX
} key_id_t;

/* 2. 按键消抖状态机定义 */
typedef enum {
    KEY_STATE_IDLE = 0,     // 空闲状态（无按键）
    KEY_STATE_DEBOUNCE,     // 软件消抖状态
    KEY_STATE_WAIT_RELEASE  // 等待松手状态（防止重复触发）
} key_state_t;

/* 3. 全局队列句柄声明 */
extern QueueHandle_t xKeyQueue;

/* 4. 函数声明 */
void Key_FreeRTOS_Init(void);
void vTaskKeyScan(void *pvParameters);
void vTaskKeyLogic(void *pvParameters);

#endif /* __ADC_SCAN_H__ */
