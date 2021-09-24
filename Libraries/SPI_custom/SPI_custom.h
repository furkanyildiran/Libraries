#ifndef __SPI_CUSTOM_H__
#define __SPI_CUSTOM_H__
#include "SPI_mnemonics.h"
#include <avr/io.h>
#include <stdint.h>

void SPI_master_init(uint8_t data_order, uint8_t clock_polarity, uint8_t clock_phase, uint8_t osc_divider)
{
	DDRB = 0;
	SPCR = 0;
	SPSR = 0;
	SPCR |= (1 << SPE) | (1 << MSTR);
	DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);
	DDRB &= ~(1 << SPI_MISO);
	PORTB |= (1 << SPI_SS);

	if (data_order == SPI_FIRST_LSB)
	SPCR |= (1 << DORD);
	else if (data_order == SPI_FIRST_MSB)
	SPCR &= ~(1 << DORD);

	if (clock_polarity == SPI_CPOL_LEADING_EDGE_FALLING)
	SPCR |= (1 << CPOL);
	else if (clock_polarity == SPI_CPOL_LEADING_EDGE_RISING)
	SPCR &= ~(1 << CPOL);

	if (clock_phase == SPI_CPHA_LEADING_EDGE_SETUP)
	SPCR |= (1 << CPHA);
	else if (clock_phase == SPI_CPHA_LEADING_EDGE_SAMPLE)
	SPCR &= ~(1 << CPHA);

	switch (osc_divider)
	{
		case SPI_OSC_DIVIDER4:
		SPCR &= ~((1 << SPR1) | (1 << SPR0));
		break;
		case SPI_OSC_DIVIDER16:
		SPCR |= (1 << SPR0);
		break;
		case SPI_OSC_DIVIDER64:
		SPCR |= (1 << SPR1);
		break;
		case SPI_OSC_DIVIDER128:
		SPCR |= (1 << SPR1) | (1 << SPR0);
		break;
		case SPI_OSC_DIVIDER2_2X:
		SPSR |= (1 << SPI2X);
		break;
		case SPI_OSC_DIVIDER8_2X:
		SPCR |= (1 << SPR0);
		SPSR |= (1 << SPI2X);
		break;
		case SPI_OSC_DIVIDER32_2X:
		SPCR |= (1 << SPR1);
		SPSR |= (1 << SPI2X);
		break;
		case SPI_OSC_DIVIDER64_2X:
		SPCR |= (1 << SPR1) | (1 << SPR0);
		SPSR |= (1 << SPI2X);
		break;
		default:
		break;
	}
}

void SPI_master_transmit_data(uint8_t data)
{
	PORTB &= ~(1 << SPI_SS);
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));
	PORTB |= (1 << SPI_SS);
}
uint8_t SPI_master_receive_data(void)
{
	PORTB &= ~(1 << SPI_SS);
	SPDR = 0;
	while(!(SPSR & (1 << SPIF)));
	PORTB |= (1 << SPI_SS);
	return SPDR;
}
void SPI_slave_init(uint8_t data_order, uint8_t clock_polarity, uint8_t clock_phase)
{
	DDRB = 0;
	SPCR = 0;
	SPSR = 0;

	SPCR |= (1 << SPE);
	DDRB &= ~((1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS));
	DDRB |= (1 << SPI_MISO);

	if (data_order == SPI_FIRST_LSB)
	SPCR |= (1 << DORD);
	else if (data_order == SPI_FIRST_MSB)
	SPCR &= ~(1 << DORD);

	if (clock_polarity == SPI_CPOL_LEADING_EDGE_FALLING)
	SPCR |= (1 << CPOL);
	else if (clock_polarity == SPI_CPOL_LEADING_EDGE_RISING)
	SPCR &= ~(1 << CPOL);

	if (clock_phase == SPI_CPHA_LEADING_EDGE_SETUP)
	SPCR |= (1 << CPHA);
	else if (clock_phase == SPI_CPHA_LEADING_EDGE_SAMPLE)
	SPCR &= ~(1 << CPHA);
}
void SPI_slave_transmit_data(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));	
}
uint8_t SPI_slave_receive_data(void)
{
	SPDR = 0;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}
#endif