/*
 * Copyright (c) 2016-2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_freertos.c ========
 */
#include <stdint.h>

#ifdef __ICCARM__
#include <DLib_Threads.h>
#endif
/* POSIX header files */
#include <pthread.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>

#include "ti_drivers_config.h"
#include "ti_msp_dl_config.h"

/* 按键 ADC 任务头文件 */
#include "targetConfigs/key/ADC_SCAN.h"

/* OLED 任务头文件 */
#include "targetConfigs/oled/OLED_Task.h"

/* AS201 激光雷达任务头文件 */
#include "targetConfigs/as201/as201.h"

/* AS201 IMU 任务头文件 */
// #include "src/as201/AS201.h"

/* Main Brain 总控任务头文件 */
#include "targetConfigs/mainTask/main_task.h"

extern void *mainThread(void *arg0);

/* Stack size in bytes */
#define THREADSTACKSIZE configMINIMAL_STACK_SIZE * 4

/* Set up the hardware ready to run this demo */
static void prvSetupHardware(void);

/*

 *  ======== main ========
 */
int main(void)
{



    // 初始化硬件
    prvSetupHardware();

    // 初始化按键 ADC 任务
    Key_FreeRTOS_Init();

    // 初始化 OLED 任务
    Oled_FreeRTOS_Init();

    /* Initialize AS201 Laser FreeRTOS tasks */
    As201_FreeRTOS_Init();

    // 初始化 AS201 IMU 任务
    // IMU_FreeRTOS_Init();

    // 初始化 Main Brain 总控任务
    MainTask_FreeRTOS_Init();

    // 启动 FreeRTOS 任务调度器
    vTaskStartScheduler();

    return (0);
}
static void prvSetupHardware(void)
{
    SYSCFG_DL_init();
}
/*-----------------------------------------------------------*/

/* ================================================================
 *  Main Brain 总控任务 — 全局定义
 * ================================================================ */

/* 消息队列句柄（定义在 main_task.h 中已声明为 extern） */
QueueHandle_t xMainQueue = NULL;

/* Main Brain 任务栈大小 */
#define MAIN_TASK_STACK_SIZE (configMINIMAL_STACK_SIZE * 4)

/*-----------------------------------------------------------*/

/*
 *  MainTask_FreeRTOS_Init
 *  创建消息队列 并 创建 main_task 任务
 */
void MainTask_FreeRTOS_Init(void)
{
    /* 创建消息队列，最多容纳 20 条消息 */
    xMainQueue = xQueueCreate(20, sizeof(MainMsg_t));
    configASSERT(xMainQueue != NULL);

    /* 创建 Main Brain 任务 */
    BaseType_t ret = xTaskCreate(vTaskMainBrain,
                                 "MainBrain",
                                 MAIN_TASK_STACK_SIZE,
                                 NULL,
                                 tskIDLE_PRIORITY + 3,  /* 较高优先级，便于及时决策 */
                                 NULL);
    configASSERT(ret == pdPASS);
}

/*-----------------------------------------------------------*/

/*
 *  vTaskMainBrain — 程序大脑，接收其他任务的消息，做总决策判断
 *
 *  @brief  通过 xMainQueue 接收 MainMsg_t 消息，
 *          根据 cmdType 分发到对应的处理分支。
 *
 *  工作流程（伪代码）：
 *     loop:
 *       阻塞等待消息（xQueueReceive）
 *       switch (msg.cmdType):
 *         case MAIN_CMD_KEY_EVENT:
 *             ── 解析按键 → 切换运行模式 / 触发标定 / 紧急停车
 *         case MAIN_CMD_SENSOR_DATA:
 *             ── 更新全局传感器结构体 → 阈值检测 → 异常时告警
 *         case MAIN_CMD_SYSTEM_ERROR:
 *             ── 根据 errorCode 分级处理 → 恢复 / 降级 / 停机
 *         case MAIN_CMD_NAV_UPDATE:
 *             ── 更新当前姿态/位置 → 决策下一步运动方向
 *         case MAIN_CMD_UART_RX:
 *             ── 解析外部指令 → 执行相应操作
 *         case MAIN_CMD_MOTOR_STATUS:
 *             ── 更新电机状态 → 故障时停车
 *         case MAIN_CMD_TIMER_EVENT:
 *             ── 定时触发的周期性决策（如 PID 控制周期）
 *         case MAIN_CMD_USER_REQUEST:
 *             ── 用户自定义逻辑
 *         default:
 *             ── 未知命令，忽略或记录日志
 */
void vTaskMainBrain(void *pvParameters)
{
    (void)pvParameters;
    MainMsg_t msg;

    for (;;)
    {
        /* 阻塞等待其他任务发来的消息 */
        if (xQueueReceive(xMainQueue, &msg, portMAX_DELAY) == pdPASS)
        {
            switch (msg.cmdType)
            {
            /* ------------------------------------------------------ */
            case MAIN_CMD_KEY_EVENT:
            {
                /*
                 * 伪代码：
                 *   key_id = (uint8_t)msg.param1;
                 *   if (key_id == KEY_1) { 切换运行模式; }
                 *   if (key_id == KEY_2) { 启动/暂停任务; }
                 *   if (key_id == KEY_3) { 紧急停车; }
                 *   更新全局状态机 → 通知 OLED/UART 等输出任务
                 */
                break;
            }
            /* ------------------------------------------------------ */
            case MAIN_CMD_SENSOR_DATA:
            {
                /*
                 * 伪代码：
                 *   sensor_type = (uint8_t)msg.param1;
                 *   raw_value   = msg.value;
                 *   更新全局传感器结构体 sensor_data[sensor_type] = raw_value;
                 *   if (raw_value > THRESHOLD_HIGH) { 触发告警; }
                 *   if (raw_value < THRESHOLD_LOW)  { 触发告警; }
                 *   必要时 → Main_SendCommand(MAIN_CMD_SYSTEM_ERROR, ...);
                 */
                break;
            }
            /* ------------------------------------------------------ */
            case MAIN_CMD_SYSTEM_ERROR:
            {
                /*
                 * 伪代码：
                 *   error_code = msg.param1;
                 *   根据 error_code 分级处理：
                 *     LEVEL_1（可恢复）→ 复位相应模块
                 *     LEVEL_2（需降级）→ 关闭部分功能，继续运行
                 *     LEVEL_3（致命）  → 停止所有电机，进入安全模式
                 *   记录错误日志
                 */
                break;
            }
            /* ------------------------------------------------------ */
            case MAIN_CMD_NAV_UPDATE:
            {
                /*
                 * 伪代码：
                 *   从 msg 中提取姿态/位置数据
                 *   更新全局导航状态
                 *   调用决策函数 → 计算下一目标点
                 *   向电机任务发送运动指令
                 */
                break;
            }
            /* ------------------------------------------------------ */
            case MAIN_CMD_UART_RX:
            {
                /*
                 * 伪代码：
                 *   解析 msg.pData 指向的串口数据帧
                 *   执行外部指令（如遥控命令、调试命令）
                 *   必要时 → 向其他任务转发指令
                 */
                break;
            }
            /* ------------------------------------------------------ */
            case MAIN_CMD_MOTOR_STATUS:
            {
                /*
                 * 伪代码：
                 *   motor_id  = (uint8_t)msg.param1;
                 *   status    = (uint8_t)msg.param2;
                 *   更新电机状态表 motor_status[motor_id] = status;
                 *   if (status == FAULT) { 停车 + 发送系统错误; }
                 */
                break;
            }
            /* ------------------------------------------------------ */
            case MAIN_CMD_TIMER_EVENT:
            {
                /*
                 * 伪代码：
                 *   周期性的系统巡检：
                 *     - 读取所有传感器最新值
                 *     - 运行控制算法（如 PID）
                 *     - 更新 OLED 显示
                 *     - 检查心跳超时
                 */
                break;
            }
            /* ------------------------------------------------------ */
            case MAIN_CMD_USER_REQUEST:
            {
                /*
                 * 伪代码：
                 *   用户自定义逻辑
                 */
                break;
            }
            /* ------------------------------------------------------ */
            default:
                /* 未知命令，忽略 */
                break;
            }
        }
    }
}

/*-----------------------------------------------------------*/

/* ================================================================
 *  快捷投递消息的 API 实现 — 供其他任务调用
 * ================================================================ */

void Main_SendKeyEvent(uint8_t keyID, uint8_t senderID)
{
    MainMsg_t msg = {
        .cmdType  = MAIN_CMD_KEY_EVENT,
        .param1   = keyID,
        .senderID = senderID
    };
    xQueueSend(xMainQueue, &msg, 0);
}

void Main_SendSensorData(int32_t rawValue, uint8_t sensorType, uint8_t senderID)
{
    MainMsg_t msg = {
        .cmdType  = MAIN_CMD_SENSOR_DATA,
        .param1   = sensorType,
        .value    = rawValue,
        .senderID = senderID
    };
    xQueueSend(xMainQueue, &msg, 0);
}

void Main_SendSystemError(uint32_t errorCode, uint8_t senderID)
{
    MainMsg_t msg = {
        .cmdType  = MAIN_CMD_SYSTEM_ERROR,
        .param1   = errorCode,
        .senderID = senderID
    };
    xQueueSend(xMainQueue, &msg, 0);
}

void Main_SendCommand(MainCmdType_e cmd, uint32_t p1, uint32_t p2, int32_t val,
                      void *pData, uint8_t senderID)
{
    MainMsg_t msg = {
        .cmdType  = cmd,
        .param1   = p1,
        .param2   = p2,
        .value    = val,
        .pData    = pData,
        .senderID = senderID
    };
    xQueueSend(xMainQueue, &msg, 0);
}

/*-----------------------------------------------------------*/
// 内存分配失败钩函数
// @param void
void vApplicationMallocFailedHook(void)
{
    /*
     * vApplicationMallocFailedHook() will only be called if
     * configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a
     * hook function that will get called if a call to pvPortMalloc() fails.
     * pvPortMalloc() is called internally by the kernel whenever a task,
     * queue, timer or semaphore is created. It is also called by various
     * parts of the demo application. If heap_1.c or heap_2.c are used,
     * then the size of the heap available to pvPortMalloc() is defined by
     * configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the
     * xPortGetFreeHeapSize() API function can be used to query the size of
     * free heap space that remains (although it does not provide information
     * on how the remaining heap might be fragmented).
     */
    taskDISABLE_INTERRUPTS();
    for (;;)
        ;
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
    /*
     * vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
     * to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the
     * idle task. It is essential that code added to this hook function never
     * attempts to block in any way (for example, call xQueueReceive() with a
     * block time specified, or call vTaskDelay()). If the application makes
     * use of the vTaskDelete() API function (as this demo application does)
     * then it is also important that vApplicationIdleHook() is permitted to
     * return to its calling function, because it is the responsibility of the
     * idle task to clean up memory allocated by the kernel to any task that
     * has since been deleted.
     */
}
/*-----------------------------------------------------------*/

#if (configCHECK_FOR_STACK_OVERFLOW)
/*
     *  ======== vApplicationStackOverflowHook ========
     *  When stack overflow checking is enabled the application must provide a
     *  stack overflow hook function. This default hook function is declared as
     *  weak, and will be used by default, unless the application specifically
     *  provides its own hook function.
     */
#if defined(__IAR_SYSTEMS_ICC__)
__weak void vApplicationStackOverflowHook(
    TaskHandle_t pxTask, char *pcTaskName)
#elif (defined(__TI_COMPILER_VERSION__))
#pragma WEAK(vApplicationStackOverflowHook)
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
#elif (defined(__GNUC__) || defined(__ti_version__))
void __attribute__((weak))
vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
#endif
{
    (void) pcTaskName;
    (void) pxTask;

    /*
     * Run time stack overflow checking is performed if
     * configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook
     * function is called if a stack overflow is detected.
     */
    taskDISABLE_INTERRUPTS();
    for (;;)
        ;
}
#endif
