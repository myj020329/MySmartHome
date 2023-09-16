#include "driver_key.h"
# include "driver_buffer.h"
#include "dev_io.h"

static RingBuffer KeyBuffer;
volatile static uint32_t KeyTrigerTime = 0;

//初始化按键的GPIO、使能其外部使能
 int Key_Init(void)
 {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    Buffer_Init(&KeyBuffer, sizeof(KeyBuffer)<<4);
    
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = KEY_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    
    HAL_GPIO_Init(KEY_GPIO_GROUP, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0 , 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    
    return 0;
 }
 
 //外部中断0的中断服务函数
 void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_GPIO_PIN);
}

static uint8_t key_flag = 0;

//GPIO外部中断的回调函数，处理触发中断的GPIO的事务，此处是更新按键的触发时刻
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
        if(GPIO_Pin == KEY_GPIO_PIN)
        key_flag = ~key_flag;
        HAL_GPIO_WritePin(KEY_GPIO_GROUP, KEY_GPIO_PIN, key_flag?GPIO_PIN_RESET:GPIO_PIN_SET);
}

//读取按键信息，可以是多次按键信息
int Key_Read(uint8_t *buf, uint16_t len)
{
    if(len ==0|| len<sizeof(KeyEvent)||(len % sizeof(KeyEvent)) !=0)    return -1;
    if(buf == NULL) return -1;
    
    if(Buffer_ReadBytes(&KeyBuffer, buf, len) == len)
        return 0;
    return -1;
}

//处理按键消抖的回调函数，会在Systick的1ms中断服务函数中调用
void KeyShakeProcess_Callback(void)
{
    KeyEvent nKeyEnvent = {0};
    static uint32_t press_time = 0;
    static uint32_t release_time = 0;
    uint32_t tick = HAL_GetTick();
    if(tick == KeyTrigerTime)
    {
        if(KEY_STATUE() == 0)
        {
            press_time = tick;
        }
        else
        {
            release_time = tick;
        }
        if(press_time != 0 && release_time != 0)
        {
            nKeyEnvent.num = 1;
            nKeyEnvent.time = release_time - press_time;
            release_time = press_time = 0;
            Buffer_WriteBytes(&KeyBuffer, (uint8_t*)&nKeyEnvent.num, sizeof(KeyEvent));
        }
    }
}




