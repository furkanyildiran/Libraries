#ifdef __cplusplus
extern "C" {
#endif


#ifndef __MPU6050_H__
#define __MPU6050_H__
#define F_CPU 16000000UL
#include <stdint.h>
#include "MPU6050_mnemonics.h"
#include "I2C.h"

#define mpu_x_max 0
#define mpu_x_min 1 
#define mpu_y_max 2
#define mpu_y_min 3
#define mpu_z_max 4
#define mpu_z_min 5

void MPU6050_filter(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis);
void MPU6050_calibration(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis, int16_t *max_min_buffer);
uint8_t MPU6050_init(void);
uint8_t MPU6050_read_data(int16_t *axis_X, int16_t *axis_Y, int16_t *axis_Z);
void MPU6050_reset(void);

#endif



#ifdef __cplusplus
}
#endif
