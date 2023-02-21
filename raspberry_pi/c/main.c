/***************************************************************************************
 * Project  :
 * Experimental Platform :Raspberry Pi 4B + MCP23017 IO Expansion Module
 * Hardware Connection :Raspberry Pi 4B -> MCP23017 IO Expansion Module in wiringpi number
 *		3.3V --> VCC
 *		GND  --> GND
 *		SDA1 --> SDA 
 *		SCL1 --> SCL
 *      P0   --> INTA
 *      P1   --> INTB
 * Author	 : Andy Li
 * Web Site	 : www.seengreat.com
***************************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "mcp23017.h"

//Interrupt service function triggered by interrupt pin
void Int_callback(void)
{
    printf("portB:%02x\r\n", Read_gpio(PORTB));
}

int main(void)
{
	Mcp23017_Init();
	Set_port_dir(PORTA, OUTPUT);//config PORTA as output
    Set_port_dir(PORTB, INPUT);//config PORTA as input
    Set_io_pu(PORTB, PIN_ALL, ENABLE);//PORTB enable pullup
    //Set the interrupt mode of all pins of PORTB port to level change
    Set_io_int(PORTB, PIN_ALL, INT_CHANGE_LEVEL);
    //INT_EDGE_FALLING/INT_EDGE_RISING/INT_EDGE_BOTH/INT_EDGE_SETUP
    wiringPiISR(PIN_INTB, INT_EDGE_BOTH, Int_callback);// PIN INTB configuration
    printf("INTCAP portB:%02x\r\n", Read_intcap(PORTB));
    printf("portB:%02x\r\n", Read_gpio(PORTB));
    while(1)
    {
        printf("port A ouput high\r\n");
        //Set_gpio_pin(PORTA, PIN4, HIGH)
        Write_gpio(PORTA, 0xFF);
        //printf("portA:%02x\r\n",Read_gpio(PORTA));
        //printf("portB:%02x\r\n",Read_gpio(PORTB));
        delay(1000);
        printf("port A ouput low\r\n");
        //Set_gpio_pin(PORTA, PIN4, LOW);
        Write_gpio(PORTA, 0x00);
        //printf("portA:%02x\r\n",Read_gpio(PORTA));
        //printf("portB:%02x\r\n",Read_gpio(PORTB));
        delay(1000);		
	}
}
