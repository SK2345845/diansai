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

/* 串口打印任务头文件 */
#include "targetConfigs/uart1/uart1.h"

/* AS201 IMU 任务头文件 */
// #include "src/as201/AS201.h"

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


    /* Prepare the hardware to run this demo. */
    prvSetupHardware();

    /* Initialize Key ADC FreeRTOS tasks */
    Key_FreeRTOS_Init();

    /* Initialize OLED FreeRTOS tasks */
    Oled_FreeRTOS_Init();

    /* Initialize UART FreeRTOS tasks */
    Uart_FreeRTOS_Init();

    /* Initialize AS201 IMU Tasks */
    // IMU_FreeRTOS_Init();

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    return (0);
}
// 初始化硬件
// @param void
static void prvSetupHardware(void)
{
    SYSCFG_DL_init();
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
// 空闲钩函数
// @param void
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
// 栈溢出钩函数
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
