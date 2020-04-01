/*
 * adc.h
 *
 *  Created on: 03/09/2014
 *      Author: Mariano
 */

#ifndef ADC_H_
#define ADC_H_

#include "KitInfo2.h"

uint32_t ADCLeer(uint8_t canal);
void Inic_Adc(void);
uint32_t ADC_Conversion_Temp(uint32_t dato);
uint32_t ADC_Conversion_Hum(uint32_t dato);
uint32_t ADC_Conversion_Luz(uint32_t dato);

#define BUFER_TEMP AD0DR1
#define	BUFER_HUM AD0DR2
#define BUFER_LUZ AD0DR5
#define CANAL_TEMPERATURA 1
#define CANAL_HUMEDAD 2
#define CANAL_LUZ 5
extern volatile uint8_t FLAG_ADC;


#endif /* ADC_H_ */
