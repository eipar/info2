/* Author: Ing. Marcelo Trujillo */

#ifndef UART_H_
#define UART_H_

//#include "LPC17xx.h"

#define	TOPE_BUFFER_TX		1000
#define	TOPE_BUFFER_RX		1000

// PCUART0
#define PCUART0_POWERON (1 << 3)

#define PCLK_UART0 6
#define PCLK_UART0_MASK (3 << 6)

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

void UART0_Init( uint32_t baudrate );
void UART0_IRQHandler (void);
void PushTx(unsigned char dato);
int PopTx( void );
void PushRx(unsigned char dato);
int PopRx( void );
void Transmitir (char *p );

#endif /*UART_H_*/
