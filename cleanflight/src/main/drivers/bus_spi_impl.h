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

#if defined(STM32F1) || defined(STM32F3) || defined(STM32F4)
#define MAX_SPI_PIN_SEL 2
#elif defined(XMC4700_F100x2048)

#include "drivers/serial.h"
#define SPIS_BUFFER_SIZE 512
#define MAX_SPI_PIN_SEL 6
#else
#define MAX_SPI_PIN_SEL 4
#endif

typedef struct spiPinDef_s {
    ioTag_t pin;
#if STM32F7
    uint8_t af;
#endif
#ifdef XMC4700_F100x2048
    uint8_t af;
    uint8_t src;
#endif
} spiPinDef_t;

typedef struct spiHardware_s {
    SPIDevice device;
    SPI_TypeDef *reg;
    spiPinDef_t sckPins[MAX_SPI_PIN_SEL];
    spiPinDef_t misoPins[MAX_SPI_PIN_SEL];
    spiPinDef_t mosiPins[MAX_SPI_PIN_SEL];
#ifdef XMC4700_F100x2048
    spiPinDef_t csPins[MAX_SPI_PIN_SEL];
    uint8_t txIrq;
    uint8_t rxIrq;
    uint8_t txPriority;
    uint8_t rxPriority;
#endif
#if !(defined(STM32F7) || defined(XMC4700_F100x2048))
    uint8_t af;
#endif
    rccPeriphTag_t rcc;
#if defined(USE_HAL_DRIVER)
    uint8_t dmaIrqHandler;
#endif
} spiHardware_t;

extern const spiHardware_t spiHardware[];

typedef struct SPIDevice_s {
#ifdef XMC4700_F100x2048
	serialPort_t port;
#endif
    SPI_TypeDef *dev;
    ioTag_t sck;
    ioTag_t miso;
    ioTag_t mosi;
#if defined(STM32F7)
    uint8_t sckAF;
    uint8_t misoAF;
    uint8_t mosiAF;
#elif defined(XMC4700_F100x2048)
    ioTag_t cs;
    uint8_t sckAF;
    uint8_t misoAF;
    uint8_t mosiAF;
    uint8_t csAF;
    uint8_t sckSRC;
    uint8_t misoSRC;
    uint8_t mosiSRC;
    uint8_t csSRC;

    uint8_t txIrq;
    uint8_t rxIrq;
    uint8_t txPriority;
    uint8_t rxPriority;

    volatile uint8_t rxBuffer[SPIS_BUFFER_SIZE];
    volatile uint8_t txBuffer[SPIS_BUFFER_SIZE];
#else
    uint8_t af;
#endif
    rccPeriphTag_t rcc;
    volatile uint16_t errorCount;
    bool leadingEdge;
#if defined(USE_HAL_DRIVER)
    SPI_HandleTypeDef hspi;
    DMA_HandleTypeDef hdma;
    uint8_t dmaIrqHandler;
#endif
} spiDevice_t;

extern spiDevice_t spiDevice[SPIDEV_COUNT];

void spiInitDevice(SPIDevice device);
uint32_t spiTimeoutUserCallback(SPI_TypeDef *instance);
