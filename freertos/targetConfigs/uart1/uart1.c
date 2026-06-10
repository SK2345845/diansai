#include "uart1.h"
#include "ti_msp_dl_config.h"
#include <string.h>

QueueHandle_t xUartQueue = NULL;

void Uart_FreeRTOS_Init(void) {
    xUartQueue = xQueueCreate(16, sizeof(UartMsg_t));
    configASSERT(xUartQueue != NULL);
    
    xTaskCreate(vTaskUartPrint, 
                "UartPrintTask", 
                512, 
                NULL, 
                tskIDLE_PRIORITY + 1, 
                NULL);
}

void vTaskUartPrint(void *pvParameters) {
    UartMsg_t msg;
    while (1) {
        if (xQueueReceive(xUartQueue, &msg, portMAX_DELAY) == pdTRUE) {
            char *p = msg.str;
            while (*p) {
                DL_UART_Main_transmitDataBlocking(UART_0_INST, *p++);
            }
        }
    }
}

void Uart_Printf(const char *format, ...) {
    if (xUartQueue == NULL) {
        return;
    }
    
    UartMsg_t msg;
    va_list args;
    va_start(args, format);
    vsnprintf(msg.str, UART_MSG_MAX_LEN, format, args);
    va_end(args);
    
    xQueueSend(xUartQueue, &msg, 0);
}
