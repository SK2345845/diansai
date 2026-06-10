#include "ADC_SCAN.h"

/**
 * @brief  FreeRTOS 组件和任务初始化函数
 */
void Key_FreeRTOS_Init(void) {
    // 1. 创建按键消息队列（队列深度设为 4 已足够满足短按缓存需求）
    xKeyQueue = xQueueCreate(4, sizeof(uint8_t));
    configASSERT(xKeyQueue != NULL);
    
    // 2. 创建按键扫描任务（由于按键实时性要求高，赋予中高优先级 tskIDLE_PRIORITY + 2）
    xTaskCreate(vTaskKeyScan, 
                "KeyScanTask", 
                1024, 
                NULL, 
                tskIDLE_PRIORITY + 2, 
                NULL);
                
    // 3. 创建专门的按键后效处理任务（负责联动OLED显示）
    xTaskCreate(vTaskKeyLogic, 
                "KeyLogicTask", 
                1024, 
                NULL, 
                tskIDLE_PRIORITY + 1, 
                NULL);
}
