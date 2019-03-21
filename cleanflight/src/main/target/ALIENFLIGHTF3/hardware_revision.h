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

#pragma once

typedef enum awf3HardwareRevision_t {
    AFF3_UNKNOWN = 0,
    AFF3_REV_1, // MPU6050 (I2C)
    AFF3_REV_2  // MPU6500 / MPU9250 (SPI)
} awf3HardwareRevision_e;

extern uint8_t hardwareRevision;
extern bool haveFrSkyRX;

void updateHardwareRevision(void);
void detectHardwareRevision(void);

ioTag_t selectMPUIntExtiConfigByHardwareRevision(void);
