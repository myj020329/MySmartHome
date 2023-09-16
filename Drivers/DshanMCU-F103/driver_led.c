#include "driver_led.h"
//#include "driver_timer.h"

///#include "gpio.h"

int LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
    return 0;
}

/*
 * 函数名：Driver_LED_WriteStatus
 * 功能：控制LED的状态
 * 输入参数：status：0-灭；1-亮
 * 输出参数：无
 * 返回值：0-成功；-1-失败；
*/
int LED_WriteStatus(uint8_t status)
{
    LED(status);
    
    return 0;
}
