#include "MPU6050.h"

void MPU6050_filter(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis)
{
  static uint8_t counter = 0;	
  static int32_t FIFO[3][5] = {0};
  if (counter == 0)
  {
    FIFO[0][0] = *x_axis;
    FIFO[1][0] = *y_axis;
    FIFO[2][0] = *z_axis;
    *x_axis = FIFO[0][0];
    *y_axis = FIFO[1][0];
    *z_axis = FIFO[2][0];
    counter++;
  }
  else if (counter == 1)
  {
    FIFO[0][1] = *x_axis;
    FIFO[1][1] = *y_axis;
    FIFO[2][1] = *z_axis;
    *x_axis = (FIFO[0][0] + FIFO[0][1]) / 2;
    *y_axis = (FIFO[1][0] + FIFO[1][1]) / 2;
    *z_axis = (FIFO[2][0] + FIFO[2][1]) / 2;
    counter++;
  }
  else if (counter == 2)
  {
    FIFO[0][2] = *x_axis;
    FIFO[1][2] = *y_axis;
    FIFO[2][2] = *z_axis;
    *x_axis = (FIFO[0][0] + FIFO[0][1] + FIFO[0][2]) / 3;
    *y_axis = (FIFO[1][0] + FIFO[1][1] + FIFO[1][2]) / 3;
    *z_axis = (FIFO[2][0] + FIFO[2][1] + FIFO[2][2]) / 3;
    counter++;
  }
  else if (counter == 3)
  {
    FIFO[0][3] = *x_axis;
    FIFO[1][3] = *y_axis;
    FIFO[2][3] = *z_axis;
    *x_axis = (FIFO[0][0] + FIFO[0][1] + FIFO[0][2] + FIFO[0][3]) / 4;
    *y_axis = (FIFO[1][0] + FIFO[1][1] + FIFO[1][2] + FIFO[1][3]) / 4;
    *z_axis = (FIFO[2][0] + FIFO[2][1] + FIFO[2][2] + FIFO[2][3]) / 4;
    counter++;
  }
  else if (counter == 4)
  {
    FIFO[0][4] = *x_axis;
    FIFO[1][4] = *y_axis;
    FIFO[2][4] = *z_axis;
    *x_axis = (FIFO[0][0] + FIFO[0][1] + FIFO[0][2] + FIFO[0][3] + FIFO[0][4]) / 5;
    *y_axis = (FIFO[1][0] + FIFO[1][1] + FIFO[1][2] + FIFO[1][3] + FIFO[1][4]) / 5;
    *z_axis = (FIFO[2][0] + FIFO[2][1] + FIFO[2][2] + FIFO[2][3] + FIFO[2][4]) / 5;
    counter++;
  }
  else if (counter == 5)
  {
    FIFO[0][0] = FIFO[0][1];
    FIFO[0][1] = FIFO[0][2];
    FIFO[0][2] = FIFO[0][3];
    FIFO[0][3] = FIFO[0][4];
    FIFO[0][4] = *x_axis;

    FIFO[1][0] = FIFO[1][1];
    FIFO[1][1] = FIFO[1][2];
    FIFO[1][2] = FIFO[1][3];
    FIFO[1][3] = FIFO[1][4];
    FIFO[1][4] = *y_axis;

    FIFO[2][0] = FIFO[2][1];
    FIFO[2][1] = FIFO[2][2];
    FIFO[2][2] = FIFO[2][3];
    FIFO[2][3] = FIFO[2][4];
    FIFO[2][4] = *z_axis;

    *x_axis = (FIFO[0][0] + FIFO[0][1] + FIFO[0][2] + FIFO[0][3] + FIFO[0][4]) / 5;
    *y_axis = (FIFO[1][0] + FIFO[1][1] + FIFO[1][2] + FIFO[1][3] + FIFO[1][4]) / 5;
    *z_axis = (FIFO[2][0] + FIFO[2][1] + FIFO[2][2] + FIFO[2][3] + FIFO[2][4]) / 5;
  }
}
void MPU6050_calibration(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis, int16_t *max_min_buffer)
{
  static int32_t x_axis_max = 0, x_axis_min = 0, y_axis_max = 0, y_axis_min = 0, z_axis_max = 0, z_axis_min = 0;

  if (x_axis_max < *x_axis)
    x_axis_max = *x_axis;
  if (x_axis_min > *x_axis)
    x_axis_min = *x_axis;
  if (y_axis_max < *y_axis)
    y_axis_max = *y_axis;
  if (y_axis_min > *y_axis)
    y_axis_min = *y_axis;
  if (z_axis_max < *z_axis)
    z_axis_max = *z_axis;
  if (z_axis_min > *z_axis)
    z_axis_min = *z_axis;
  max_min_buffer[0] = x_axis_max;
  max_min_buffer[1] = x_axis_min;
  max_min_buffer[2] = y_axis_max;
  max_min_buffer[3] = y_axis_min;
  max_min_buffer[4] = z_axis_max;
  max_min_buffer[5] = z_axis_min;
}

uint8_t MPU6050_init(void)
{
  if (I2C_master_transmit_data(MPU_ADDRESS, MPU_RA_PWR_MGMT_1, 0x00))
    return 1;
  if (I2C_master_transmit_data(MPU_ADDRESS, MPU_RA_CONFIG, 0x01))
    return 1;
  if (I2C_master_transmit_data(MPU_ADDRESS, MPU_RA_GYRO_CONFIG, 1 << 4))
    return 1;
  if (I2C_master_transmit_data(MPU_ADDRESS, MPU_RA_ACCEL_CONFIG, 0x00))
    return 1;
  if (I2C_master_transmit_data(MPU_ADDRESS, MPU_RA_SIGNAL_PATH_RESET, 0x00))
    return 1;
  return 0;
}

uint8_t MPU6050_read_data(int16_t *axis_X, int16_t *axis_Y, int16_t *axis_Z)
{
  volatile uint8_t xh, xl, yh, yl, zh, zl;

  if (I2C_master_receive_data(MPU_ADDRESS, MPU_RA_ACCEL_XOUT_H, &xh, 1))
    return 1;
  if (I2C_master_receive_data(MPU_ADDRESS, MPU_RA_ACCEL_XOUT_L, &xl, 1))
    return 1;
  *axis_X = (xh << 8) | xl;
  if (!(*axis_X < 19000 && *axis_X > -19000))
    *axis_X = 0;
  if (I2C_master_receive_data(MPU_ADDRESS, MPU_RA_ACCEL_YOUT_H, &yh, 1))
    return 1;
  if (I2C_master_receive_data(MPU_ADDRESS, MPU_RA_ACCEL_YOUT_L, &yl, 1))
    return 1;
  *axis_Y = (yh << 8) | yl;
  if (!(*axis_Y < 19000 && *axis_Y > -19000))
    *axis_Y = 0;
  if (I2C_master_receive_data(MPU_ADDRESS, MPU_RA_ACCEL_ZOUT_H, &zh, 1))
    return 1;
  if (I2C_master_receive_data(MPU_ADDRESS, MPU_RA_ACCEL_ZOUT_L, &zl, 1))
    return 1;
  *axis_Z = (zh << 8) | zl;
  if (!(*axis_Z < 19000 && *axis_Z > -19000))
    *axis_Z = 0;
  return 0;
}
void MPU6050_reset(void)
{
  I2C_master_transmit_data(MPU_ADDRESS, MPU_RA_SIGNAL_PATH_RESET, 0x07);
  I2C_master_transmit_data(MPU_ADDRESS, MPU_RA_PWR_MGMT_1, 128);
}

