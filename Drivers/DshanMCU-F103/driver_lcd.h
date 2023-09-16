#ifndef __DRIVER_LCD_H
#define __DRIVER_LCD_H

#include <stdint.h>

//初始化LCD
void LCD_Init(void);


//清屏函数
void LCD_Clear(void);

//显示一个字符
void LCD_PutChar(uint8_t x, uint8_t y, char c);


//显示一个字符串
int LCD_PrintString(uint8_t x, uint8_t y, const char *str);

//清除一行
void LCD_ClearLine(uint8_t x, uint8_t y);

//以16进制显示数值
int LCD_PrintHex(uint8_t x, uint8_t y, uint32_t val, uint8_t pre);

//以10进制显示一个数值
int LCD_PrintSignedVal(uint8_t x, uint8_t y, int32_t val);

//获得LCD的Framebuffer
void * LCD_GetFrameBuffer(uint32_t *pXres, uint32_t *pYres, uint32_t *pBpp);

//把Framebuffer的数据全部刷新到LCD
void LCD_Flush(void);

//刷新LCD的区域
void LCD_FlushRegion(int col, int row, int width, int heigh);

//把Framebuffer的数据全部清零
void LCD_ClearFrameBuffer(void);

//LCD测试程序
void LCD_Test(void);

#endif /* __DRIVER_LCD_H */

