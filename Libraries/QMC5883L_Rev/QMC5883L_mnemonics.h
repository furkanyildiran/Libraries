#ifndef __QMC5883L_MNEMONICS__
#define __QMC5883L_MNEMONICS__


#define QMC_ADDRESS 0x0D
#define QMC_X_LSB_REG 0x00
#define QMC_X_MSB_REG 0x01
#define QMC_Y_LSB_REG 0x02
#define QMC_Y_MSB_REG 0x03
#define QMC_Z_LSB_REG 0x04
#define QMC_Z_MSB_REG 0x05
#define QMC_STATUS_REG 0x06
#define QMC_TMPTR_LSB_REG 0x07
#define QMC_TMPTR_MSB_REG 0x08
#define QMC_CONTOL1_REG 0x09
#define QMC_CONTOL2_REG 0x0A
#define QMC_SETPRD_REG 0x0B
#define QMC_CHIP_ID 0x0D
#define QMC_OSR_64 0b11
#define QMC_OSR_128 0b10
#define QMC_OSR_256 0b01
#define QMC_OSR_512 0b00
#define QMC_RNG_8G 0b01
#define QMC_RNG_2G 0b00
#define QMC_ODR_200HZ 0b11
#define QMC_ODR_100HZ 0b10
#define QMC_ODR_50HZ 0b01
#define QMC_ODR_10HZ 0b00
#define QMC_MODE_CONTINUOUS 0b01
#define QMC_MODE_STANDBY 0b00
#define QMC_SOFT_RESET 0x80

#endif