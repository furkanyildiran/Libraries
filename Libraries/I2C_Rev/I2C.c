#include "I2C.h"


static uint8_t twi_waiting_duration = 0;


/*
if TWINT flag does not change then 
occur time overflow and function return 
error signal(1).
This function use in all twi signal sending except stop
signal sending for example start signal, data sending etc.
If you want TWSR register content then you can get it 
in this function.
*/
uint8_t wait_transmit(uint8_t us)
{
  //MAX I2C freq = 400KHz 2.5 us period
  uint8_t error_signal = 0;
  if (us > 63)
    us = 63;
  us *= 4;
  while (!(TWCR & (1 << TWINT))) {
    asm volatile ("NOP");            //4*(NOP command) = 0.25 us delay
    asm volatile ("NOP");
    asm volatile ("NOP");
    asm volatile ("NOP");
    us --;
    if (us == 0) {
      error_signal = 1;
      TWCR = 0;
      break;
    }
  }
  return error_signal;
}
/*For stop signal sending used seperate 
a time overflow function.Because stop signal`s flag
is different from others.
*/
uint8_t wait_stop_signal(uint8_t us)
{
  //MAX I2C freq = 400KHz 2.5 us period
  uint8_t error_signal = 0;
  if (us > 63)
    us = 63;
  us *= 4;
  while (TWCR & (1 << TWSTO)) {
    asm volatile ("NOP");
    asm volatile ("NOP");
    asm volatile ("NOP");
    asm volatile ("NOP");
    us --;
    if (us == 0) {
      error_signal = 1;	
      TWCR = 0;
      break;
    }
  }
  return error_signal;
}


uint8_t I2C_master_init(uint32_t SCLK, uint8_t wait_signal_us)
{
  twi_waiting_duration = wait_signal_us;
  TWSR = 0x00;
  TWBR = ((F_CPU / SCLK) - 16) / (2 * pow(4, (TWSR & ((1 << TWPS0) | (1 << TWPS1)))));
}

uint8_t I2C_master_transmit_data(uint8_t device_addr, uint8_t reg_addr, uint8_t data)
{
  uint8_t transmit_error = 0;
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);   //start
  transmit_error = wait_transmit(twi_waiting_duration);

  TWDR = (device_addr << 1) | WRITE;                  //transmit addr
  TWCR = (1 << TWINT) | (1 << TWEN);
  transmit_error = wait_transmit(twi_waiting_duration);

  TWDR = reg_addr;                                    //transmit reg_addr
  TWCR = (1 << TWINT) | (1 << TWEN);
  transmit_error = wait_transmit(twi_waiting_duration);

  TWDR = data;                                        //transmit data
  TWCR = (1 << TWINT) | (1 << TWEN);
  transmit_error = wait_transmit(twi_waiting_duration);

  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);  //transmit stop
  wait_stop_signal(twi_waiting_duration);
  return transmit_error;
}


uint8_t I2C_master_receive_data(uint8_t device_addr, uint8_t reg_addr, volatile uint8_t *data_addr, uint8_t range)
{
  uint8_t reading_error = 0;
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);  //start
  reading_error = wait_transmit(twi_waiting_duration);

  TWDR = (device_addr << 1) | WRITE;                 //transmit sla+w
  TWCR = (1 << TWINT) | (1 << TWEN);
  reading_error = wait_transmit(twi_waiting_duration);

  TWDR = reg_addr;                                   //transmit reg_addr
  TWCR = (1 << TWINT) | (1 << TWEN);
  reading_error = wait_transmit(twi_waiting_duration);

  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);  //repeated start
  reading_error = wait_transmit(twi_waiting_duration);

  TWDR = (device_addr << 1) | READ;                  //transmit sla+r
  TWCR = (1 << TWINT) | (1 << TWEN);
  reading_error = wait_transmit(twi_waiting_duration);

  for (uint8_t i = 1; i < range; i++, data_addr++)
  {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); //read multible bytes
    reading_error = wait_transmit(twi_waiting_duration);
    *data_addr =  TWDR;
  }
  if (range > 1)
    data_addr++;
  TWCR = (1 << TWINT) | (1 << TWEN);                 //read last or single byte
  reading_error = wait_transmit(twi_waiting_duration);
  *data_addr = TWDR;
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);  //transmit stop
  reading_error = wait_stop_signal(twi_waiting_duration);
  return reading_error;
}
//slave section will rewrite
void I2C_slave_init(uint8_t address)
{
	TWAR = (address << 1);
	TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
}

void I2C_slave_wait_address(void)
{
	TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void I2C_slave_receive_data(unsigned char data_buffer[], uint8_t byte_size)
{
	for (int i = 0; i < byte_size - 1; i++)
	{
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while (!(TWCR & (1 << TWINT)));
		data_buffer[i] = TWDR;
	}
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	data_buffer[byte_size - 1] = TWDR;
}

