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

#include <stdint.h>

#define RX_SPI_MAX_PAYLOAD_SIZE 32

struct rxSpiConfig_s;

bool rxSpiDeviceInit(const struct rxSpiConfig_s *rxSpiConfig);
uint8_t rxSpiTransferByte(uint8_t data);
uint8_t rxSpiWriteByte(uint8_t data);
uint8_t rxSpiWriteCommand(uint8_t command, uint8_t data);
uint8_t rxSpiWriteCommandMulti(uint8_t command, const uint8_t *data, uint8_t length);
uint8_t rxSpiReadCommand(uint8_t command, uint8_t commandData);
uint8_t rxSpiReadCommandMulti(uint8_t command, uint8_t commandData, uint8_t *retData, uint8_t length);
