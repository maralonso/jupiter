#include "delay.h"

#define CLOCKS_PER_MS    (CLOCKS_PER_SEC / 1000)

void delay_ms(uint32_t ms)
{
    clock_t clk = clock();
    while (((clock() - clk) / CLOCKS_PER_MS < ms));
}

void delay_secs(uint32_t secs)
{
    clock_t clk = clock();
    while (((clock() - clk) / CLOCKS_PER_SEC < secs));
}

clock_t get_clock_ms()
{
    return clock() / CLOCKS_PER_MS;
}

uint32_t clock_diff_ms(clock_t ms1, clock_t ms2)
{
    return (uint32_t) (ms1 -ms2);
}
