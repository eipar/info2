/*
 * maquinas.h
 *
 *  Created on: 24/09/2014
 *      Author: Mariano
 */

#ifndef MAQUINAS_H_
#define MAQUINAS_H_

#include "KitInfo2.h"

void Maquina_Temperatura(void);
void Maquina_Humedad_suelo(void);
void Maquina_Humedad_ambiente(void);
void Maquina_Estado_General(void);
void Maquina_RX(void);
void Maquina_Luz(void);
void Maquina_dePrueba(void);
void Maquina_Botones(void);
void Cargar_Datos(void);
void Lectura_CanalesADC(void);
void Maquina_Alarma(void);

#endif /* MAQUINAS_H_ */
