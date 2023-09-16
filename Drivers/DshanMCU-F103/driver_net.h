#ifndef __DRIVER_NET_H
#define __DRIVER_NET_H

#include "stm32f1xx_hal.h"

int Net_Init(void);
int Net_TransmitSocket(const char *socket, int len, int timeout);
int Net_RecvSocket(char *buf, int len, int timeout);
int Net_ConnectWiFi(const char *ssid, const char *pwd, int timeout);
int Net_DisconnectWiFi(void);
int Net_ConnectTCP(const char *ip, int port, int timeout);
int Net_Disconnect_TCP_UDP(void);
void NetDataProcess_Callback(uint8_t data);

#endif /* __DRIVER_NET_H */

