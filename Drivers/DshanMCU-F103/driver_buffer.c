# include "driver_buffer.h"
#include <stdlib.h>
#include <string.h>

//��ʼ��һ��ָ���Ļ��λ�����
int Buffer_Init(ptRingBuffer buffer, uint16_t size)
{
    if(buffer == NULL || size == 0) return -1;
    if(buffer->fifo == NULL)
    {
        buffer->fifo = (uint8_t*)malloc(size);
    }
    buffer->pw = buffer->pr =0;
    buffer->buf_size = size;
    
    return 0;
}

//��ָ���Ļ��λ�����д��һ���ֽڵ�����
int Buffer_Write(ptRingBuffer buffer, const uint8_t data)
{
    if(buffer == NULL || buffer->fifo == NULL) return -1;
    int i = (buffer->pw +1) % buffer->buf_size;
    if(i != buffer->pr)
    {
        buffer->fifo[buffer->pw] = data;
        buffer->pw = i;
        
        return 0;
    }
    
    return -1;
}

//��ָ���Ļ��λ�����д�����ֽڵ�����
int Buffer_WriteBytes(ptRingBuffer buffer, const uint8_t *data_stream, uint8_t len)
{
    int i = 0;
    if(buffer == NULL || buffer->fifo == NULL) return -1;
    if(data_stream == NULL) return -1;
    if(len == 0) return -1;
    for (i = 0; i < len; i++)
    {
        if(Buffer_Write(buffer, data_stream[i]) != 0) break;
        
    }
    return i;
}

//��ָ���Ļ��λ���������һ���ֽڵ�����
int Buffer_Read(ptRingBuffer buffer, uint8_t *data)
{
    if(buffer == NULL || buffer->fifo == NULL) return -1;
    if(data == NULL) return -1;
    if(buffer->pr == buffer->pw) return -1;
    
    *data = buffer->fifo[buffer->pr];
    buffer->pr = (buffer->pr + 1) % buffer->buf_size;
    
        return 0;
    
    
}

//��ָ���Ļ��λ�������������ֽڵ�����
int Buffer_ReadBytes(ptRingBuffer buffer, uint8_t *data_stream, uint8_t len)
{
    int i = 0;
    if(buffer == NULL || buffer->fifo == NULL) return -1;
    if(data_stream == NULL) return -1;
    if(len == 0) return -1;
    for (i = 0; i < len; i++)
    {
        if(Buffer_Read(buffer, &data_stream[i]) != 0) break;
        
    }
    return i;
}

//���ָ���Ļ��λ�����
int Buffer_Clean(ptRingBuffer buffer)
{
    if(buffer == NULL || buffer->fifo == NULL) return -1;
    memset(buffer->fifo, 0, buffer->buf_size);
    buffer->pw = buffer->pr = 0;
    
    return 0;
}
