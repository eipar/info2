/*
 * rtc.c
 *
 *  Created on: 28/08/2014
 *      Author: Mariano
 */
#include "KitInfo2.h"

volatile uint8_t alarma = 0;

void Init_RTC(void)
{
	PCONP|=(1<<9);
	ILR = 0x00;
	CIIR = 0x00;
	AMR = 0xFF;
	CALIBRATION = 0x00;
	CCR = 0x01;
	// HABILITACION INTERRUPCION POR ALARMA
	AMR &=~(0x6);		//se desenmascara el bit de alarma pedido
	ILR = 0x02;			//limpio flag de interrupcion
	ISER0 |= 1<<17;		//habilito interrupcion desde el NVIC

}

void RTC_IRQHandler(void)
{

	if((ILR & (0x02)) != 0)
	{
		if(alarma == 0)
		{
		alarma = 1;

		}
	}
	AMR = 0xFF; // deshabilito interrupcion por Alarma
	ILR = 0x02;// limpio flag de interrupcion

}

/*void Configurar_Alarma(void)
{
	ALMIN = cultivo.riego_inicio_mins;
	ALHOUR = cultivo.riego_inicio_hora;
}*/


void RTC_SetHoraFecha(RTC_HoraFecha* horafecha)
{
	SEC = horafecha->seg;
	MIN = horafecha->min;
	HOUR = horafecha->hora;
	DOM = horafecha->dia_mes;
	DOW = horafecha->dia_semana;
	DOY = horafecha->dia_anio;
	MONTH = horafecha->mes;
	YEAR = horafecha->anio;
}

void RTC_GetHoraFecha(RTC_HoraFecha* horafecha)
{
	horafecha->seg = SEC;
	horafecha->min = MIN;
	horafecha->hora = HOUR;
	horafecha->dia_mes = DOM;
	horafecha->dia_semana = DOW;
	horafecha->dia_anio = DOY;
	horafecha->mes = MONTH;
	horafecha->anio = YEAR;
}

void RTC_SetAlarma(uint8_t hora,uint8_t min)
{
	ALHOUR = hora;
	ALMIN = min;
}

