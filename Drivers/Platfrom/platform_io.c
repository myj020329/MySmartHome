#include "platform_io.h"

#include <driver_led.h>
#include <driver_key.h>
#include <driver_uart.h>

//�豸��ʼ��
void platform_io_init(struct IODev *dev)
{
    if(dev == NULL) return;
    
    switch(dev->Type)
    {
        case LED:
        {
            LED_Init();
            break;
        }
        case KEY:
        {
            Key_Init();
            break;
        }
        case DBGOUT:
        {
            UART_Init();
            break;
        }
        default:break;
    }
}

//�����豸���
int platform_io_write(struct IODev *dev, uint8_t *buf, uint16_t len)
{
    if(dev == NULL || buf==NULL || len==0) return -1;
    
    return LED_WriteStatus(buf[0]);
}

//�����豸����
int platform_io_read(struct IODev *dev, uint8_t *buf, uint16_t len)
{
    if(dev == NULL || buf==NULL || len==0) return -1;
    
    return Key_Read(buf, len);
}

