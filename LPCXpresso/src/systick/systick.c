/*
 * systick.c
 *
 *  Created on: 29/07/2014
 *      Author: Mariano
 */

#include "systick.h"


volatile uint32_t contador=0;
volatile uint32_t contador_segundos= 0;
volatile uint32_t contador_minutos= 0;
volatile uint32_t contador_horas= 0;
volatile uint8_t flag_10segs= 0;
volatile uint32_t Demora_LCD=0;
volatile uint32_t contador_riego;
volatile uint32_t contador_rehabilitacion_alarma = 0;

void Init_Systick(void)
{
	STCURR = 0;                       	// Reseteo el timer
	STRELOAD  = (STCALIB)-1;
	STCTRL |= 7;

}



void SysTick_Handler(void)	// 10 ms
{

	contador++;


	if(contador >= 100)
	{
		Demora_Prueba--;

		contador_segundos++;
		contador = 0;
		flag_10segs++;
		FLAG_ADC=1;
		contador_riego++;	// contador para regar por un cierto tiempo
		// ADC
		/*AD0CR &=~(0xFF);
		AD0CR |=(1<<5);//canales[5]);
		AD0CR |=(1<<24);	// disparo conversion
		AD0CR &=~(0x07<<24);*/
	}
	if(contador_segundos >= 60)
	{

		contador_minutos++;
		contador_rehabilitacion_alarma++;	// contador para deshabilitar la alarma x 2 mins por problemas en el RTC Handler
		contador_segundos = 0;


	}
	if(contador_minutos >= 60)
	{
		contador_horas++;
		contador_minutos = 0;
	}
	if(contador_horas >= 24)
		{
			contador_horas = 0;
		}

	if(Demora_LCD)
	{
		Demora_LCD--;
	}
	if((((contador_riego)/60) == cultivo.riego_duracion) && (flag_riego == ON))	// si se cumplio el tiempo de riego:
		{
			contador_riego=0;	// reseteo contador
			flag_riego = OFF;	// desactivo flag
			SetPin(REGADOR,OFF);	// apago Regador
		}


}

