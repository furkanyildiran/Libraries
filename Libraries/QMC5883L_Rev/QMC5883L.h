#ifdef __cplusplus
extern "C" {
#endif


#ifndef __QMC5883L_H__
#define __QMC5883L_H__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include "I2C.h"
#include "QMC5883L_mnemonics.h"

#define qmc_x_max 0
#define qmc_x_min 1 
#define qmc_y_max 2
#define qmc_y_min 3
#define qmc_z_max 4
#define qmc_z_min 5

void QMC_x_calib_rst(void);
void QMC_y_calib_rst(void);
void QMC_z_calib_rst(void);
void QMC_x_enbl_ofst(void);
void QMC_x_dsbl_ofst(void);
void QMC_y_enbl_ofst(void);
void QMC_y_dsbl_ofst(void);
void QMC_z_enbl_ofst(void);
void QMC_z_dsbl_ofst(void);
void QMC_filter(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis);
void QMC_calibration(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis, int16_t *max_min_buffer);
void QMC_soft_reset(void);
void QMC_init(uint8_t OSR, uint8_t RNG, uint8_t ODR, uint8_t MODE);
void QMC_read_data(int16_t *axis_X, int16_t *axis_Y, int16_t *axis_Z);

#endif


#ifdef __cplusplus
}
#endif