#ifndef __UART1_H__
#define __UART1_H__

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include <stdarg.h>
#include <stdio.h>

#define UART_MSG_MAX_LEN 64

typedef struct {
    char str[UART_MSG_MAX_LEN];
} UartMsg_t;

extern QueueHandle_t xUartQueue;

void Uart_FreeRTOS_Init(void);
void vTaskUartPrint(void *pvParameters);
void Uart_Printf(const char *format, ...);

#endif /* __UART1_H__ */
