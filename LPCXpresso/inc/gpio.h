/*
 * funciones_mias.h
 *
 *  Created on: 14/04/2014
 *      Author: Mariano
 */



#ifndef FUNCIONES_MIAS_H_
#define FUNCIONES_MIAS_H_

#include "Regs.h"
#include "KitInfo2.h"
#include "KitInic.h"

void SetPin(uint8_t  port, uint8_t pin,uint8_t value);
void SetDir(uint8_t  port, uint8_t pin,uint8_t mode);
void SetFunc(uint8_t  port, uint8_t pin,uint8_t function);
uint8_t GetPin(uint8_t  port, uint8_t pin);


#endif /* FUNCIONES_MIAS_H_ */
