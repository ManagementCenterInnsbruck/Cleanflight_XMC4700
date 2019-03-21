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

#include <math.h>

#include "platform.h"

#if defined(USE_MAG_AK09916)

#include "build/debug.h"

#include "common/axis.h"
#include "common/maths.h"
#include "common/utils.h"

#include "drivers/bus.h"
#include "drivers/bus_i2c.h"
#include "drivers/bus_i2c_busdev.h"
#include "drivers/bus_spi.h"
#include "drivers/io.h"
#include "drivers/sensor.h"
#include "drivers/time.h"

#include "drivers/compass/compass.h"

#include "drivers/accgyro/accgyro.h"
#include "drivers/accgyro/accgyro_mpu.h"
#include "drivers/accgyro/accgyro_mpu6500.h"
#include "drivers/accgyro/accgyro_spi_mpu6500.h"
#include "drivers/accgyro/accgyro_spi_mpu9250.h"
#include "drivers/compass/compass_ak09916.h"

#include "scheduler/scheduler.h"

// This sensor is also available also part of the MPU-9250 connected to the secondary I2C bus.

// AK09916, mag sensor address
#define AK09916_MAG_I2C_ADDRESS          0x0C
#define AK09916_DEVICE_ID                0x09

// Registers
#define AK09916_MAG_REG_WIA2             0x01
#define AK09916_MAG_REG_ST1              0x10
#define AK09916_MAG_REG_HXL              0x11
#define AK09916_MAG_REG_HXH              0x12
#define AK09916_MAG_REG_HYL              0x13
#define AK09916_MAG_REG_HYH              0x14
#define AK09916_MAG_REG_HZL              0x15
#define AK09916_MAG_REG_HZH              0x16
#define AK09916_MAG_REG_ST2              0x18
#define AK09916_MAG_REG_CNTL2            0x31
#define AK09916_MAG_REG_CNTL3            0x32

#define ST1_DATA_READY                  0x01

#define ST2_MAG_SENSOR_OVERFLOW         0x08

#define CNTL2_MODE_POWER_DOWN           0x00
#define CNTL2_MODE_ONCE                 0x01

#define CNTL3_SOFT_RESET                0x01

static bool ak09916ReadRegisterBuffer(const busDevice_t *busdev, uint8_t reg, uint8_t *buf, uint8_t len)
{
    return busReadRegisterBuffer(busdev, reg, buf, len);
}

static bool ak09916WriteRegister(const busDevice_t *busdev, uint8_t reg, uint8_t data)
{
    return busWriteRegister(busdev, reg, data);
}

static bool ak09916DirectReadData(const busDevice_t *busdev, uint8_t *buf)
{
    uint8_t status;

    bool ack = ak09916ReadRegisterBuffer(busdev, AK09916_MAG_REG_ST1, &status, 1);

    if (!ack || (status & ST1_DATA_READY) == 0) {
        return false;
    }

    return ak09916ReadRegisterBuffer(busdev, AK09916_MAG_REG_HXL, buf, 8);
}

static bool ak09916Read(magDev_t *mag, int16_t *magData)
{
    bool ack = false;
    uint8_t buf[8];

    const busDevice_t *busdev = &mag->busdev;

    switch (busdev->bustype) {
#if defined(USE_MAG_AK09916)
    case BUSTYPE_I2C:
    case BUSTYPE_SPI:
        ack = ak09916DirectReadData(busdev, buf);
        break;
#endif
    default:
        break;
    }

    uint8_t status2 = buf[7];
    if (!ack) {
        return false;
    }

    ak09916WriteRegister(busdev, AK09916_MAG_REG_CNTL2, CNTL2_MODE_ONCE); // start reading again    uint8_t status2 = buf[6];

    if (status2 & ST2_MAG_SENSOR_OVERFLOW) {
        return false;
    }

    magData[X] = (buf[1] << 8) | buf[0];
    magData[Y] = (buf[3] << 8) | buf[2];
    magData[Z] = (buf[5] << 8) | buf[4];

    return true;
}

static bool ak09916Init(magDev_t *mag)
{
    uint8_t status;

    const busDevice_t *busdev = &mag->busdev;

    ak09916WriteRegister(busdev, AK09916_MAG_REG_CNTL2, CNTL2_MODE_POWER_DOWN);               // power down before entering fuse mode

    // Clear status registers
    ak09916ReadRegisterBuffer(busdev, AK09916_MAG_REG_ST1, &status, 1);
    ak09916ReadRegisterBuffer(busdev, AK09916_MAG_REG_ST2, &status, 1);

    // Trigger first measurement
    ak09916WriteRegister(busdev, AK09916_MAG_REG_CNTL2, CNTL2_MODE_ONCE);
    return true;
}

void ak09916BusInit(const busDevice_t *busdev)
{
    switch (busdev->bustype) {
#ifdef USE_MAG_AK09916
    case BUSTYPE_I2C:
        UNUSED(busdev);
        break;
#endif
    default:
        break;
    }
}

void ak09916BusDeInit(const busDevice_t *busdev)
{
    switch (busdev->bustype) {
#ifdef USE_MAG_AK09916
    case BUSTYPE_I2C:
        UNUSED(busdev);
        break;
#endif
    default:
        break;
    }
}

bool ak09916Detect(magDev_t *mag)
{
    uint8_t sig = 0;

    busDevice_t *busdev = &mag->busdev;

    if (busdev->bustype == BUSTYPE_MPU_SLAVE && busdev->busdev_u.mpuSlave.address == 0) {
        busdev->busdev_u.mpuSlave.address = AK09916_MAG_I2C_ADDRESS;
    }

    if (busdev->bustype == BUSTYPE_I2C && busdev->busdev_u.i2c.address == 0) {
        busdev->busdev_u.i2c.address = AK09916_MAG_I2C_ADDRESS;
    }

    ak09916BusInit(busdev);

    ak09916WriteRegister(busdev, AK09916_MAG_REG_CNTL3, CNTL3_SOFT_RESET);                    // reset MAG
    delay(4);

    bool ack = ak09916ReadRegisterBuffer(busdev, AK09916_MAG_REG_WIA2, &sig, 1);              // check for AK09916

    if (ack && sig == AK09916_DEVICE_ID)
    {
        mag->init = ak09916Init;
        mag->read = ak09916Read;

        return true;
    }

    ak09916BusDeInit(busdev);

    return false;
}
#endif
