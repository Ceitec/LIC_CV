/*
 * SPI_Config.h
 *
 * Created: 5.8.2015 15:27:13
 *  Author: Lukas
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include <avr/io.h>


// Nastaveni pinu pro Atmega32
#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define SPI_PIN		PINB	
#define SPI_SS		DDB4
#define SPI_MOSI	DDB5
#define SPI_MISO	DDB6
#define SPI_SCK		DDB7


/* Pro Arduino Nano 328P
#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define SPI_PIN		PINB
#define SPI_SS		PORTB2
#define SPI_MOSI	PORTB3
#define SPI_MISO	PORTB4
#define SPI_SCK		PORTB5
*/

#endif /* SPI_CONFIG_H_ */