#ifndef __AS201_H__
#define __AS201_H__

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include <stdint.h>

// 激光雷达单点数据结构 (按 1 字节对齐防止 HardFault)
typedef struct {
    int16_t distance;
    uint16_t noise;
    uint32_t peak;
    uint8_t confidence;
    uint32_t intg;
    int16_t reftof;
} __attribute__((packed)) LidarPoint_t;

extern QueueHandle_t xAs201RxQueue;

void As201_FreeRTOS_Init(void);
void vTaskAs201Parse(void *pvParameters);

#endif /* __AS201_H__ */
