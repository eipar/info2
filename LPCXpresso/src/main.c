/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
//#include "LPC17xx.h"
#endif

#include "KitInfo2.h"
#include <stdio.h>


int main (void)
{
	InicializarKit();
	//	Lo "pongo en hora" , solo lo hago una vez pq dps con la pila de la placa me queda almacenada la hora
	/*----------------------------------------------------------------------------------------
		RTC_HoraFecha horafecha;
		horafecha.anio = 2014;
		horafecha.mes = 11;
		horafecha.dia_mes = 16;
		horafecha.hora = 15;
		horafecha.min = 15;
		horafecha.seg = 0;
		RTC_SetHoraFecha(&horafecha);
	----------------------------------------------------------------------------------------
	*/
	// codigo de prueba de maquina de  estados
		cultivo.temp_min = 10;
		cultivo.temp_max = 35;
		cultivo.humedad_min =75;
		cultivo.humedad_max =90;
		cultivo.iluminacion =18;
		cultivo.riego_inicio_hora =18;
		cultivo.riego_inicio_mins =15;
		cultivo.riego_duracion =6;
	//---------------------------------------------

	while(1)
    {


    	if(FLAG_ADC)
    	{
    		Lectura_CanalesADC();
    		FLAG_ADC=0;
    	}
    	//UART

    	Maquina_dePrueba();
    	if(flag_dato == VALIDO)	// llego el dato , copio de la estructura buffer a la estructura cultivo
    	{
    		Cargar_Datos();
    	}
    	//maquinas de estados del clima (toma valores medidos e indica el estado del clima)
    	Maquina_Temperatura();
    	Maquina_Humedad_suelo();
    	Maquina_Luz();
    	//maquina de estados del invernadero (toma el estado del clima y actua en consecuencia)
    	Maquina_Estado_General();
    	Maquina_Botones();
    	Maquina_Alarma();

    }

    return 0;
}

