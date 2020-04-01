/*
 * funciones_mias.c
 *
 *  Created on: 14/04/2014
 *      Author: Mariano
 */


#include "KitInfo2.h"




// funciones hechas por mi
void SetPin(uint8_t  port, uint8_t pin,uint8_t value)
{
	switch(port)
	{
	case 0:
		if( value == 0)
		{
			FIO0CLR |= (1<<pin);
		}
		else
		{
			FIO0SET |=(1<<pin);
		}
		break;
	case 1:
			if( value == 0)
			{
				FIO1CLR |= (1<<pin);
			}
			else
			{
				FIO1SET |=(1<<pin);
			}
			break;
	case 2:
				if( value == 0)
				{
					FIO2CLR |= (1<<pin);
				}
				else
				{
					FIO2SET |=(1<<pin);
				}
				break;
	case 3:
					if( value == 0)
					{
						FIO3CLR |= (1<<pin);
					}
					else
					{
						FIO3SET |=(1<<pin);
					}
					break;
	default:
		break;
	}

}

void SetDir(uint8_t  port, uint8_t pin,uint8_t mode)
{
switch(port)
{
case 0:
	FIO0DIR &= ~(0x03 <<pin);
	FIO0DIR |= (mode << pin);
	break;
case 1:
	FIO1DIR &= ~(0x03 <<pin);
	FIO1DIR |= (mode << pin);
	break;
case 2:
	FIO2DIR &= ~(0x03 <<pin);
	FIO2DIR |= (mode << pin);
	break;
case 3:
	FIO3DIR &= ~(0x03 <<pin);
	FIO3DIR |= (mode << pin);
	break;
case 4:
	FIO4DIR &= ~(0x03 <<pin);
	FIO4DIR |= (mode << pin);
	break;
default:
	break;
}
}

void SetFunc(uint8_t  port, uint8_t pin,uint8_t function)
{
	switch(port)
	{
	case 0:
		if(pin >= 16)
		{
			pin -=16;
			PINSEL1 &= ~(0x03 <<(pin*2));
			PINSEL1 |= (function << (pin*2));
		}
		else
		{
			PINSEL0 &= ~(0x03 <<(pin*2));
			PINSEL0 |= (function << (pin*2));
		}
		break;
	case 1:
		if(pin >= 16)
				{
					pin -=16;
					PINSEL3 &= ~(0x03 <<(pin*2));
					PINSEL3 |= (function << (pin*2));
				}
				else
				{
					PINSEL2 &= ~(0x03 <<(pin*2));
					PINSEL2 |= (function << (pin*2));
				}
		break;
	case 2:
		if(pin >= 16)
				{
					pin -=16;
					PINSEL5 &= ~(0x03 <<(pin*2));
					PINSEL5 |= (function << (pin*2));
				}
				else
				{
					PINSEL4 &= ~(0x03 <<(pin*2));
					PINSEL4 |= (function << (pin*2));
				}
		break;
	case 3:
		if(pin >= 16)
				{
					pin -=16;
					PINSEL7 &= ~(0x03 <<(pin*2));
					PINSEL7 |= (function << (pin*2));
				}
				else
				{
					PINSEL6 &= ~(0x03 <<(pin*2));
					PINSEL6 |= (function << (pin*2));
				}
		break;
	case 4:
			if(pin >= 16)
					{
						pin -=16;
						PINSEL9 &= ~(0x03 <<(pin*2));
						PINSEL9 |= (function << (pin*2));
					}
					else
					{
						PINSEL8 &= ~(0x03 <<(pin*2));
						PINSEL8 |= (function << (pin*2));
					}
			break;
	default: break;
	}
}

uint8_t GetPin(uint8_t  port, uint8_t pin)
{
	switch(port)
	{
	case 0:
		return (FIO0PIN & (0x01<<pin)>>pin);
		break;
	case 1:
		return ((FIO1PIN & (0x01<<pin) )>>pin);
		break;
	case 2:
			return ((FIO2PIN & (0x01<<pin))>>pin);
			break;
	case 3:
			return ((FIO3PIN & (0x01<<pin))>>pin);
			break;
	case 4:
			return ((FIO4PIN & (0x01<<pin))>>pin);
			break;
	default:
		return ERROR;
		break;
	}
return ERROR;
}

// mismas funciones hechas en clase
/*
uint8_t GPIO_Leer(uint8_t port, uint8_t pin)
{
	return (((GPIOs[port]->FIOPIN) &= (0x01 << pin) )>>pin);
}
*/
//

