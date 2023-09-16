#ifndef __DEV_IO_H
#define __DEV_IO_H

typedef enum{
    LED     = (0),
    KEY     = (1),
    DBGOUT  = (2),
}IODevType;

typedef struct{
    unsigned short num;   // 按键序号
    unsigned short time;  // 按键持续时间
}KeyEvent;  /* 按键事件 */

typedef struct IODev{
    IODevType Type;
    void(*Init)(struct IODev *dev);
    int(*Write)(struct IODev *dev, unsigned char *buf, unsigned short len);
    int(*Read)(struct IODev *dev, unsigned char *buf, unsigned short len);
}IODev, *ptIODev;

ptIODev IODev_GetDev(IODevType type);

#endif /* __DEV_IO_H */
