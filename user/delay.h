#ifndef _DELAY_H_
#define _DELAY_H_
#include<stm32f10x.h>
void delay_init(u8 SYSCLK);
void delay_ms(u32 ms);
void delay_us(u32 us);
#endif
