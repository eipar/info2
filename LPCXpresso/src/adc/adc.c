/*
 * adc.c
 *
 *  Created on: 27/08/2014
 *      Author: Mariano
 */
#include "KitInfo2.h"

#define CANT_CANALES 3
#define CUENTAS_LIMITE 324
#define NIVEL_LUZ 1000

volatile uint8_t FLAG_ADC=0;
volatile uint8_t canales[CANT_CANALES]={1,2,5};//CANAL_TEMPERATURA,1,4};
uint32_t BUFFER_ADC[CANT_CANALES];
volatile uint8_t flag_conv_temp;
volatile uint8_t indice_adc=4; // falta inicializar con primer canal para lectura
// Rango de Temperaturas : -32,4° a 70° , la resolucion es de 0,1

void Inic_Adc(void)
{
	PCONP |= (1<<12);		// enciendo adc
	PCLKSEL0 &=~(0x03<<24);	//seleccion de clock/4
	AD0CR |= (1<<9);
	//PCLKSEL0 |=(1<<25);
	//Configuracion de pines
	//Estan ordenados del AD0.0 al AD0.7
	//SetFunc(0,23,1);	//CANAL 0
	SetFunc(0,24,1);	//CANAL 1 TEMPERATURA TEC2
	SetFunc(0,25,1);	//CANAL 2 HUMEDAD TEC3
	//SetFunc(0,26,1);*/	//CANAL 3
	//SetFunc(1,30,3);	//CANAL 4
	SetFunc(1,31,3); //CANAL 5 LUZ TEC1
	//SetFunc(0,2,2); // canal 6 , no se puede usar por el UART0
	//SetFunc(0,3,2);
	// Habilito Interrupcion
	//ISER0 |=(1<<22);
	AD0CR &=~(0xFF);
	AD0CR |=(1<<5) |(1<<1) |(1<<2);	// 	que canales voy a utilizar (5)
	//AD0INTEN |= (1<<5);	// habilitar la interrupcion de cada canal (5)
	// prendo PDN = 1
	AD0CR |=(1<<21);
	// desactivo modo BURST ( rafaga)
	//AD0CR &=~(1<<16);
	// activo modo BURST
	AD0CR |= (1<<16);
	AD0CR &= ~(0x07<<24);
	// para configurar el modo de disparo
	// bits 24,25,26
	//AD0CR |=(1<<24); // un disparo simple
	//BUFFER_ADC[4] = AD0GDR;
}


/*void ADC_IRQHandler(void)
{

	//static uint8_t indice=0;	// indice inicializo con el primer canal a leer
	uint32_t temp=0;
	//temp = AD0GDR;
	temp = AD0DR5;
	temp = temp>>4;
	temp = (temp & 0xFFF);
	BUFFER_ADC[5] = temp;
	//indice_adc++;
	if(indice>=CANT_CANALES)
	{
		indice=0;
	}

}*/

uint32_t ADCLeer(uint8_t canal)
{
	//uint32_t dato=BUFFER_ADC[canal];
	uint32_t aux_buffer=0;
	//temp = AD0GDR;


	switch(canal)
	{
	case CANAL_HUMEDAD:
		// codigo que hay que poner adentro de cada canal , por ejemplo al de humedad le puse AD0.5
		aux_buffer = BUFER_HUM;
		aux_buffer = aux_buffer>>4;
		aux_buffer = (aux_buffer & 0xFFF);
		aux_buffer = ADC_Conversion_Hum(aux_buffer);
		break;
	case CANAL_TEMPERATURA:
		aux_buffer = BUFER_TEMP;
		aux_buffer = aux_buffer>>4;
		aux_buffer = (aux_buffer & 0xFFF);
		aux_buffer = ADC_Conversion_Temp(aux_buffer);
		break;
	case CANAL_LUZ:
		aux_buffer = BUFER_LUZ;
		aux_buffer = aux_buffer>>4;
		aux_buffer = (aux_buffer & 0xFFF);
		aux_buffer = ADC_Conversion_Luz(aux_buffer);
		break;
	default:
		return -1;
		break;
	}
	return aux_buffer;
}

uint32_t ADC_Conversion_Temp(uint32_t dato)
{
	dato= dato/41;

	return dato;
}
uint32_t ADC_Conversion_Hum(uint32_t dato)
{
	dato = (dato/100)+60;
	return dato;
}

uint32_t ADC_Conversion_Luz(uint32_t dato)
{
	if(dato>=NIVEL_LUZ)
	{
		dato=1;
	}
	else
	{
		dato=0;
	}
	return dato;
}
