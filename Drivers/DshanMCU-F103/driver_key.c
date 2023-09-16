#include "driver_key.h"
# include "driver_buffer.h"
#include "dev_io.h"

static RingBuffer KeyBuffer;
volatile static uint32_t KeyTrigerTime = 0;

//��ʼ��������GPIO��ʹ�����ⲿʹ��
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
 
 //�ⲿ�ж�0���жϷ�����
 void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_GPIO_PIN);
}

static uint8_t key_flag = 0;

//GPIO�ⲿ�жϵĻص��������������жϵ�GPIO�����񣬴˴��Ǹ��°����Ĵ���ʱ��
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
        if(GPIO_Pin == KEY_GPIO_PIN)
        key_flag = ~key_flag;
        HAL_GPIO_WritePin(KEY_GPIO_GROUP, KEY_GPIO_PIN, key_flag?GPIO_PIN_RESET:GPIO_PIN_SET);
}

//��ȡ������Ϣ�������Ƕ�ΰ�����Ϣ
int Key_Read(uint8_t *buf, uint16_t len)
{
    if(len ==0|| len<sizeof(KeyEvent)||(len % sizeof(KeyEvent)) !=0)    return -1;
    if(buf == NULL) return -1;
    
    if(Buffer_ReadBytes(&KeyBuffer, buf, len) == len)
        return 0;
    return -1;
}

//�����������Ļص�����������Systick��1ms�жϷ������е���
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




