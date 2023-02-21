/***************************************************************************************
 * Project  :MCP23017-IIC-STM32
 * Describe :Use IIC for I/O port expansion.
 * Experimental Platform :STM32F103C8T6 + MCP23017 IO Expansion Module
 * Hardware Connection :STM32f103 -> MCP23017 IO Expansion Module
 *			3V3	 ->	VCC					PB10 -> SCL
 *			GND	 ->	GND					PB11 -> SDA
 *			PB3	 ->	INTA        PB4	 ->	INTB
 * Library Version :ST_V3.5
 * Author		   :Andy Li
 * Web Site		 :www.seengreat.com
***************************************************************************************/
#include "sys.h"
#include "usart.h"
#include "gpio.h"
#include "delay.h"
#include "mcp23017.h"
#include "myiic.h"
#include "exti.h"

extern unsigned char int_flag;

int main(void)
{
		SystemInit();
		Uart1Init(115200,0,0);
		printf("\r\n---------- MCP23017 IO Expansion Module ----------\r\n");
		printf("STM32F103C8T6 ");
		printf("V1.0.0 Build 2022/11/29 09:22\r\n");

		delay_init();
		IIC_Init();
		Exti_Init();	

		Set_port_dir(PORTA, OUTPUT);//config PORTA as output
    Set_port_dir(PORTB, INPUT);//config PORTA as input
	  //printf("set io pu\r\n");
    Set_io_pu(PORTB, PIN_ALL, ENABLE);//PORTB enable pullup
	  //printf("set io int\r\n");
    //Set the interrupt mode of all pins of PORTB port to level change
    Set_io_int(PORTB, PIN_ALL, INT_CHANGE_LEVEL);
	  printf("INTCAP PORT B:%02x\r\n",Read_intcap(PORTB));

    while(1)
    {
        printf("port A ouput high\r\n");
        //Set_gpio_pin(PORTA, PIN4, HIGH)
        Write_gpio(PORTA, 0xFF);
			  
			  if(intb_flag == 1)
				{
           printf("ISR read port B:%02x\r\n",Read_gpio(PORTB));
					 intb_flag = 0;
				}
        delay_ms(1000);
        printf("port A ouput low\r\n");
        //Set_gpio_pin(PORTA, PIN4, LOW);
        Write_gpio(PORTA, 0x00);
			  if(intb_flag == 1)
				{
           printf("ISR read port B:%02x\r\n",Read_gpio(PORTB));
					 intb_flag = 0;
				}
        delay_ms(1000);		
	}
}

