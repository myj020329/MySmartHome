
#ifndef _DRIVER_LED_H
#define _DRIVER_LED_H

#include "stm32f1xx_hal.h"


#define LED_PORT        GPIOA
#define LED_PIN         GPIO_PIN_1
#define LED(STATUS)     HAL_GPIO_WritePin(LED_PORT, LED_PIN, STATUS?GPIO_PIN_RESET:GPIO_PIN_SET)
#define LED_SHINE()     HAL_GPIO_TogglePin(LED_PORT, LED_PIN)

int LED_Init(void);
int LED_WriteStatus(uint8_t status);

#endif /* _DRIVER_LED_H */

