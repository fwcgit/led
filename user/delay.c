#include"delay.h"

static u8  fac_us;
static u16 fac_ms;

void delay_init(u8 SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	
	fac_us = SYSCLK / 8 ;
	fac_ms = (u16)fac_us * 1000;
}

void delay_us(u32 us)
{
	
	u32 temp;
	
	SysTick->LOAD = (u32)fac_ms * us;
	SysTick->VAL	= 0x00;
	SysTick->CTRL	= 0x01;
	
	do{
		
		temp = SysTick->CTRL;
		
	}while(temp & 0x01 && !(temp & (1 << 16))); // �жϿ������������Ҽ���������0
	
	SysTick->CTRL  = 0x00;//�رռ�����
	SysTick->LOAD = 0x00;//��ռ�����
	
}

void delay_ms(u32 ms)
{
	u32 temp;
	
	SysTick->LOAD = fac_ms * ms;
	SysTick->VAL	= 0x00;
	SysTick->CTRL	= 0x01;
	
	do{
		
		temp = SysTick->CTRL;
		
	}while(temp & 0x01 && !(temp & (1 << 16))); // �жϿ������������Ҽ���������0
	
	SysTick->CTRL  = 0x00;//�رռ�����
	SysTick->LOAD = 0x00;//��ռ�����
}
