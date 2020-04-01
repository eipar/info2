/* Author: Ing. Marcelo Trujillo */

#include "KitInfo2.h"

// Buffer de Transmision
volatile unsigned char BufferTx[TOPE_BUFFER_TX];

// Buffer de Recepcion
unsigned char BufferRx[TOPE_BUFFER_RX];

// Indices de Transmision
volatile unsigned char IndiceTxIn,IndiceTxOut;
// Indices de Recepcion
volatile unsigned char IndiceRxIn,IndiceRxOut;

// flag de fin de TX
volatile char TxStart;


// ***********************
// Function to set up UART
void UART0_Init( uint32_t baudrate )
{
	int pclk;
	unsigned long int Fdiv;

	// PCLK_UART0 is being set to 1/4 of SystemCoreClock
	pclk = CORE_CLK / 4;

	// Turn on power to UART0
	PCONP |=  PCUART0_POWERON;

	// Turn on UART0 peripheral clock
	PCLKSEL0 &= ~(PCLK_UART0_MASK);
	PCLKSEL0 |=  (0 << PCLK_UART0);		// PCLK_periph = CCLK/4

	// Set PINSEL0 so that P0.2 = TXD0, P0.3 = RXD0
	PINSEL0 &= ~0xf0;
	PINSEL0 |= ((1 << 4) | (1 << 6));

	U0LCR = 0x83;		// 8 bits, no Parity, 1 Stop bit, DLAB=1
    Fdiv = ( pclk / 16 ) / baudrate ;	// Set baud rate
    U0DLM = Fdiv / 256;
    U0DLL = Fdiv % 256;

    //-----------------------------------------------------------------------------
    U0LCR = 0x03;		// 8 bits, no Parity, 1 Stop bit DLAB = 0
    //-----------------------------------------------------------------------------

    U0IER = IER_RBR | IER_THRE | IER_RLS;	/* Habilito las Interrupciones por Recepcion,Transmision o Error */

    ISER0 |= (1 << 5); // Habilito la interrupcion UART0
}


void UART0_IRQHandler (void)
{
	static  char buffer[300];
	static int j = 0;

	uint32_t lsr;
	uint32_t iir;
	uint32_t IntEnCurso , IntPendiente ;
	uint32_t dato ;

	do
	{  //IIR es reset por HW, una vez que lo lei se resetea.

		iir = U0IIR;

		IntPendiente = iir & 0x01;
		IntEnCurso = ( iir >> 1 ) & 0x03;	// estaba en 0x07

		switch( IntEnCurso )
		{
			case IIR_RLS:
				lsr = U0LSR;	// con la lectura se borra la int
				if ( lsr & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
				{
					dato = U0RBR;		// Leo para borrar el buffer
					return;
				}
			case IIR_RDA:	/* Receive Data Available */

				dato = U0RBR;						// Lectura del dato

				buffer[j] = dato;
				j++;

				PushRx( (unsigned char ) dato );	// Guardo el dato
				FLAG_DATO = DATO_NUEVO;
				//IntPendiente=1;
			// codigo experimento---
			//U0THR = (unsigned char) PopRx();
			//
				break;

			case IIR_THRE:	/* THRE, transmit holding register empty */
			case 0:
				dato = PopTx();						// Tomo el dato a Transmitir
				if ( dato >= 0 )
					U0THR = (unsigned char) dato;	// si hay dato en la cola lo Transmito
				else
					TxStart = 0;
				break;

		}
	}
	while( ! (iir & 0x01) ); /* me fijo si cuando entr‚ a la ISR habia otra
						     	int. pendiente de atenci¢n: b0=1 (ocurre £nicamente si dentro del mismo
								espacio temporal lleguan dos interrupciones a la vez) */
}

void PushTx(unsigned char dato)
{
	int Dato_Leido = -1;

	BufferTx[IndiceTxIn] = dato;

	IndiceTxIn ++;
	IndiceTxIn %= TOPE_BUFFER_TX;

	if ( TxStart == 0 )
	{
		TxStart = 1;

		Dato_Leido = PopTx();						// Tomo el dato a Transmitir
		if ( Dato_Leido >= 0 )
			U0THR = (unsigned char) Dato_Leido;	// si hay dato en la cola lo Transmito
		else
			TxStart = 0;

		//ISPR |= ISP_UART0;	// interrupcion UART0 pendiente
	}
}

int PopTx( void )
{
	int dato = -1;

	if ( IndiceTxIn != IndiceTxOut )
	{
		dato = (unsigned int) BufferTx[IndiceTxOut];
		IndiceTxOut ++;
		IndiceTxOut %= TOPE_BUFFER_TX;
	}
	return dato;
}

void PushRx(unsigned char dato)
{
	BufferRx[IndiceRxIn] = dato;
	IndiceRxIn ++;
	IndiceRxIn %= TOPE_BUFFER_RX;
}

int PopRx( void )
{

	int dato = -1;

	if ( IndiceRxIn != IndiceRxOut )
	{
		dato = (unsigned int) BufferRx[IndiceRxOut];
		IndiceRxOut ++;
		IndiceRxOut %= TOPE_BUFFER_RX;
	}
	return dato;
}

void Transmitir (char *p )
{
	int i;
	for( i = 0 ; p[i] ; i++ )
		PushTx( p[i] );
}

