/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "build/build_config.h"

#include "barometer.h"

#include "drivers/bus.h"
#include "drivers/bus_i2c.h"
#include "drivers/bus_i2c_busdev.h"
#include "drivers/io.h"
#include "drivers/time.h"

#include "barometer_dps310.h"

#ifdef USE_BARO

typedef struct {
	// coefficients to calculate physical values
	int32_t c00; /**< coefficients to calculate physical values */
	int32_t c10; /**< coefficients to calculate physical values */
	int32_t c20; /**< coefficients to calculate physical values */
	int32_t c30; /**< coefficients to calculate physical values */
	int32_t c01; /**< coefficients to calculate physical values */
	int32_t c11; /**< coefficients to calculate physical values */
	int32_t c21; /**< coefficients to calculate physical values */
	int32_t c0; /**< coefficients to calculate physical values */
	int32_t c1; /**< coefficients to calculate physical values */
	// compensation scale factors (data sheet page 15, table 9)
	uint32_t kP; /**< compensation scale factor for pressure measurement (data sheet page 15, table 9) */
	uint32_t kT; /**< compensation scale factor for temperature measurement (data sheet page 15, table 9) */
} dps310_calibration_param_t;

typedef struct {
	dps310_calibration_param_t cal_param;
	uint8_t chip_id;
	uint8_t dev_addr;
} dps310_t;

#define DPS310_ID 0x10
#define DPS310_PROM_DATA__LEN1 18
#define DPS310_PROM_DATA__LEN2 6

#define DPS310_PSR_B2 0x00
#define DPS310_PSR_B1 0x01
#define DPS310_PSR_B0 0x02
#define DPS310_TMP_B2 0x03
#define DPS310_TMP_B1 0x04
#define DPS310_TMP_B0 0x05
#define DPS310_PRS_CFG 0x06 ///pressure config register
#define DPS310_TMP_CFG 0x07 ///temperature config register
#define DPS310_MEAS_CFG 0x08 ///Sensor Operating mode register
#define DPS310_CFG_REG 0x09///Interrupt and FIFO-config
#define DPS310_INT_STS 0x0A///Interrupt status register
#define DPS310_RESET_REGISTER 0x0C///reset register of sensor
#define DPS310_PRODUCT_ID 0x0D ///ID of Sensor
#define DPS310_COEF_SRC 0x28///Temperature coefficient source
#define DPS310_CAL_COEF_START_ADDR1 0x10
#define DPS310_CAL_COEF_START_ADDR2 0x1A

//reset
#define DPS310_SOFT_RESET 0x09///sequence to perform soft-reset
#define DPS310_FIFO_FLUSH 0x80///flush FIFO-Buffer

//sensor operating mode and status register-config
#define DPS310_MEAS_CTRL_IDLE 0x00
#define DPS310_MEAS_CTRL_TEMP_SINGLE 0x02
#define DPS310_MEAS_CTRL_PRESSURE_SINGLE 0x01
#define DPS310_MEAS_CTRL_CONTINUES_TEMP_PRESSURE 0x07
#define DPS310_MEAS_CTRL_CONTINUES_TEMP 0x06
#define DPS310_MEAS_CTRL_CONTINUES_PRESSURE 0x05

//pressure-config
#define DPS310_PM_RATE_128 0x70 ///128 messungen/sec
#define DPS310_PM_PRC_128 0x07 ///pressure oversampling rate -128 times

#define DPS310_PM_RATE_64 0x60 ///64 messungen/sec
#define DPS310_PM_PRC_64 0x06 ///pressure oversampling rate -64 times

#define DPS310_PM_RATE_32 0x50 ///32 messungen/sec
#define DPS310_PM_PRC_32 0x05 ///pressure oversampling rate -32 times

#define DPS310_PM_RATE_16 0x40 ///16 messungen/sec
#define DPS310_PM_PRC_16 0x04 ///pressure oversampling rate -16 times

#define DPS310_PM_RATE_8 0x30 ///8 messungen/sec
#define DPS310_PM_PRC_8 0x03 ///pressure oversampling rate -8 times

#define DPS310_PM_RATE_4 0x20 ///4 messungen/sec
#define DPS310_PM_PRC_4 0x02 ///pressure oversampling rate -4 times

#define DPS310_PM_RATE_2 0x10 ///2 messungen/sec
#define DPS310_PM_PRC_2 0x01 ///pressure oversampling rate -2 times

#define DPS310_PM_RATE_1 0x00 ///1 messungen/sec
#define DPS310_PM_PRC_1 0x00 ///pressure oversampling rate -1 time

//temp-config
#define DPS310_TMP_RATE_128 0x70 ///128 messungen/sec
#define DPS310_TMP_PRC_128 0x07 ///temp oversampling rate -128 times

#define DPS310_TMP_RATE_64 0x60 ///64 messungen/sec
#define DPS310_TMP_PRC_64 0x06 ///temp oversampling rate -64 times

#define DPS310_TMP_RATE_32 0x50 ///32 messungen/sec
#define DPS310_TMP_PRC_32 0x05 ///temp oversampling rate -32 times

#define DPS310_TMP_RATE_16 0x40 ///16 messungen/sec
#define DPS310_TMP_PRC_16 0x04 ///temp oversampling rate -16 times

#define DPS310_TMP_RATE_8 0x30 ///8 messungen/sec
#define DPS310_TMP_PRC_8 0x03 ///temp oversampling rate -8 times

#define DPS310_TMP_RATE_4 0x20 ///4 messungen/sec
#define DPS310_TMP_PRC_4 0x02 ///temp oversampling rate -4 times

#define DPS310_TMP_RATE_2 0x10 ///2 messungen/sec
#define DPS310_TMP_PRC_2 0x01 ///temp oversampling rate -2 times

#define DPS310_TMP_RATE_1 0x00 ///1 messungen/sec
#define DPS310_TMP_PRC_1 0x00 ///temp oversampling rate -1 time

#define DPS310_UT_DELAY    5000
#define DPS310_UP_DELAY    30000

STATIC_UNIT_TESTED dps310_t dps310;

static bool dps310InitDone = false;
STATIC_UNIT_TESTED uint32_t dps310_ut;  // static result of temperature measurement
STATIC_UNIT_TESTED int32_t dps310_up;  // static result of pressure measurement

float up_sc = 0.0f;
float ut_sc = 0.0f;

static void dps310_start_ut(baroDev_t *baro) {

	busWriteRegister(&baro->busdev, DPS310_MEAS_CFG, DPS310_MEAS_CTRL_TEMP_SINGLE);
}

static void dps310_get_ut(baroDev_t *baro) {

	uint8_t data[3];

	uint8_t temp_ready = busReadRegister(&baro->busdev, DPS310_MEAS_CFG);

	if (temp_ready & 0x20)
	{
		busReadRegisterBuffer(&baro->busdev, DPS310_TMP_B2, data, 3);

		dps310_ut = (uint32_t)data[0] << 16 | (uint32_t)data[1] << 8 | (uint32_t)data[2];
		if(dps310_ut & ((uint32_t)1 << 23))
			dps310_ut -= (uint32_t)1 << 24;
	}
}

static void dps310_start_up(baroDev_t *baro) {

	busWriteRegister(&baro->busdev, DPS310_MEAS_CFG, DPS310_MEAS_CTRL_PRESSURE_SINGLE);
}

static void dps310_get_up(baroDev_t *baro) {

	uint8_t data[3];

	uint8_t pressure_ready = busReadRegister(&baro->busdev, DPS310_MEAS_CFG);

	if (pressure_ready & 0x10)
	{
		busReadRegisterBuffer(&baro->busdev, DPS310_PSR_B2, data, 3);
		dps310_up = (uint32_t)data[0] << 16 | (uint32_t)data[1] << 8 | (uint32_t)data[2];
		if(dps310_up & ((uint32_t)1 << 23))
			dps310_up -= (uint32_t)1 << 24;
	}
}

static void dps310_get_cal_param(baroDev_t *baro) {

	uint8_t data[DPS310_PROM_DATA__LEN1];

	busReadRegisterBuffer(&baro->busdev, DPS310_CAL_COEF_START_ADDR1, data, DPS310_PROM_DATA__LEN1);

	dps310.cal_param.c0 = ((uint32_t)data[0] << 4) | (((uint32_t)data[1] >> 4) & 0x0F);
	if(dps310.cal_param.c0 & ((uint32_t)1 << 11))
		dps310.cal_param.c0 -= (uint32_t)1 << 12;

	dps310.cal_param.c1 = (((uint32_t)data[1] & 0x0F) << 8) | (uint32_t)data[2];
	if(dps310.cal_param.c1 & ((uint32_t)1 << 11))
		dps310.cal_param.c1 -= (uint32_t)1 << 12;

	dps310.cal_param.c00 =   ((uint32_t)data[3] << 12) | ((uint32_t)data[4] << 4) | (((uint32_t)data[5] >> 4) & 0x0F);
	if(dps310.cal_param.c00 & ((uint32_t)1 << 19))
		dps310.cal_param.c00 -= (uint32_t)1 << 20;

	dps310.cal_param.c10 =   (((uint32_t)data[5] & 0x0F) << 16)	| ((uint32_t)data[6] << 8)| (uint32_t)data[7];
	if(dps310.cal_param.c10 & ((uint32_t)1<<19))
		dps310.cal_param.c10 -= (uint32_t)1 << 20;

	dps310.cal_param.c01 =   ((uint32_t)data[8] << 8) | (uint32_t)data[9];
	if(dps310.cal_param.c01 & ((uint32_t)1 << 15))
		dps310.cal_param.c01 -= (uint32_t)1 << 16;

	dps310.cal_param.c11 =   ((uint32_t)data[10] << 8) | (uint32_t)data[11];
	if(dps310.cal_param.c11 & ((uint32_t)1 << 15))
		dps310.cal_param.c11 -= (uint32_t)1 << 16;

	dps310.cal_param.c20 =   ((uint32_t)data[12] << 8) | (uint32_t)data[13];
	if(dps310.cal_param.c20 & ((uint32_t)1 << 15))
		dps310.cal_param.c20 -= (uint32_t)1 << 16;

	dps310.cal_param.c21 =   ((uint32_t)data[14] << 8) | (uint32_t)data[15];
	if(dps310.cal_param.c21 & ((uint32_t)1 << 15))
		dps310.cal_param.c21 -= (uint32_t)1 << 16;

	dps310.cal_param.c30 =   ((uint32_t)data[16] << 8) | (uint32_t)data[17];
	if(dps310.cal_param.c30 & ((uint32_t)1 << 15))
		dps310.cal_param.c30 -= (uint32_t)1 << 16;
}

static int32_t dps310_get_temperature(uint32_t ut) {

	int32_t temperature;

	// calculate physical temperature Tcomp [°C]
	ut_sc = (float) ut / dps310.cal_param.kT;
	temperature = (int32_t)(dps310.cal_param.c0 * 0.5 + dps310.cal_param.c1 * ut_sc) ;

	return temperature;
}

static int32_t dps310_get_pressure(int32_t up) {

	float pressure;

	// calculate physical pressure Pcomp [Pa]
	up_sc = (float) up / dps310.cal_param.kP;

	//Calculate compensated pressure
	pressure =   dps310.cal_param.c00
			+ up_sc * (dps310.cal_param.c10 + up_sc * (dps310.cal_param.c20 + up_sc * dps310.cal_param.c30))
			+ ut_sc * (dps310.cal_param.c01 + up_sc * (dps310.cal_param.c11 + up_sc * dps310.cal_param.c21));
	return (int32_t)pressure;
}

static void dps310_calculate(int32_t *pressure, int32_t *temperature)
{
	int32_t temp, press;

	temp = dps310_get_temperature(dps310_ut);
	press = dps310_get_pressure(dps310_up);
	if (pressure)
		*pressure = press;
	if (temperature)
		*temperature = temp;
}


bool dps310Detect(baroDev_t *baro)
{
	if (dps310InitDone)
		return true;

	delay(10);

    if ((baro->busdev.bustype == BUSTYPE_I2C) && (baro->busdev.busdev_u.i2c.address == 0)) {
    	baro->busdev.busdev_u.i2c.address = BARO_I2C_ADDRESS;
    }

	uint8_t chipId = busReadRegister(&baro->busdev, DPS310_PRODUCT_ID);

	if (chipId == DPS310_ID)
	{
		busWriteRegister(&baro->busdev, DPS310_RESET_REGISTER, DPS310_SOFT_RESET);
		delay(50);

		dps310_get_cal_param(baro);

		busWriteRegister(&baro->busdev, DPS310_MEAS_CFG, DPS310_MEAS_CTRL_IDLE);
		busWriteRegister(&baro->busdev, DPS310_RESET_REGISTER, DPS310_FIFO_FLUSH);
		busWriteRegister(&baro->busdev, DPS310_CFG_REG, 0x04);

		uint8_t T_config =  DPS310_TMP_PRC_1;
		dps310.cal_param.kT = 524288;

		uint8_t data = busReadRegister(&baro->busdev, DPS310_COEF_SRC);

		if (data & 0x80)
			busWriteRegister(&baro->busdev, DPS310_TMP_CFG, 0x80| T_config);		// use external sensor (MEMS)
		else
			busWriteRegister(&baro->busdev, DPS310_TMP_CFG, T_config);			// use internal sensor (ASIC)

		uint8_t P_config =  DPS310_PM_PRC_16;
		dps310.cal_param.kP = 253952;

		busWriteRegister(&baro->busdev, DPS310_PRS_CFG, P_config);

		do
		{
			busWriteRegister(&baro->busdev, DPS310_MEAS_CFG, DPS310_MEAS_CTRL_TEMP_SINGLE);
			delay(10);
			data = busReadRegister(&baro->busdev, DPS310_MEAS_CFG);

		} while((data & 0x20) == 0);

		busWriteRegister(&baro->busdev, DPS310_MEAS_CFG, DPS310_MEAS_CTRL_IDLE);

		// fix possible hardware problem
		busWriteRegister(&baro->busdev, 0x0E, 0xA5);
		busWriteRegister(&baro->busdev, 0x0F, 0x96);
		busWriteRegister(&baro->busdev, 0x62, 0x02);
		busWriteRegister(&baro->busdev, 0x0E, 0x00);
		busWriteRegister(&baro->busdev, 0x0F, 0x00);

		do
		{
			busWriteRegister(&baro->busdev, DPS310_MEAS_CFG, DPS310_MEAS_CTRL_TEMP_SINGLE);
			delay(10);
			data = busReadRegister(&baro->busdev, DPS310_MEAS_CFG);

		} while((data & 0x20) == 0);

		busWriteRegister(&baro->busdev, DPS310_MEAS_CFG, DPS310_MEAS_CTRL_IDLE);

		baro->ut_delay = DPS310_UT_DELAY;
		baro->start_ut = dps310_start_ut;
		baro->get_ut = dps310_get_ut;

		baro->up_delay = DPS310_UP_DELAY;
		baro->start_up = dps310_start_up;
		baro->get_up = dps310_get_up;

		baro->calculate = dps310_calculate;

		dps310InitDone = true;
	}
    return true;
}

#endif /* BARO */
