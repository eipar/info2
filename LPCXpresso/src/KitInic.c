/*
 * KitInic.c
 *
 *  Created on: 17/04/2012
 *      Author: Mica y Chor
 */

#include "KitInfo2.h"

void InicializarKit ( void )
{

	InitPLL();
	Init_Systick();
	InitLCD();
	UART0_Init(9600);
	Inic_Adc();
	Init_RTC();


	// APAGO RGB
	SetDir(2,1,1);
	SetDir(2,2,1);
	SetDir(2,3,1);
	//RGB OFF
	SetPin(2,1,0);	// verde
	SetPin(2,2,0); // rojo
	SetPin(2,3,0);	// azul

	SetDir(0,22,1);
	SetFunc(BOTON_BLOQUEO,0);
	SetDir(BOTON_BLOQUEO,ENTRADA);
	SetDir(BOTON_PRUEBA,ENTRADA);
	SetDir(BOTON_DESBLOQUEO,ENTRADA);
	/*
	// Configuracion del P0.18 para que me interrumpa cada vez que presiono
	SetFunc(0,18,01);	// P0.18 como EINT0
	SetFunc(2,10,01);	// P2.10 como EINT0
	SetFunc(2,13,01);	// P2.13 como EINT3
	ISER0 |= (1<18) |(1<<21); 	// habilito interrupcion por EINT0 e EINT3
	IO0IntEnR |= (0x01<<18); // habilito interrupcion por Flanco Ascendente
	IO2IntEnR |=(0x01<<10) |(0x01<<13); // habilito interrupcion por Flanco Ascendente
	*/



	//lamparas
	SetFunc(LAMPARA,0);
	SetDir(LAMPARA,SALIDA);


	//coolers
	SetFunc(COOLER_IN,0);
	SetDir(COOLER_IN,SALIDA);
	SetFunc(COOLER_OUT,0);
	SetDir(COOLER_OUT,SALIDA);

	//calefactor
	SetFunc(CALEFACTOR,0);
	SetDir(CALEFACTOR,SALIDA);

	//regador
	SetFunc(REGADOR,0);
	SetDir(REGADOR,SALIDA);
}


void InitPLL(void)
{

	SCS       = SCS_Value;

	if (SCS_Value & (1 << 5))               /* If Main Oscillator is enabled      */
		while ((SCS & (1<<6)) == 0);/* Wait for Oscillator to be ready    */

	CCLKCFG   = CCLKCFG_Value;      /* Setup Clock Divider                */

	PCLKSEL0  = PCLKSEL0_Value;     /* Peripheral Clock Selection         */
	PCLKSEL1  = PCLKSEL1_Value;

	CLKSRCSEL = CLKSRCSEL_Value;    /* Select Clock Source for PLL0       */

	PLL0CFG   = PLL0CFG_Value;      /* configure PLL0                     */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	PLL0CON   = 0x01;             /* PLL0 Enable                        */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & (1<<26)));/* Wait for PLOCK0                    */

	PLL0CON   = 0x03;             /* PLL0 Enable & Connect              */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

	PLL1CFG   = PLL1CFG_Value;
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	PLL1CON   = 0x01;             /* PLL1 Enable                        */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & (1<<10)));/* Wait for PLOCK1                    */

	PLL1CON   = 0x03;             /* PLL1 Enable & Connect              */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */

	PCONP     = PCONP_Value;        /* Power Control for Peripherals      */

	CLKOUTCFG = CLKOUTCFG_Value;    /* Clock Output Configuration         */

	FLASHCFG  = (FLASHCFG & ~0x0000F000) | FLASHCFG_Value;
}


