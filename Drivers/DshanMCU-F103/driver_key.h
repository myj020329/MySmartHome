#ifndef __DRIVER_KEY_H
#define __DRIVER_KEY_H

#include "stm32f1xx_hal.h"

#define KEY_GPIO_GROUP  GPIOB
#define KEY_GPIO_PIN    GPIO_PIN_14
#define KEY_STATUE()    HAL_GPIO_ReadPin(KEY_GPIO_GROUP, KEY_GPIO_PIN)

//typedef struct{
//    uint16_t num;
//    uint16_t time;
//}KeyEvent;

//    int Key_Read(void);
    int Key_Init(void);
    void EXTI0_IRQHandler(void);
    void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
    int Key_Read(uint8_t *buf, uint16_t len);
    void KeyShakeProcess_Callback(void);

#endif /* __DRIVER_KEY_H */

