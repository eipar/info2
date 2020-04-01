/*
 * Maquina_estados.c
 *
 *  Created on: 29/07/2014
 *      Author: Mariano
 */

#include "KitInfo2.h"

volatile uint8_t estado_temperatura = 0;
volatile uint8_t estado_humedad = 0;
volatile struct_invernadero invernadero;
volatile struct_cultivo cultivo;
volatile struct_cultivo buffer_cultivo;
volatile uint8_t flag_dato = INVALIDO;
volatile uint8_t flag_iluminacion;
volatile uint8_t flag_rx = ESTADO_NO_PRUEBA;
volatile uint8_t Demora_Prueba;
uint8_t dato_rx;
volatile uint8_t FLAG_DATO;
uint8_t first_time = 0;
volatile uint8_t flag_riego = 0;
/*Maquina_Temperatura y Maquina Humedad es una maquina de estados para manipular las variable globales estado_temperatura
 y estado_humedad  que me indica en que condiciones esta la temp y humedad en el invernadero */
void Maquina_Temperatura(void)
{
	switch(estado_temperatura)
	{
	case ESTABLE:
		if(invernadero.temperatura > cultivo.temp_max)
		{
			estado_temperatura = CALOR;
		}
		if(invernadero.temperatura < cultivo.temp_min)
		{
			estado_temperatura = FRIO;
		}
		break;
	case CALOR:

		if(invernadero.temperatura <= cultivo.temp_max)
			{
				estado_temperatura = ESTABLE;
			}
		break;
	case FRIO:

		if(invernadero.temperatura >= cultivo.temp_min)
			{
				estado_temperatura = ESTABLE;
			}
		break;

	default: break;
	}

}

void Maquina_Humedad_suelo(void)
{
	switch(estado_humedad)
	{
	case ESTABLE:
		if(invernadero.humedad > cultivo.humedad_max)
		{
			estado_humedad = HUMEDO;
		}
		if(invernadero.humedad < cultivo.humedad_min)
		{
			estado_humedad = SECO;
		}
		break;
	case HUMEDO:

		if(invernadero.humedad <= cultivo.humedad_max)
			{
				estado_humedad = ESTABLE;
			}
		break;
	case SECO:

			if(invernadero.humedad >= cultivo.humedad_min)
				{
					estado_humedad = ESTABLE;
				}
			break;
	default: break;
	}

}

/*void Maquina_Humedad_ambiente(void)
{
	switch(estado_humedad_ambiente)
	{
	case ESTABLE:
		if(invernadero.humedad > cultivo.humedad_ambiente_max)
		{
			estado_humedad_ambiente = HUMEDO;
		}
		if(invernadero.humedad < cultivo.humedad_ambiente_min)
		{
			estado_humedad_ambiente = SECO;
		}
		break;
	case HUMEDO:

		if(invernadero.humedad <= cultivo.humedad_ambiente_max)
			{
				estado_humedad_ambiente = ESTABLE;
			}
		break;
	case SECO:

			if(invernadero.humedad >= cultivo.humedad_ambiente_min)
				{
					estado_humedad_ambiente = ESTABLE;
				}
			break;
	default: break;
	}

}*/

void Maquina_Estado_General(void)
{
	// Manejo del Cooler
	if(/*estado_humedad == HUMEDO ||*/ estado_temperatura == CALOR)
	{
		SetPin(COOLER_IN,ON);
		SetPin(COOLER_OUT,ON);
	}
	if(/*estado_humedad != HUMEDO &&*/ estado_temperatura != CALOR)
	{
		SetPin(COOLER_IN,OFF);
		SetPin(COOLER_OUT,OFF);
	}
	// Manejo del Calefactor
	if(estado_temperatura == FRIO)
	{
		SetPin(CALEFACTOR,ON);
		SetPin(COOLER_IN,ON);
	}
		else
			{
				SetPin(CALEFACTOR,OFF);
				SetPin(COOLER_IN,OFF);
			}
	// Control del Riego
	if(estado_humedad == SECO)
	{

		SetPin(REGADOR,ON);
		// comienzo a contar tiempo utilizando timers
	}

	if(estado_humedad == HUMEDO)
	{
		SetPin(REGADOR,OFF);

	}
	if(estado_humedad == ESTABLE)
	{
		if(flag_riego == ON)
			{
				SetPin(REGADOR,ON);
			}
			else
			{
				SetPin(REGADOR,OFF);
			}
	}
}
	/*if(estado_humedad == ESTABLE)
	{
	}
	*/

void Maquina_RX(void)
{

	// trama de datos de funcionamiento normal <,<,T,temp_max,temp_min,H,hum_max,hum_min,I,horas al dia,R,hora_deinicio,mins_deinicio,duracion(en minutos),>,>

	static uint8_t estado_rx = REPOSO0;



	if(estado_rx == REPOSO0 && dato_rx == '<')
		{
		estado_rx=REPOSO1;
		return;
		}
	if(estado_rx == REPOSO1 && dato_rx =='<')
		{
		estado_rx=REPOSO2;
		return;
		}
	if(estado_rx == REPOSO2 && dato_rx == 'T')
		{
			estado_rx=RECIBIENDO_TEMP_MAX;
			return;
		}
	if(estado_rx == RECIBIENDO_TEMP_MAX) // recibo temperatura maxima
		{
			if(first_time == 0)
			{

				buffer_cultivo.temp_max = (dato_rx-48) * 10;
				estado_rx= RECIBIENDO_TEMP_MAX;
				first_time = 1;
				return;
			}
			if(first_time == 1)
			{
				buffer_cultivo.temp_max += (dato_rx-48);
				estado_rx = RECIBIENDO_TEMP_MIN;
				first_time = 0;
				return;
			}

			else{
				estado_rx = REPOSO0;
			}
			return;

		}
	if(estado_rx == RECIBIENDO_TEMP_MIN)	// recibo temperatura minima
	{
		if(first_time == 0)
		{

			buffer_cultivo.temp_min = (dato_rx-48) * 10;
			estado_rx= RECIBIENDO_TEMP_MIN;
			first_time = 1;
			return;
		}
		if(first_time == 1)
		{
			buffer_cultivo.temp_min += (dato_rx-48);
			estado_rx = RECIBIENDO_HUMEDAD;
			first_time = 0;
			return;
		}

		else{
			estado_rx = REPOSO0;
		}
		return;
	}
	if(estado_rx == RECIBIENDO_HUMEDAD && dato_rx == 'H')
	{
		estado_rx=RECIBIENDO_HUM_MAX;
		return;
	}
	if(estado_rx == RECIBIENDO_HUM_MAX)
	{
		if(first_time == 0)
		{

			buffer_cultivo.humedad_max = (dato_rx-48) * 10;
			estado_rx= RECIBIENDO_HUM_MAX;
			first_time = 1;
			return;
		}
		if(first_time == 1)
		{
			buffer_cultivo.humedad_max += (dato_rx-48);
			estado_rx = RECIBIENDO_HUM_MIN;
			first_time = 0;
			return;
		}

		else{
			estado_rx = REPOSO0;
		}
		return;
	}
	if(estado_rx == RECIBIENDO_HUM_MIN)
	{
		if(first_time == 0)
		{

			buffer_cultivo.humedad_min = (dato_rx-48) * 10;
			estado_rx= RECIBIENDO_HUM_MIN;
			first_time = 1;
			return;
		}
		if(first_time == 1)
		{
			buffer_cultivo.humedad_min += (dato_rx-48);
			estado_rx = RECIBIENDO_ILUMINACION;
			first_time = 0;
			return;
		}

		else{
			estado_rx = REPOSO0;
		}
		return;
	}
	if(estado_rx == RECIBIENDO_ILUMINACION && dato_rx == 'I')
	{
		estado_rx = RECIBIENDO_ILUMINACION_HORAS;
		return;
	}
	if(estado_rx == RECIBIENDO_ILUMINACION_HORAS)
	{
		if(first_time == 0)
		{

			buffer_cultivo.iluminacion = (dato_rx-48) * 10;
			estado_rx= RECIBIENDO_ILUMINACION_HORAS;
			first_time = 1;
			return;
		}
		if(first_time == 1)
		{
			buffer_cultivo.iluminacion += (dato_rx-48);
			estado_rx = RECIBIENDO_RIEGO;
			first_time = 0;
			return;
		}

		else{
			estado_rx = REPOSO0;
		}
		return;
	}
	if(estado_rx == RECIBIENDO_RIEGO && dato_rx == 'R')
	{
		estado_rx = RECIBIENDO_RIEGO_INICIO_HORA;
		return;
	}
	if(estado_rx == RECIBIENDO_RIEGO_INICIO_HORA)
	{
		if(first_time == 0)
				{

					buffer_cultivo.riego_inicio_hora = (dato_rx-48) * 10;
					estado_rx= RECIBIENDO_RIEGO_INICIO_HORA;
					first_time = 1;
					return;
				}
				if(first_time == 1)
				{
					buffer_cultivo.riego_inicio_hora += (dato_rx-48);
					estado_rx = RECIBIENDO_RIEGO_INICIO_MINS;
					first_time = 0;
					return;
				}

				else{
					estado_rx = REPOSO0;
				}
				return;
	}
	if(estado_rx == RECIBIENDO_RIEGO_INICIO_MINS)
	{
		if(first_time == 0)
				{

					buffer_cultivo.riego_inicio_mins = (dato_rx-48) * 10;
					estado_rx= RECIBIENDO_RIEGO_INICIO_MINS;
					first_time = 1;
					return;
				}
				if(first_time == 1)
				{
					buffer_cultivo.riego_inicio_mins += (dato_rx-48);
					estado_rx = RECIBIENDO_RIEGO_DURACION;
					first_time = 0;
					return;
				}

				else{
					estado_rx = REPOSO0;
				}
				return;
	}
	if(estado_rx == RECIBIENDO_RIEGO_DURACION)
	{
		if(first_time == 0)
				{

					buffer_cultivo.riego_duracion = (dato_rx-48) * 10;
					estado_rx= RECIBIENDO_RIEGO_DURACION;
					first_time = 1;
					return;
				}
				if(first_time == 1)
				{
					buffer_cultivo.riego_duracion += (dato_rx-48);
					//estado_rx = REPOSO_CARACTER_ESPECIAL;
					estado_rx = REPOSO3;
					first_time = 0;
					return;
				}

				else{
					estado_rx = REPOSO0;
				}
				return;
	}
	/*if(estado_rx == REPOSO_CARACTER_ESPECIAL && dato_rx == '\r' )
	{

			estado_rx=REPOSO3;
			return;
	}*/
	if(estado_rx == REPOSO3 && dato_rx == '>')
	{

			estado_rx=REPOSO4;
			return;
	}
	if(estado_rx == REPOSO4 && dato_rx == '>')
	{

			estado_rx=REPOSO0;
			flag_dato=VALIDO;
			return;
	}
	else
	{
		estado_rx=REPOSO0;
	}
	}




void Maquina_Luz(void)
{
	// CTIME0 --> del bit 16 al 20 tengo los 5 bits que contienen la hora
	uint32_t hora_actual = 0;


	/*for(i=16;i<21;i++)
	{
	hora_actual |= ( CTIME0 & (1<<i));
	}*/
	hora_actual = HOUR;
	//hora_actual = hora_actual>>16;
	//hora_actual &=(32);
	if(hora_actual >= (14-((cultivo.iluminacion/2)+cultivo.iluminacion%2)) && (hora_actual <= (14+((cultivo.iluminacion/2)+cultivo.iluminacion%2))) )
	{
		flag_iluminacion = ON; // flag que me indica que el cultivo debe estar iluminado
		//SetPin(REGADOR,ON);
	}
	else
	{
			flag_iluminacion = OFF;
			//SetPin(REGADOR,OFF);
	}
	if( flag_iluminacion == ON)
	{
		if(invernadero.luz == 0) // No hay luz solar , prendo la iluminacion
		{
			SetPin(LAMPARA,ON);
		}
		else{ // apago la iluminacion
			SetPin(LAMPARA,OFF);
		}
	}
	if( flag_iluminacion == OFF)
	{
		SetPin(LAMPARA,OFF);
	}
}


void Maquina_dePrueba(void)
{
	// trama de prueba >,>,p,r,u,e,b,a,<,<
	static uint8_t estado_pruebarx = PRIMER_CARACTER;


	if(flag_rx == ESTADO_PRUEBA)	// ejecuto codigo de prueba
	{
		// Primero Apago todo
		SetPin(COOLER_IN,OFF);
		SetPin(COOLER_OUT,OFF);
		SetPin(LAMPARA,OFF);
		SetPin(REGADOR,OFF);
		SetPin(CALEFACTOR,OFF);

		Demora_Prueba = DEMORA_SEGUNDOS;
		while(Demora_Prueba);
		SetPin(COOLER_IN,ON);
		Demora_Prueba = DEMORA_SEGUNDOS;
		while(Demora_Prueba);
		SetPin(COOLER_IN,OFF);
		SetPin(COOLER_OUT,ON);
		Demora_Prueba = DEMORA_SEGUNDOS;
		while(Demora_Prueba);
		SetPin(COOLER_OUT,OFF);
		SetPin(REGADOR,ON);
		Demora_Prueba = DEMORA_SEGUNDOS;
		while(Demora_Prueba);
		SetPin(REGADOR,OFF);
		SetPin(LAMPARA,ON);
		Demora_Prueba = DEMORA_SEGUNDOS;
		while(Demora_Prueba);
		SetPin(LAMPARA,OFF);
		SetPin(CALEFACTOR,ON);
		Demora_Prueba = DEMORA_SEGUNDOS;
		while(Demora_Prueba);
		SetPin(CALEFACTOR,OFF);
		flag_rx = ESTADO_NO_PRUEBA;		// salgo del modo prueba
	}

	if( FLAG_DATO == DATO_NUEVO)
	{
		dato_rx = PopRx();
		FLAG_DATO = DATO_VIEJO;

	if(dato_rx == '|' && estado_pruebarx == PRIMER_CARACTER)
			{
				estado_pruebarx = SEGUNDO_CARACTER;
				return;
			}
	if(dato_rx == '|' && estado_pruebarx == SEGUNDO_CARACTER)
			{
				estado_pruebarx = TERCER_CARACTER;
				return;
			}

	if((dato_rx == 'p') && estado_pruebarx == TERCER_CARACTER)
			{
				estado_pruebarx=CUARTO_CARACTER;
				return;
			}

	if((dato_rx == 'r') && estado_pruebarx == CUARTO_CARACTER)
			{
				estado_pruebarx=QUINTO_CARACTER;
				return;
			}

	if((dato_rx == 'u') && estado_pruebarx == QUINTO_CARACTER)
			{
				estado_pruebarx=SEXTO_CARACTER;
				return;
			}

	if((dato_rx == 'e') && estado_pruebarx == SEXTO_CARACTER)
			{
					estado_pruebarx=SEPTIMO_CARACTER;
					return;
			}

	if((dato_rx == 'b') && estado_pruebarx == SEPTIMO_CARACTER)
			{
					estado_pruebarx=OCTAVO_CARACTER;
					return;
			}
	if((dato_rx == 'a') && estado_pruebarx == OCTAVO_CARACTER)
			{
					estado_pruebarx=NOVENO_CARACTER;
					return;
			}

	if((dato_rx == '|') && estado_pruebarx == NOVENO_CARACTER)
			{
					estado_pruebarx=DECIMO_CARACTER;
					return;
			}

	if((dato_rx == '|') && estado_pruebarx == DECIMO_CARACTER)
			{
					estado_pruebarx=PRIMER_CARACTER;
					flag_rx = ESTADO_PRUEBA;
					return;
			}
		else
			{
					estado_pruebarx=PRIMER_CARACTER;
					flag_rx = ESTADO_NO_PRUEBA;

			}

	Maquina_RX();

	}



}

/*
void EINT0_IRQHandler(void)
{
	if(IO0StatR & (0x01 << 18) != 0) // se presiono el Boton P0.18
	{

	}
	if(IO2StatR & (0x01 << 10) != 0) // // se presiono el Boton P2.10
	{

	}

	IO0IntClr |= (1<<18); // limpio interrupcion
	IO2IntClr |= (1<<10); // limpio interrupcion
}


void EINT3_IRQHandler(void)
{
	if(IO2StatR & (0x01 << 13) != 0) // // se presiono el Boton P2.13
		{

		}

	IO2IntClr |= (1<<13); // limpio interrupcion
}

*/

void Maquina_Botones(void)
{
	if(GetPin(BOTON_PRUEBA) == 0)
	    	{
	    		flag_rx = ESTADO_PRUEBA;
	    	}
	    	if(GetPin(BOTON_BLOQUEO) == 0)	// se presiono el pulsador de bloqueo
	    	{
	    		flag_bloqueo = 1;
	    		SetPin(COOLER_IN,OFF);
	    		SetPin(COOLER_OUT,OFF);
	    		SetPin(LAMPARA,OFF);
	    		SetPin(REGADOR,OFF);
	    		SetPin(CALEFACTOR,OFF);

	    		while(flag_bloqueo == 1 )
	    		{
	    			if(GetPin(BOTON_DESBLOQUEO) == 0)
	    			{
	    				flag_bloqueo = 0;
	    			}
	    		}
	    	}
}

void Cargar_Datos(void)
{
	cultivo.temp_min = buffer_cultivo.temp_min;
	cultivo.temp_max = buffer_cultivo.temp_max;
	cultivo.humedad_min = buffer_cultivo.humedad_min;
	cultivo.humedad_max = buffer_cultivo.humedad_max;
	cultivo.iluminacion = buffer_cultivo.iluminacion;
	cultivo.riego_inicio_hora = buffer_cultivo.riego_inicio_hora;
	cultivo.riego_inicio_mins = buffer_cultivo.riego_inicio_mins;
	cultivo.riego_duracion = buffer_cultivo.riego_duracion;

	RTC_SetAlarma(cultivo.riego_inicio_hora,cultivo.riego_inicio_mins);
}

void Lectura_CanalesADC(void)
{
	invernadero.temperatura = ADCLeer(CANAL_TEMPERATURA);
	invernadero.humedad = ADCLeer(CANAL_HUMEDAD);
	invernadero.luz = ADCLeer(CANAL_LUZ);
}

void Maquina_Alarma(void)
{
	if(alarma == 1)
	{
		alarma = 0;
		// Salta la alarma, enciendo el riego
		if(estado_humedad != HUMEDO)	// salto la alarma de riego, pero solo la voy a activar si esta SECO.
		{
		SetPin(REGADOR,1);
		flag_riego = ON;
		contador_riego = 0;
		contador_rehabilitacion_alarma = 0;
		}
	}
	if((contador_rehabilitacion_alarma == 2) && (alarma == 0)) // dejo pasar 2 mins hasta rehabilitar la alarma
	{
		AMR &=~(0x6); // vuelvo a habilitar la alarma
	}

}
