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

#include "drivers/bus.h"
#include "drivers/sensor.h"
#include "drivers/exti.h"

typedef struct magDev_s {
    sensorMagInitFuncPtr init;                              // initialize function
    sensorMagReadFuncPtr read;                              // read 3 axis data function
    extiCallbackRec_t exti;
    busDevice_t busdev;
    sensor_align_e magAlign;
    ioTag_t magIntExtiTag;
    int16_t magGain[3];
} magDev_t;

#ifndef MAG_I2C_INSTANCE
#define MAG_I2C_INSTANCE I2C_DEVICE
#endif
