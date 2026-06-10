#ifndef __MAIN_TASK_H__
#define __MAIN_TASK_H__

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include <stdint.h>

/* ================================================================
 *  1. 命令类型枚举 — 其他任务通过此枚举向 main_task 发送命令
 * ================================================================ */
typedef enum {
    MAIN_CMD_KEY_EVENT = 0,     // 按键事件
    MAIN_CMD_SENSOR_DATA,       // 传感器数据更新
    MAIN_CMD_SYSTEM_ERROR,      // 系统错误/告警
    MAIN_CMD_NAV_UPDATE,        // 导航/姿态更新
    MAIN_CMD_UART_RX,           // 串口接收数据
    MAIN_CMD_MOTOR_STATUS,      // 电机状态
    MAIN_CMD_TIMER_EVENT,       // 定时器事件
    MAIN_CMD_USER_REQUEST,      // 用户自定义请求
    MAIN_CMD_MAX
} MainCmdType_e;

/* ================================================================
 *  2. 消息结构体 — 统一的消息格式
 * ================================================================ */
typedef struct {
    MainCmdType_e cmdType;      // 命令类型
    uint32_t      param1;       // 参数1（通用整型）
    uint32_t      param2;       // 参数2（通用整型）
    int32_t       value;        // 有符号数值（如传感器原始值）
    void         *pData;        // 可选：指向附加数据的指针
    uint8_t       senderID;     // 发送者任务 ID（用于溯源）
} MainMsg_t;

/* ================================================================
 *  3. 外部全局队列句柄 — 其他任务通过此队列向 main_task 发消息
 * ================================================================ */
extern QueueHandle_t xMainQueue;

/* ================================================================
 *  4. 函数声明
 * ================================================================ */
void MainTask_FreeRTOS_Init(void);
void vTaskMainBrain(void *pvParameters);

/* ================================================================
 *  5. 快捷投递消息的 API — 供其他任务调用
 * ================================================================ */

/* 发送按键事件 */
void Main_SendKeyEvent(uint8_t keyID, uint8_t senderID);

/* 发送传感器数据 */
void Main_SendSensorData(int32_t rawValue, uint8_t sensorType, uint8_t senderID);

/* 发送系统错误 */
void Main_SendSystemError(uint32_t errorCode, uint8_t senderID);

/* 发送通用命令 */
void Main_SendCommand(MainCmdType_e cmd, uint32_t p1, uint32_t p2, int32_t val,
                      void *pData, uint8_t senderID);

#endif /* __MAIN_TASK_H__ */
