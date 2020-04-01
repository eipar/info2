/*
 * lcd.c
 *
 *  Created on: 27/08/2014
 *      Author: Mariano
 */
//Nuestro código
#include "KitInfo2.h"
/*extern volatile uint32_t Demora_LCD;

void LCD_ESCRIBIR_DATO(uint8_t dato)
{
	//uint16_t i=0;

	//SetPin(PIN_RW,0);
	SetPin(PIN_RS,1);

	SetPin(PIN_D7,((dato>>7)&1));
	SetPin(PIN_D6,((dato>>6)&1));
	SetPin(PIN_D5,((dato>>5)&1));
	SetPin(PIN_D4,((dato>>4)&1));

	SetPin(PIN_EN,1);
	Demora_LCD = 10;
	while(Demora_LCD);
	SetPin(PIN_EN,0);
	//for(i=0;i<255;i++);
	//----------------------//

	SetPin(PIN_D7,((dato>>3)&1));
	SetPin(PIN_D6,((dato>>2)&1));
	SetPin(PIN_D5,((dato>>1)&1));
	SetPin(PIN_D4,((dato>>0)&1));

	SetPin(PIN_EN,1);
	Demora_LCD = 10;
	while(Demora_LCD);
	//for(i=0;i<255;i++);
	SetPin(PIN_EN,0);

}

void LCD_ESCRIBIR_FUNC(uint8_t dato)
{
	uint8_t Aux;

	//uint16_t i=0;

	//SetPin(PIN_RW,0);

	SetPin(PIN_RS,0);

	Aux = dato >> 7;
	SetPin(PIN_D7,(Aux&1));

	Aux = dato >> 6;
	SetPin(PIN_D6,((Aux)&1));

	Aux = dato >> 5;
	SetPin(PIN_D5,((Aux)&1));

	Aux = dato >> 4;
	SetPin(PIN_D4,((Aux)&1));

	SetPin(PIN_EN,1);
	//for(i=0;i<255;i++);
	SetPin(PIN_EN,0);
	//for(i=0;i<255;i++);

	// mando los 4 bits menos significativos

	Aux = dato >> 3;
	SetPin(PIN_D7,(Aux&1));

	Aux = dato >> 2;
	SetPin(PIN_D6,((Aux)&1));

	Aux = dato >> 1;
	SetPin(PIN_D5,((Aux)&1));

	Aux = dato >> 0;
	SetPin(PIN_D4,((Aux)&1));

	SetPin(PIN_EN,1);
	//for(i=0;i<255;i++);
	SetPin(PIN_EN,0);

}



void LCD_Inicializacion(void)
{
	//Inicializo los pines conectados al LCD, todos como gpio y salida


	SetFunc(PIN_RS,0);
	SetFunc(PIN_EN,0);
	SetFunc(PIN_BF,0);
	SetFunc(PIN_D4,0);
	SetFunc(PIN_D5,0);
	SetFunc(PIN_D6,0);
	SetFunc(PIN_D7,0);

	SetDir(PIN_D4,1);
	SetDir(PIN_D5,1);
	SetDir(PIN_D6,1);
	SetDir(PIN_D7,1);
	SetDir(PIN_RS,1);
	SetDir(PIN_BF,0);
	SetDir(PIN_EN,1);

	SetDir(PIN_D4,OFF);
	SetDir(PIN_D5,OFF);
	SetDir(PIN_D6,OFF);
	SetDir(PIN_D7,OFF);
	SetDir(PIN_RS,OFF);
	SetDir(PIN_BF,OFF);
	SetDir(PIN_EN,OFF);


	Demora_LCD=10;
	while(Demora_LCD);

	LCD_ESCRIBIR_FUNC(0X28);	// 4 bits
	LCD_ESCRIBIR_FUNC(0X0E);	// enciendo pantalla, enciende cursor y no parpadea
	LCD_ESCRIBIR_FUNC(0X01);	//clear display
	LCD_ESCRIBIR_FUNC(0X02);	// cursor al inicio de la pantalla

}

void LCD_ESCRIBIR_TEXTO(uint32_t pos,char *mensaje)
{
	uint8_t i=0;

	LCD_ESCRIBIR_FUNC(pos |(1<<7));
	for(i=0;mensaje[i]!='\0';i++)
	{
		LCD_ESCRIBIR_DATO(mensaje[i]);
	}
}*/

//Codigo Kuo

void InitLCD ( void )
{
	unsigned int i,j;

	//1.- Selecciono los bits del puerto como GPIOs y los direcciono:
	Select_PINSEL(LCD_D4_PORT,LCD_D4_PIN,PINSEL_GPIO);
	GPIO_Port(LCD_D4_PORT,LCD_D4_PIN,SALIDA);

	Select_PINSEL(LCD_D5_PORT,LCD_D5_PIN,PINSEL_GPIO);
	GPIO_Port(LCD_D5_PORT,LCD_D5_PIN,SALIDA);

	Select_PINSEL(LCD_D6_PORT,LCD_D6_PIN,PINSEL_GPIO);
	GPIO_Port(LCD_D6_PORT,LCD_D6_PIN,SALIDA);

	Select_PINSEL(LCD_D7_PORT,LCD_D7_PIN,PINSEL_GPIO);
	GPIO_Port(LCD_D7_PORT,LCD_D7_PIN,SALIDA);

	Select_PINSEL(LCD_RS_PORT,LCD_RS_PIN,PINSEL_GPIO);
	GPIO_Port(LCD_RS_PORT,LCD_RS_PIN,SALIDA);

	Select_PINSEL(LCD_E_PORT,LCD_E_PIN,PINSEL_GPIO);
	GPIO_Port(LCD_E_PORT,LCD_E_PIN,SALIDA);

	for( i = 0 ; i < 3 ; i++ )
	{
		LCD_E_OFF;

		for ( j = 0 ; j < 500000 ; j++ ); // 300000
		LCD_DATO(1,1,0,0);

		LCD_RS_OFF;
		LCD_E_ON;

		for( j = 0 ; j < 10000 ; j++ );//4500

		LCD_E_OFF;
	}

	LCD_E_OFF;

	for ( j = 0 ; j < 500000 ; j++ ); // 300000 flor demora

	LCD_DATO(0,1,0,0);

	LCD_RS_OFF;
	LCD_E_ON;

	for( j = 0 ; j < 10000 ; j++ );//4500

	LCD_E_OFF;

	// A partir de aca pasa a 4 bits
	Dato_LCD( 0x28 , LCD_CONTROL );
	Dato_LCD( 0x08 , LCD_CONTROL);	// display OFF
	Dato_LCD( 0x01 , LCD_CONTROL);	// clear display
	for( j = 0 ; j < 10000 ; j++ );	//delay por la instruccion clear display
	Dato_LCD( 0x06 , LCD_CONTROL);	// programo el LCD para mis necesidades
	Dato_LCD( 0x0C , LCD_CONTROL);	// display ON,sin cursor y blinking OFF del cursor

}

void Dato_LCD ( unsigned char data , unsigned char control )
{
	int q , i = 1;
	int data_d4,data_d5,data_d6,data_d7;

	do
	{
		data_d4 = ( data >> ( 0 + i * 4 ) ) & 0x01 ;
		data_d5 = ( data >> ( 1 + i * 4 ) ) & 0x01 ;
		data_d6 = ( data >> ( 2 + i * 4 ) ) & 0x01 ;
		data_d7 = ( data >> ( 3 + i * 4 ) ) & 0x01 ;

		LCD_DATO(data_d4,data_d5,data_d6,data_d7);
		//LCD_DATO(data_d7,data_d6,data_d5,data_d4);

		if( control == LCD_CONTROL )
			LCD_RS_OFF;
		else
			LCD_RS_ON;

		LCD_E_ON;
		for( q = 0 ; q < 400 ; q++ );
		LCD_E_OFF;
		for( q = 0 ; q < 14000 ; q++ );
	}
	while ( i--);
}

void Display_lcd( char *msg , char renglon , char posicion )
{
	unsigned char i ;

	if( renglon )
        posicion = posicion + 0xc0 ;
	else
		posicion = posicion + 0x80 ;

	Dato_LCD( posicion , LCD_CONTROL );
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		Dato_LCD( msg[ i ] , LCD_DATA );

}

void Select_PINSEL(uint8_t puerto, uint8_t pin, uint8_t modo)
{
	if(pin < 16){
			PINSEL[puerto*2] &= ~((uint32_t)3<<(pin*2));
			PINSEL[puerto*2] |= ((uint32_t)modo<<(pin*2));
		}
		else{
			PINSEL[(puerto*2)+1] &= ~((uint32_t)3<<(pin*2));
			PINSEL[(puerto*2)+1] |= ((uint32_t)modo<<(pin*2));
		}
}

void GPIO_Port(uint32_t port,uint32_t pin,uint8_t est)
{
	Select_PINSEL(port,pin,0);
	if(est){
		GPIOs[port].FIODIR |= ((uint32_t)1<<pin);

	}
	else{
		GPIOs[port].FIODIR &= ~((uint32_t)1<<pin);
	}
}

void GPIO_Set(uint32_t port,uint32_t pin,uint8_t est)	// Cuando est está en 1, lo setea
{
	if(est){
		GPIOs[port].FIOSET |= ((uint32_t)1<<pin);		// Poner 1
	}
	else{
		GPIOs[port].FIOCLR |= ((uint32_t)1<<pin);		// Poner 0
	}
}
