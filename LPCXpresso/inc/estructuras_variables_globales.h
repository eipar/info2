/*
 * estructuras_globales.h
 *
 *  Created on: 29/07/2014
 *      Author: Proyecto Invernadero
 */

#ifndef ESTRUCTURAS_GLOBALES_H_
#define ESTRUCTURAS_GLOBALES_H_

typedef struct
{
	uint8_t temp_min;
	uint8_t temp_max;
	uint8_t humedad_max;
	uint8_t humedad_min;
	uint8_t iluminacion;
	uint8_t riego_inicio_hora;
	uint8_t riego_inicio_mins;
	uint8_t riego_duracion;


}struct_cultivo;

typedef struct
{
	uint8_t temperatura;
	uint8_t humedad;
	uint8_t luz;

}struct_invernadero;

extern volatile uint32_t contador;
extern volatile uint32_t contador_segundos;
extern volatile uint32_t contador_minutos;
extern volatile uint32_t contador_horas;
extern volatile uint32_t contador_riego;
extern volatile uint8_t flag_10segs;
extern volatile uint8_t estado_temperatura;
extern volatile uint8_t estado_humedad_suelo;
extern volatile uint8_t estado_humedad_ambiente;
extern volatile struct_invernadero invernadero;
extern volatile struct_cultivo cultivo;
extern volatile struct_cultivo buffer_cultivo;
extern volatile uint8_t alarma;
extern volatile uint32_t contador_rehabilitacion_alarma;
extern volatile uint8_t flag_riego;

// ADC
volatile uint8_t canales[3];

#define ESTABLE 0
#define FRIO 1
#define CALOR 2
#define SECO 1
#define HUMEDO 2

// defines-variables para el manejo del adc
#define POSITIVO 1
#define NEGATIVO 0
extern volatile uint8_t flag_conv_temp;
extern volatile uint8_t indice_adc;
extern volatile uint8_t flag_dato;

//Defines Maquina Receptora de Datos
#define REPOSO0 0
#define REPOSO1 1
#define REPOSO2 2
#define REPOSO3 3
#define REPOSO4 92
#define REPOSO_CARACTER_ESPECIAL 80
#define RECIBIENDO_TEMP_MAX 4
#define RECIBIENDO_TEMP_MIN 5
#define RECIBIENDO_HUMEDAD 6
#define RECIBIENDO_HUM_MAX 7
#define RECIBIENDO_HUM_MIN 8
#define RECIBIENDO_ILUMINACION 9
#define RECIBIENDO_ILUMINACION_HORAS 10
#define RECIBIENDO_RIEGO 11
#define RECIBIENDO_RIEGO_INICIO_HORA 12
#define RECIBIENDO_RIEGO_INICIO_MINS 13
#define RECIBIENDO_RIEGO_DURACION 14

// Defines para la Maquina de estado RX de prueba ( prueba de hardware), la trama la recibo desde el qt
#define PRIMER_CARACTER 1
#define SEGUNDO_CARACTER 2
#define TERCER_CARACTER 3
#define CUARTO_CARACTER 4
#define QUINTO_CARACTER 5
#define SEXTO_CARACTER 6
#define SEPTIMO_CARACTER 7
#define OCTAVO_CARACTER 8
#define NOVENO_CARACTER 9
#define DECIMO_CARACTER 10
#define DECIMOPRIMERO_CARACTER 11
#define DECIMOSEGUNDO_CARACTER 12
#define ESTADO_NO_PRUEBA 1
#define ESTADO_PRUEBA 0
#define DEMORA_SEGUNDOS 3

extern volatile uint8_t Demora_Prueba;
uint8_t  flag_bloqueo;


extern volatile uint8_t flag_rx;

#define DATO_NUEVO 1
#define DATO_VIEJO 0
extern volatile uint8_t FLAG_DATO;

#define VALIDO 1
#define INVALIDO 0

extern uint8_t dato_rx;

//Defines Limites para verificar los datos
#define TEMP_LIM_MIN 0
#define TEMP_LIM_MAX 200
#define HUM_LIM_MAX 110
#define HUM_LIM_MIN 0
#define LUZ_LIM_MAX 24
#define LUZ_LIM_MIN 0
#define RIEGO_LIM_MAX 60
#define RIEGO_LIM_MIN 0

// variable Global RTC



#endif /* ESTRUCTURAS_GLOBALES_H_ */
