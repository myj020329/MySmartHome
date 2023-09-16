
#ifndef _DRIVER_TIMER_H
#define _DRIVER_TIMER_H

#include <stdint.h>

void udelay(int us);

void mdelay(int ms);

uint64_t system_get_ns(void);


#endif /* _DRIVER_TIMER_H */

