/*
 * KitInfo2.h
 *
 *  Created on: 17/04/2012
 *      Author: Mica y Chor
 */

#ifndef KIT_INFO2_H_
#define KIT_INFO2_H_

	#include <cr_section_macros.h>
	#include "systick.h"
	#include "gpio.h"
	#include "Regs.h"
	#include "KitInic.h"
	#include "Info2_cortexM3Uart.h"
	#include "estructuras_variables_globales.h"
	#include "lcd.h"
	#include "adc.h"
	#include "maquinas.h"
	#include "rtc.h"

	//******agregue aquí debajo los includes propios de su aplicación.
	//#include.............
	//#include.............
	//******

	//Leds (Reles)
	#define		LED1		PORT2,0 		//GPIO2
	#define		LED2		PORT0,23		//GPIO0
	#define		LED3		PORT0,21		//GPIO0
	#define		LED4		PORT0,27		//GPIO0

	//Led RGB:
	#define		RGBR		2,1			//GPIO2
	#define		RGBG		2,2			//GPIO2
	#define		RGBB		2,3			//GPIO2
	#define		BUZZ		PORT0,28		//GPIO0

	//Teclas (teclado 4x1)
	#define		KEY0		PORT2,10		//GPIO2
	#define		KEY1		PORT0,18		//GPIO0
	#define		KEY2		PORT0,11		//GPIO0
	#define		KEY3		PORT2,13		//GPIO2

	#define		KEY_RC		PORT1,26		//GPIO1

	//Entradas digitales:
	#define		IN0			PORT4,29	//GPIO4
	#define		IN1			PORT2,11	//GPIO2

	//GPIOS LCD:
	#define		LCD_D4		PORT0,5			//GPIO0
	#define		LCD_D5		PORT0,10		//GPIO0
	#define		LCD_D6		PORT2,4			//GPIO2
	#define		LCD_D7		PORT2,5			//GPIO2

	#define		LCD_RS		PORT2,6			//GPIO2
	#define		LCD_BF		PORT0,28		//GPIO1
	#define		LCD_E		PORT0,4			//GPIO0

	//salidas
	#define		COOLER_IN	0,27
	#define		COOLER_OUT	0,21
	#define		LAMPARA		0,23
	#define		CALEFACTOR	0,22
	#define		REGADOR		2,0
	// botones de entrada
	#define BOTON_PRUEBA 2,10
	#define BOTON_BLOQUEO 1,26
	#define BOTON_DESBLOQUEO 2,13

	//Identificación de los puertos de expansion:
	#define EXPANSION0		PORT2,7
	#define EXPANSION1		PORT1,29
	#define EXPANSION2		PORT4,28
	#define EXPANSION3		PORT1,23
	#define EXPANSION4		PORT1,20
	#define EXPANSION5		PORT0,19
	#define EXPANSION6		PORT3,26
	#define EXPANSION7		PORT1,25
	#define EXPANSION8		PORT1,22
	#define EXPANSION9		PORT1,19
	#define EXPANSION10		PORT0,20
	#define EXPANSION11		PORT3,25
	#define EXPANSION12		PORT1,27
	#define EXPANSION13		PORT1,24
	#define EXPANSION14		PORT1,21
	#define EXPANSION15		PORT1,18
	#define EXPANSION16		PORT1,31
	#define EXPANSION17		PORT0,24
	#define EXPANSION18		PORT0,25
	#define EXPANSION19		PORT0,17
	#define EXPANSION20		PORT1,31
	#define EXPANSION21		PORT0,22
	#define EXPANSION22		PORT0,15
	#define EXPANSION23		PORT0,16
	#define EXPANSION24		PORT2,8
	#define EXPANSION25		PORT2,12
	#define EXPANSION26		PORT1,31
	#define EXPANSION27		PORT1,31


	//Defines generales:
	#define		OFF		0
	#define		ON		1

	#define		BUZZ_ON		0
	#define		BUZZ_OFF	1


	//Valores para configuracion del PLL:
	#define CLOCK_SETUP_Value 	    1
	#define SCS_Value				0x00000020
	#define CLKSRCSEL_Value         0x00000001
	#define PLL0_SETUP_Value        1
	#define PLL0CFG_Value           0x00050063
	#define PLL1_SETUP_Value        1
	#define PLL1CFG_Value           0x00000023
	#define CCLKCFG_Value           0x00000003
	#define USBCLKCFG_Value         0x00000000
	#define PCLKSEL0_Value          0x00000000
	#define PCLKSEL1_Value          0x00000000
	#define PCONP_Value             0x042887DE
	#define CLKOUTCFG_Value         0x00000000
	#define FLASHCFG_Value			0x00004000

#endif /* KIT_INFO2_H_ */
