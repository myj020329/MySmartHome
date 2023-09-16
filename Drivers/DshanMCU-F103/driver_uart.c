#include "driver_uart.h"
//#include "driver_lcd.h"
//#include "driver_timer.h"
#include "usart.h"

#include <stdio.h>

#define DEBUG_UART_TIMEOUT 500

extern UART_HandleTypeDef huart1;
static UART_HandleTypeDef * g_HDebugUART = &huart1;

//UART初始化函数
void UART_Init(void)
{
}


int fputc(int c, FILE *f) 
{
    (void)f;
    HAL_UART_Transmit(g_HDebugUART, (uint8_t *)&c, 1, DEBUG_UART_TIMEOUT);
    return c;
}

int fgetc(FILE *f)
{
    uint8_t ch = 0;
    (void)f;

    /* Clear the Overrun flag just before receiving the first character */
    __HAL_UART_CLEAR_OREFLAG(g_HDebugUART);

    /* Wait for reception of a character on the USART RX line and echo this
    * character on console */
    HAL_UART_Receive(g_HDebugUART, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    HAL_UART_Transmit(g_HDebugUART, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;    
}


//UART测试程序
void UART_Test(void)
{    
    char c;
    
    UART_Init();

    ///LCD_PrintString(0, 0, "Use Serial Tool on PC to test UART");

    printf("100ask UART test:\n\r");
    while (1)
    {
        c = fgetc(NULL);
        printf("\n\rget %c\n\r", c);
    }
}
