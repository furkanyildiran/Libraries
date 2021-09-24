#include "QMC5883L.h"

static int16_t x_axis_max = 0, x_axis_min = 0, y_axis_max = 0, y_axis_min = 0, z_axis_max = 0, z_axis_min = 0;
static uint8_t x_enable_offset = 0, y_enable_offset = 0, z_enable_offset = 0;


void QMC_x_calib_rst(void)
{
	x_axis_max = 0;
	x_axis_min = 0;
}
void QMC_y_calib_rst(void)
{
	y_axis_max = 0;
	y_axis_min = 0;
}
void QMC_z_calib_rst(void)
{
	z_axis_max = 0;
	z_axis_min = 0;
}
void QMC_x_enbl_ofst(void)
{
	x_enable_offset = 1;
}
void QMC_x_dsbl_ofst(void)
{
	x_enable_offset = 0;
}
void QMC_y_enbl_ofst(void)
{
	y_enable_offset = 1;
}
void QMC_y_dsbl_ofst(void)
{
	y_enable_offset = 0;
}
void QMC_z_enbl_ofst(void)
{
	z_enable_offset = 1;
}
void QMC_z_dsbl_ofst(void)
{
	z_enable_offset = 0;
}

void QMC_filter(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis)
{
	static uint8_t counter = 0;
	static int16_t FIFO[3][5] = {0};
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
void QMC_calibration(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis, int16_t *max_min_buffer)
{
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
void QMC_soft_reset(void)
{
	I2C_master_transmit_data(QMC_ADDRESS,QMC_CONTOL2_REG,QMC_SOFT_RESET);
}
void QMC_init(uint8_t OSR, uint8_t RNG, uint8_t ODR, uint8_t MODE)
{
  uint8_t temp = ((OSR << 6) | (RNG << 4) | (ODR << 2) | MODE);
  I2C_master_transmit_data(QMC_ADDRESS, QMC_CONTOL1_REG, temp);
  I2C_master_transmit_data(QMC_ADDRESS, QMC_SETPRD_REG, 0x01); //recommended setting from qst datasheet
}
void QMC_read_data(int16_t *axis_X, int16_t *axis_Y, int16_t *axis_Z)
{
  volatile uint8_t data_bytes[7];
  I2C_master_receive_data(QMC_ADDRESS, QMC_X_LSB_REG, data_bytes, 7);
  *axis_X = (data_bytes[1] << 8) | data_bytes[0];
  if (!(*axis_X < 7000 && *axis_X > -7000))
    *axis_X = 0;
  *axis_Y = (data_bytes[3] << 8) | data_bytes[2];
  if (!(*axis_Y < 7000 && *axis_Y > -7000))
    *axis_Y = 0;
  *axis_Z = (data_bytes[5] << 8) | data_bytes[4];
  if (!(*axis_Z < 7000 && *axis_Z > -7000))
    *axis_Z = 0;
  if (x_enable_offset == 1)  
	*axis_X -= ((x_axis_max + x_axis_min)/2);
  if (y_enable_offset == 1)
	*axis_Y -= ((y_axis_max + y_axis_min)/2);
  if (z_enable_offset == 1)  
	*axis_Z -= ((z_axis_max + z_axis_min)/2);
}

