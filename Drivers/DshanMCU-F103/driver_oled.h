/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_oled.h
 * 摘要：
 *  
 * 修改历史     版本号        Author       修改内容
 *--------------------------------------------------
 * 2020.8.18      v01         百问科技      创建文件
 *--------------------------------------------------
*/

#ifndef __DRIVER_OLED_H
#define __DRIVER_OLED_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

#define FRAME_WIDTH			128
#define FRAME_HEIGHT		64
#define FRAME_BUFFER_SIZE	((FRAME_WIDTH * FRAME_HEIGHT) / 8)


//初始化OLED
void OLED_Init(void);

//设置像素显示的起始页和起始列地址
void OLED_SetPosition(uint8_t page, uint8_t col);

//清屏函数
void OLED_Clear(void);

//显示一个字符
void OLED_PutChar(uint8_t x, uint8_t y, char c);


//显示一个字符串
int OLED_PrintString(uint8_t x, uint8_t y, const char *str);


///清除一行
void OLED_ClearLine(uint8_t x, uint8_t y);

//以16进制显示数值
int OLED_PrintHex(uint8_t x, uint8_t y, uint32_t val, uint8_t pre);

//获得OLED的Framebuffer
int OLED_PrintSignedVal(uint8_t x, uint8_t y, int32_t val);

//获得OLED的Framebuffer
void * OLED_GetFrameBuffer(uint32_t *pXres, uint32_t *pYres, uint32_t *pBpp);

//把Framebuffer的数据全部刷新到OLED
void OLED_Flush(void);

//刷新OLED的区域
void OLED_FlushRegion(int col, int row, int width, int heigh);


//把Framebuffer的数据全部清零
void OLED_ClearFrameBuffer(void);

//OLED测试程序
void OLED_Test(void);

#endif /* __DRIVER_OLED_H */

