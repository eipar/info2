/*
 * rtc.h
 *
 *  Created on: 28/08/2014
 *      Author: Mariano
 */

#ifndef RTC_H_
#define RTC_H_

#include "KitInfo2.h"



// declaro registro del RTC faltantes

/*
#define CTIME0	(*( (uint32_t  *) 0x40024014UL))
#define CTIME1	(*( (uint32_t  *) 0x40024018UL))
#define AMR		(*( (uint32_t  *) 0x40024010UL))
#define CCR		(*( (uint32_t  *) 0x40024008UL))
#define ILR		(*( (uint32_t  *) 0x40024000UL))
#define CIIR	(*( (uint32_t  *) 0x4002400CUL))

#define ALMIN	(*( (uint32_t  *) 0x40024064UL))
#define ALHOUR	(*( (uint32_t  *) 0x40024068UL))
#define ALDOM	(*( (uint32_t  *) 0x4002406CUL))
#define ALMON	(*( (uint32_t  *) 0x40024078UL))
*/

typedef 	volatile uint32_t 		registro;
#define		RTC 			( ( registro  * ) 0x40024000UL )
//!< Miscellaneous registers
	#define		ILR			RTC[0]
	#define		CCR			RTC[2]
	#define		CIIR		RTC[3]
	#define		AMR			RTC[4]
	#define		RTC_AUX		RTC[23]
	#define		RTC_AUXEN	RTC[22]
	#define		CTIME0		RTC[5]
	#define		CTIME1		RTC[6]
	#define		CTIME2		RTC[7]

	//!< Time counter registers
	#define		SEC			RTC[8]
	#define		MIN			RTC[9]
	#define		HOUR		RTC[10]
	#define		DOM			RTC[11]
	#define		DOW			RTC[12]
	#define		DOY			RTC[13]
	#define		MONTH		RTC[14]
	#define		YEAR		RTC[15]
	#define		CALIBRATION	RTC[16]

	//!< General purpose registers
	#define		GPREG0		RTC[17]
	#define		GPREG1		RTC[18]
	#define		GPREG2		RTC[19]
	#define		GPREG3		RTC[20]
	#define		GPREG4		RTC[21]

	//!< Alarm register group
	#define		ALSEC		RTC[24]
	#define		ALMIN		RTC[25]
	#define		ALHOUR		RTC[26]
	#define		ALDOM		RTC[27]
	#define		ALDOW		RTC[28]
	#define		ALDOY		RTC[29]
	#define		ALMON		RTC[30]
	#define		ALYEAR		RTC[31]


//void Configurar_Alarma(void);
typedef struct BLA{
	uint8_t seg;
	uint8_t min;
	uint8_t hora;
	uint8_t dia_mes;
	uint8_t dia_semana;
	uint16_t dia_anio;
	uint8_t mes;
	uint16_t anio;
}RTC_HoraFecha;
void Init_RTC(void);
void RTC_SetHoraFecha(RTC_HoraFecha*);
void RTC_GetHoraFecha(RTC_HoraFecha*);
void RTC_SetAlarma(uint8_t,uint8_t);

volatile RTC_HoraFecha fechayhora_actual;


#endif /* RTC_H_ */
