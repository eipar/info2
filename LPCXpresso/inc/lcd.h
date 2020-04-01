/*
 * lcd.h
 *
 *  Created on: 28/08/2014
 *      Author: Mariano
 */

#ifndef LCD_H_
#define LCD_H_

#include "KitInfo2.h"

/*void LCD_ESCRIBIR_DATO(uint8_t dato);
void LCD_ESCRIBIR_FUNC(uint8_t dato);
void LCD_Inicializacion(void);
void LCD_ESCRIBIR_TEXTO(uint32_t pos,char *mensaje);


#define PIN_RS	2,6
#define PIN_BF	0,28
#define PIN_EN 	0,4
#define PIN_D4	0,5
#define PIN_D5	0,10
#define PIN_D6	2,4
#define PIN_D7	2,5
*/

//Codigo Kuo

#define		ALTO		1
#define 	BAJO		0
#define		ENTRADA		0
#define 	SALIDA		1
//GPIOS LCD:
#define		LCD_D4_PORT	0
#define		LCD_D4_PIN	5

#define		LCD_D5_PORT	0
#define		LCD_D5_PIN	10

#define		LCD_D6_PORT	2
#define		LCD_D6_PIN	4

#define		LCD_D7_PORT	2
#define		LCD_D7_PIN	5

#define		LCD_RS_PORT	2
#define		LCD_RS_PIN	6

#define		LCD_E_PORT	0
#define		LCD_E_PIN	4


// Controles de Comandos

#define		LCD_E_OFF				GPIO_Set(LCD_E_PORT,LCD_E_PIN,BAJO)
#define		LCD_E_ON				GPIO_Set(LCD_E_PORT,LCD_E_PIN,ALTO)
#define		LCD_RS_OFF				GPIO_Set(LCD_RS_PORT,LCD_RS_PIN,BAJO)
#define		LCD_RS_ON				GPIO_Set(LCD_RS_PORT,LCD_RS_PIN,ALTO)
#define		LCD_DATO(d4,d5,d6,d7)	GPIO_Set(LCD_D4_PORT,LCD_D4_PIN,d4);GPIO_Set(LCD_D5_PORT,LCD_D5_PIN,d5);GPIO_Set(LCD_D6_PORT,LCD_D6_PIN,d6);GPIO_Set(LCD_D7_PORT,LCD_D7_PIN,d7)

#define		LCD_CONTROL		1
#define		LCD_DATA		0


// Funciones LCD

void InitLCD ( void );
void Dato_LCD ( unsigned char data , unsigned char control );
void Display_lcd( char *msg , char renglon , char posicion );
void GPIO_Port(uint32_t port,uint32_t pin,uint8_t est);
void Select_PINSEL(uint8_t puerto, uint8_t pin, uint8_t modo);
void GPIO_Set(uint32_t port,uint32_t pin,uint8_t est);

#endif /* LCD_H_ */
