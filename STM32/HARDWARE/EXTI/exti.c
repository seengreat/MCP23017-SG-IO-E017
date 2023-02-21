
#include "exti.h"
#include "gpio.h"
#include "delay.h"
#include "mcp23017.h"
#include "usart.h"

unsigned char inta_flag=0;
unsigned char intb_flag=0;

void Exti_Init(void)
{
   	EXTI_InitTypeDef EXTI_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;

    IO_Init();

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3 | EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure); 
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI3_IRQHandler(void)
{
	  if(EXTI_GetITStatus(EXTI_Line3)==SET)
		{
				if(inta_flag == 0)
				{
					 inta_flag = 1;
				}	
				EXTI_ClearITPendingBit(EXTI_Line3);
		}
}

void EXTI4_IRQHandler(void)
{
	  if(EXTI_GetITStatus(EXTI_Line4)==SET)
		{
				if(intb_flag == 0)
				{
					 intb_flag = 1;
				}	
				EXTI_ClearITPendingBit(EXTI_Line4);
		}
}
