#include "delay.h"

void delay_50ms()
{
    os_delay_us(50000);
}

// n 为毫秒数，必须为50的整数倍
void delay_50x_ms(uint16_t n)
{
    for (uint16_t i = 0; i < (n / 50); i++)
    {
        delay_50ms();
    }
}