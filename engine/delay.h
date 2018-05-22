#ifndef _DELAY_H_
#define _DELAY_H_

#include <time.h>
#include <stdint.h>

void delay_ms(uint32_t ms);
void delay_secs(uint32_t secs);
clock_t get_clock_ms();
uint32_t clock_diff_ms(clock_t ms1, clock_t ms2);

#endif
