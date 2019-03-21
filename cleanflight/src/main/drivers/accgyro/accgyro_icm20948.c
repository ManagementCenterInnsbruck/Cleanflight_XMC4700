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
#include <stdlib.h>

#include "platform.h"

#include "common/axis.h"
#include "common/maths.h"

#include "drivers/accgyro/accgyro.h"
#include "drivers/accgyro/accgyro_mpu.h"
#include "drivers/accgyro/accgyro_icm20948.h"
#include "drivers/bus_spi.h"
#include "drivers/exti.h"
#include "drivers/io.h"
#include "drivers/sensor.h"
#include "drivers/time.h"


uint8_t icm20948Detect(const busDevice_t *bus)
{
	busWriteRegister(bus, ICM20948_RA_REG_BANK_SEL, 0 << 4); // select bank 0 just to be safe
    delay(15);

    busWriteRegister(bus, ICM20948_RA_PWR_MGMT_1, ICM20948_BIT_RESET);

    uint8_t icmDetected = MPU_NONE;
    uint8_t attemptsRemaining = 20;
    do {
        delay(150);
        const uint8_t whoAmI = busReadRegister(bus, ICM20948_RA_WHO_AM_I);
        if (whoAmI == ICM20948_WHO_AM_I_CONST) {
            icmDetected = ICM_20948_I2C;
        } else {
            icmDetected = MPU_NONE;
        }
        if (icmDetected != MPU_NONE) {
            break;
        }
        if (!attemptsRemaining) {
            return MPU_NONE;
        }
    } while (attemptsRemaining--);

    return icmDetected;

}

void icm20948AccInit(accDev_t *acc)
{
	// 4,096 LSB/g 8g
    // 2,048 LSB/g 16g
    acc->acc_1G = acc->acc_high_fsr ? 2048 : 4096;

    busWriteRegister(&acc->bus, ICM20948_RA_REG_BANK_SEL, 2 << 4); // config in bank 2
    delay(15);
    const uint8_t acc_fsr = acc->acc_high_fsr ? ICM20948_FSR_16G : ICM20948_FSR_8G;
    busWriteRegister(&acc->bus, ICM20948_RA_ACCEL_CONFIG, acc_fsr << 1);
    delay(15);
    busWriteRegister(&acc->bus, ICM20948_RA_REG_BANK_SEL, 0 << 4); // back to bank 0
    delay(15);
}

bool icm20948AccDetect(accDev_t *acc)
{
    if (acc->mpuDetectionResult.sensor != ICM_20948_I2C) {
        return false;
    }

    acc->initFn = icm20948AccInit;
    acc->readFn = icm20948AccRead;

    return true;
}


void icm20948GyroInit(gyroDev_t *gyro)
{
    mpuGyroInit(gyro);

    busWriteRegister(&gyro->bus, ICM20948_RA_REG_BANK_SEL, 0 << 4); // select bank 0 just to be safe
    delay(15);
    busWriteRegister(&gyro->bus, ICM20948_RA_PWR_MGMT_1, ICM20948_BIT_RESET);
    delay(100);
    busWriteRegister(&gyro->bus, ICM20948_RA_PWR_MGMT_1, INV_CLK_PLL);
    delay(15);
    busWriteRegister(&gyro->bus, ICM20948_RA_REG_BANK_SEL, 2 << 4); // config in bank 2
    delay(15);
    const uint8_t gyro_fsr = gyro->gyro_high_fsr ? ICM20948_FSR_2000DPS : ICM20948_FSR_1000DPS;

    uint8_t raGyroConfigData = gyro->gyroRateKHz > GYRO_RATE_1100_Hz ? 0 : 1; // deactivate GYRO_FCHOICE for sample rates over 1kHz (opposite of other invensense chips)
    raGyroConfigData |= gyro_fsr << 1;
    busWriteRegister(&gyro->bus, ICM20948_RA_GYRO_CONFIG_1, raGyroConfigData);
    delay(15);
    busWriteRegister(&gyro->bus, ICM20948_RA_GYRO_SMPLRT_DIV, gyro->mpuDividerDrops); // Get Divider Drops
    delay(100);

    // Data ready interrupt configuration
    // back to bank 0
    busWriteRegister(&gyro->bus, ICM20948_RA_REG_BANK_SEL, 0 << 4);
    delay(15);
    busWriteRegister(&gyro->bus, ICM20948_RA_INT_PIN_CFG, 0x12);  // INT_ANYRD_2CLEAR, BYPASS_EN
    delay(15);

#ifdef USE_MPU_DATA_READY_SIGNAL
    busWriteRegister(&gyro->bus, ICM20948_RA_INT_ENABLE_1, 0x01);
#endif
}

bool icm20948GyroDetect(gyroDev_t *gyro)
{
    if (gyro->mpuDetectionResult.sensor != ICM_20948_I2C)
        return false;

    gyro->initFn = icm20948GyroInit;
    gyro->readFn = icm20948GyroRead;

    // 32.8 dps/lsb 1kDps
    // 16.4 dps/lsb 2kDps
    gyro->scale = 1.0f / (gyro->gyro_high_fsr ? 16.4f : 32.8f);

    return true;
}

bool icm20948GyroRead(gyroDev_t *gyro)
{
    uint8_t data[6];

    const bool ack = busReadRegisterBuffer(&gyro->bus, ICM20948_RA_GYRO_XOUT_H, data, 6);
    if (!ack) {
        return false;
    }

    gyro->gyroADCRaw[X] = (int16_t)((data[0] << 8) | data[1]);
    gyro->gyroADCRaw[Y] = (int16_t)((data[2] << 8) | data[3]);
    gyro->gyroADCRaw[Z] = (int16_t)((data[4] << 8) | data[5]);

    return true;
}

bool icm20948AccRead(accDev_t *acc)
{
    uint8_t data[6];

    const bool ack = busReadRegisterBuffer(&acc->bus, ICM20948_RA_ACCEL_XOUT_H, data, 6);
    if (!ack) {
        return false;
    }

    acc->ADCRaw[X] = (int16_t)((data[0] << 8) | data[1]);
    acc->ADCRaw[Y] = (int16_t)((data[2] << 8) | data[3]);
    acc->ADCRaw[Z] = (int16_t)((data[4] << 8) | data[5]);

    return true;
}
