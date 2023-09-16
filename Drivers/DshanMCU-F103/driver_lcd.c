#include "driver_oled.h"

//初始化LCD

void LCD_Init(void)
{
    OLED_Init();
}


//清屏函数
void LCD_Clear(void)
{
    OLED_Clear();
}

//显示一个字符
void LCD_PutChar(uint8_t x, uint8_t y, char c)
{
    OLED_PutChar(x, y, c);
}


//显示一个字符串
int LCD_PrintString(uint8_t x, uint8_t y, const char *str)
{
   return OLED_PrintString(x, y, str);
}

//清除一行
void LCD_ClearLine(uint8_t x, uint8_t y)
{
   OLED_ClearLine(x, y);
}

//以16进制显示数值
int LCD_PrintHex(uint8_t x, uint8_t y, uint32_t val, uint8_t pre)
{
    return OLED_PrintHex(x, y, val, pre);
}

//以10进制显示一个数值
int LCD_PrintSignedVal(uint8_t x, uint8_t y, int32_t val)
{
    return OLED_PrintSignedVal(x, y, val);
}

//获得LCD的Framebuffer
void * LCD_GetFrameBuffer(uint32_t *pXres, uint32_t *pYres, uint32_t *pBpp)
{
    return OLED_GetFrameBuffer(pXres, pYres, pBpp);
}


//把Framebuffer的数据全部刷新到LCD
void LCD_Flush(void)
{
    OLED_Flush();
}

//刷新LCD的区域
void LCD_FlushRegion(int col, int row, int width, int heigh)
{
    OLED_FlushRegion(col, row, width, heigh);
}


//把Framebuffer的数据全部清零
void LCD_ClearFrameBuffer(void)
{
    OLED_ClearFrameBuffer();
}

//lcd测试
void LCD_Test(void)
{
    OLED_Test();
}


