/*
 * SPI.h
 *
 * Created: 28.7.2015 17:28:09
 *  Author: Lukas
 */ 


#ifndef SPIX_H
#define SPIX_H

#include "SPI_Config.h"
#include <stdint.h>

void spi_init();
uint8_t spi_transmit(uint8_t data);

#define ENABLE_CHIP() (SPI_PORT &= (~(1<<SPI_SS)))
#define DISABLE_CHIP() (SPI_PORT |= (1<<SPI_SS))


#endif

/*


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "SPI_Config.h"

void SPI_MasterInit(void);
void SPI_SlaveInit(void);
uint8_t SPI_MasterTransmit(char cData);
char SPI_SlaveReceive(void);

#define ENABLE_CHIP() (SPI_DDR &= (~(1 << SPI_SS)))
#define DISABLE_CHIP() (SPI_DDR |= (1 << SPI_SS))



#endif / * SPI_H_ * /*/