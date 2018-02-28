#include<stm32f10x.h>
#include "delay.h"

#define SCLK(a) if(a) GPIOA->BSRR = 1; else GPIOA->BRR = 1
#define RCLK(a) if(a) GPIOA->BSRR = 1<<1; else GPIOA->BRR = 1<<1;
#define DIO(a)	if(a) GPIOA->BSRR = 1<<2; else GPIOA->BRR = 1<<2;

void Config_GPIO(void);

int main(void)
{
	u32 i,j;
	u16 data = 0x8080;
	u8 r;
	
	delay_init(72);
	Config_GPIO();

	while(1)
	{
		RCLK(0);
		for(j = 0; j < 64;j++)
		{
			r = (j / 8)+1;
			data = (1 << (7 - r-1));
			data = data << 8;
			data = data | (1 << (7-(j % 8+1)));
			
				for( i = 0 ; i < 16 ; i++)
			{
				
				if((data >> i) & 0x0001)
				{
					DIO(1);
				}	
				else
				{
					DIO(0);
				}
					
				SCLK(0);
				SCLK(1);
			}
			
			RCLK(0);
			RCLK(1);
			
			delay_ms(500);
			
		}
		
		
		
	}
}

void Config_GPIO()
{
	GPIO_InitTypeDef GPIO_Init_Type_Struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_Init_Type_Struct.GPIO_Pin  	= GPIO_Pin_All;
	GPIO_Init_Type_Struct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init_Type_Struct.GPIO_Mode 	= GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOB,&GPIO_Init_Type_Struct);
	GPIO_Init(GPIOC,&GPIO_Init_Type_Struct);
	
	GPIO_Init_Type_Struct.GPIO_Pin 		= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init_Type_Struct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init_Type_Struct.GPIO_Mode 	= GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOA,&GPIO_Init_Type_Struct);
	
}
