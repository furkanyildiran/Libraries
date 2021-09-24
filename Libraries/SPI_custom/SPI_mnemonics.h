#ifndef __SPI_MNEMONICS__
#define __SPI_MNEMONICS__
#ifndef F_CPU
#define F_CPU 16000000
#endif

#define SPI_OSC_DIVIDER4 0
#define SPI_OSC_DIVIDER16 1
#define SPI_OSC_DIVIDER64 2
#define SPI_OSC_DIVIDER128 3
#define SPI_OSC_DIVIDER2_2X 4
#define SPI_OSC_DIVIDER8_2X 5
#define SPI_OSC_DIVIDER32_2X 6
#define SPI_OSC_DIVIDER64_2X 7
#define SPI_CPOL_LEADING_EDGE_RISING 0
#define SPI_CPOL_LEADING_EDGE_FALLING 1
#define SPI_CPHA_LEADING_EDGE_SAMPLE 0
#define SPI_CPHA_LEADING_EDGE_SETUP 1
#define SPI_MASTER_MODE 1
#define SPI_SLAVE_MODE 0
#define SPI_FIRST_LSB 1
#define SPI_FIRST_MSB 0

#if defined (__AVR_ATmega328P__)
#define SPI_SS 2
#define SPI_MOSI  3
#define SPI_MISO 4
#define SPI_SCK 5
#elif defined (__AVR_ATmega2560__)
#define SPI_SS 0
#define SPI_SCK 1
#define SPI_MOSI 2
#define SPI_MISO 3
#endif

#endif