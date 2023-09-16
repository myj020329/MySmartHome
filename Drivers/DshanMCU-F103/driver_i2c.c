#include "driver_i2c.h"

void I2C_Delay(uint32_t t)
{
    volatile uint32_t tmp = t;
    while(tmp--);
}

void I2C_GPIO_ReInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    HAL_GPIO_DeInit(SDA_PORT, SDA_PIN);
    
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        
    GPIO_InitStruct.Pin = SCL_PIN;
    
    HAL_GPIO_Init(SCL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = SDA_PIN;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);
}

void I2C_Start(void)
{
    SCL_H;
    SDA_H;
    I2C_Delay(100);
    SDA_L;
    I2C_Delay(100);
}

void I2C_Stop(void)
{
    SDA_L;
    SCL_H;
    I2C_Delay(100);
    SDA_H;
    I2C_Delay(100);
}

int I2C_GetAck(void)
{
    int i = 0;
    SCL_L;
    SDA_H;
    I2C_Delay(100);
    SCL_H;
    while(SDA_IN != 0)
    {
        i++;
        if(i == 100)
        {
            SCL_L;
            return -1;
        }
        I2C_Delay(10);
    }
    SCL_L;
    return 0;
}


void I2C_ACK(void)
{
    SCL_L;
    SDA_L;
    I2C_Delay(100);
    SCL_H;
    I2C_Delay(100);
}

void I2C_NACK(void)
{
    SCL_L;
    SDA_H;
    I2C_Delay(100);
    SCL_H;
    I2C_Delay(100);
}

void I2C_WriteByte(uint8_t data)
{
    uint8_t i = 0;
    for(i=0; i<8; i++)
    {
        SCL_L;
        I2C_Delay(100);
        if(data & 0x80)
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }
        data <<= 1; // 发出1bit数据后，要更新数据，将data的次高位移位到最高位
        SCL_H;
        I2C_Delay(100);
    }
    I2C_GetAck();
}

uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t i = 0;
    uint8_t data = 0;
    
    SDA_H;
    for(i=0; i<8; i++)
    {
        SCL_L;
        I2C_Delay(100);
        SCL_H;
        I2C_Delay(100);
        data <<= 1; // 更新数据前，要将上一次数据左移1位用来保存接下来的这一位数据
        if(SDA_IN == 1)    
        {                 
            data++;
        }
        else
        {
            data = data;
        }
    }
    
    if(ack == 0)
    {
        I2C_ACK();
    }
    else if(ack == 1)
    {
        I2C_NACK();
    }
    
    return data;
}

