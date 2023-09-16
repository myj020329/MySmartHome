
#ifndef _DRIVER_DHT11_H
#define _DRIVER_DHT11_H


void DHT11_Init(void);


int DHT11_Read(int *hum, int *temp);


void DHT11_Test(void);


#endif /* _DRIVER_DHT11_H */

