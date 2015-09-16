/*
 * SPI.c
 *
 * Created: 28.7.2015 17:27:59
 *  Author: Lukas
 */ 


#include "SPI.h"
#include <avr/io.h>



#if SPI_CONFIG_AS_MASTER
void spi_init()
{
	SPI_DDR = (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPR1);//prescaler 128
}


uint8_t spi_transmit(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}

#else
void spi_init()
{
	SPI_DDR = (1<<SPI_MISO);
	SPCR = (1<<SPE);
}

uint8_t spi_transmit(uint8_t data)
{
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
#endif



/*

void SPI_MasterInit(void)
{
	
	//Set MOSI and SCK output, all others input 
	//SPI_DDR = (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);
	
	//Enable SPI, Master, set clock rate fck/16 
	//SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	
	
	SPI_DDR = (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);//prescaler 16
}

uint8_t SPI_MasterTransmit(char cData)
{
	//Start transmission 
	SPDR = cData;
	PORTA ^= (1 << PA6);
	//Wait for transmission complete
	while(!(SPSR & (1 << SPIF)));
	PORTA ^= (1 << PA5);
	return SPSR;
	
}

void SPI_SlaveInit(void)
{
	/ * Set MISO output, all others input * /
	SPI_DDR = (1 << SPI_MISO);
	/ * Enable SPI * /
	SPCR = (1 << SPE);
}

char SPI_SlaveReceive(void)
{
	/ * Wait for reception complete * /
	while(!(SPSR & (1 << SPIF)));
	/ * Return data register * /
	return SPDR;
}
*/

