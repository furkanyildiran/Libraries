#ifdef __cplusplus
extern "C" {
#endif

#ifndef  _TWI_H
#define  _TWI_H
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include <math.h>
#include "I2C_mnemonics.h"


void I2C_master_init(uint32_t SCLK, uint8_t wait_signal_us);
uint8_t I2C_master_transmit_data(uint8_t device_addr, uint8_t reg_addr, uint8_t data);
uint8_t I2C_master_receive_data(uint8_t device_addr, uint8_t reg_addr, volatile uint8_t *data_addr, uint8_t range);
void I2C_slave_init(uint8_t address);
void I2C_slave_wait_address(void);
void I2C_slave_receive_data(unsigned char data_buffer[], uint8_t byte_size);


#endif

#ifdef __cplusplus
}
#endif 