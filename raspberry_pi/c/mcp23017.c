#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <softPwm.h>
#include "mcp23017.h"

unsigned char i2c_fd;

void Mcp23017_Init(void)
{
    wiringPiSetup(); //init wiringpi lib
    pinMode(PIN_INTA, INPUT);  //INTA
    pullUpDnControl(PIN_INTA, PUD_UP);
    pinMode(PIN_INTB, INPUT);  //INTB
    pullUpDnControl(PIN_INTB, PUD_UP);
    i2c_fd = wiringPiI2CSetup(DEV_ADRR);
    printf("dev_addr:%d\r\n", i2c_fd);
}
//i2c bus write register
static void Write_reg(unsigned char reg, unsigned char value)
{
    wiringPiI2CWriteReg8(i2c_fd, reg, value );
}
//i2c bus read register
static unsigned char Read_reg(unsigned char reg)
{
    return wiringPiI2CReadReg8(i2c_fd, reg);
}
//Set the input and output direction of the port
void Set_port_dir(unsigned char port, unsigned char port_dir)
{
	if (port_dir == INPUT)
		Write_reg(IODIR+port, 0xFF);
	else if (port_dir == OUTPUT)
		Write_reg(IODIR+port, 0x00);
}
//Set the specified pin of the specified port to the input or output state
unsigned char Set_io_dir(unsigned char port, unsigned char pin, unsigned char pin_dir)
{
	unsigned char state;
	state = Read_reg(IODIR+port);
	if (pin_dir == INPUT)
	{
		state |= pin;
	}
	else if (pin_dir == OUTPUT)
	{
		state &= ~pin;
	}
	else 
	{
		printf("dir error!\r\n");
		return 0;
	}
	Write_reg(IODIR+port, state);
	return 1;
}
//Set whether the specified pin of the specified port turns on the pull-up resistance
unsigned char Set_io_pu(unsigned char port, unsigned char pin, unsigned char pu)
{
	unsigned char state;	
	state = Read_reg(GPPU+port);
	if (pu == ENABLE)
	{
		state |= pin;
	}
	else if (pu == DISABLE)
	{
		state &= ~pin;
	}
	else
	{
		printf("pu state error!\r\n");
		return 0;
	}
	Write_reg(GPPU+port, state);
	return 1;
}
//Set whether the specified pin of the specified port reverses the port polarity
unsigned char Set_io_polarty(unsigned char port, unsigned char pin, unsigned char polarity)
{
	unsigned char state;
	state = Read_reg(IPOL + port);
	if (polarity == ENABLE)
		state |= pin;
	else if (polarity == DISABLE)
		state &= ~pin;
	else
	{
		printf("polarity state error!\r\n");
		return 0;
	}
	Write_reg(IPOL + port, state);
	return 1;
}
//Set whether the interrupt function and interrupt type are enabled
//for the specified pin of the specified port
void Set_io_int(unsigned char port, unsigned char pin, unsigned char int_type)
{
	unsigned char inten_state;
	unsigned char defval_state;
	unsigned char intcon_state;
	inten_state = Read_reg(GPINTEN + port);
	defval_state = Read_reg(DEFVAL + port);
	intcon_state = Read_reg(INTCON + port);
	if (int_type == INT_DISABLE)
	{
		inten_state &= ~pin;
	}
	else if (int_type == INT_HIGH_LEVEL)
	{
		inten_state |= pin;
		defval_state &= ~pin;
		intcon_state |= pin;
	}
	else if (int_type == INT_LOW_LEVEL)
	{
		inten_state |= pin;
		defval_state |= pin;
		intcon_state |= pin;
	}
	else if (int_type == INT_CHANGE_LEVEL)
	{
		inten_state |= pin;
		intcon_state &= ~pin;
	}
	Write_reg(GPINTEN + port, inten_state);
	Write_reg(DEFVAL + port, defval_state);
	Write_reg(INTCON + port, intcon_state);
}
//Read the INTF register of the corresponding port 
unsigned char Read_intf(unsigned char port)
{
	return Read_reg(INTF + port);
}
//Read the INTCAP register of the corresponding port
unsigned char Read_intcap(unsigned char port)
{
	return Read_reg(INTCAP + port);
}
//Read the GPIO register of the corresponding port
unsigned char Read_gpio(unsigned char port)
{
	return Read_reg(GPIO + port);
}
//Read the OLAT register of the corresponding port
unsigned char Read_olat(unsigned char port)
{
	return Read_reg(OLAT + port);
} 
//Set the level of MCP23017 specified port
void Write_gpio(unsigned char port, unsigned char value)
{
	Write_reg(GPIO + port, value);
}
//Set the level of the specified pin of the specified port of MCP23017
void Set_gpio_pin(unsigned char port, unsigned char pin, unsigned char value)
{
	unsigned char gpio_state;
	gpio_state = Read_reg(GPIO + port);
	if (value == HIGH)
		gpio_state |= pin;
	else if (value == LOW)
		gpio_state &= ~pin;
	Write_reg(GPIO + port, gpio_state);
}

