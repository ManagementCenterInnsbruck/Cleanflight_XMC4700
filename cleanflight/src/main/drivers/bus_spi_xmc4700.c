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
#include <string.h>
#include <stdlib.h>

#include "platform.h"

#if defined(USE_SPI)

#include "common/utils.h"

#include "drivers/bus.h"
#include "drivers/bus_spi.h"
#include "drivers/bus_spi_impl.h"
#include "drivers/dma.h"
#include "drivers/io.h"
#include "drivers/nvic.h"
#include "drivers/rcc.h"
#include "drivers/serial_spi_slave.h"

spiDevice_t spiDevice[SPIDEV_COUNT];

#ifndef SPI2_SCK_PIN
#define SPI2_NSS_PIN    PB12
#define SPI2_SCK_PIN    PB13
#define SPI2_MISO_PIN   PB14
#define SPI2_MOSI_PIN   PB15
#endif

#ifndef SPI3_SCK_PIN
#define SPI3_NSS_PIN    PA15
#define SPI3_SCK_PIN    PB3
#define SPI3_MISO_PIN   PB4
#define SPI3_MOSI_PIN   PB5
#endif

#ifndef SPI4_SCK_PIN
#define SPI4_NSS_PIN    PA15
#define SPI4_SCK_PIN    PB3
#define SPI4_MISO_PIN   PB4
#define SPI4_MOSI_PIN   PB5
#endif

#ifndef SPI1_NSS_PIN
#define SPI1_NSS_PIN NONE
#endif
#ifndef SPI2_NSS_PIN
#define SPI2_NSS_PIN NONE
#endif
#ifndef SPI3_NSS_PIN
#define SPI3_NSS_PIN NONE
#endif
#ifndef SPI4_NSS_PIN
#define SPI4_NSS_PIN NONE
#endif

#define SPI_DEFAULT_TIMEOUT 10

void spiInitDevice(SPIDevice device)
{
    spiDevice_t *spi = &(spiDevice[device]);

#ifdef SDCARD_SPI_INSTANCE
    if (spi->dev == SDCARD_SPI_INSTANCE) {
        spi->leadingEdge = true;
    }
#endif
#ifdef RX_SPI_INSTANCE
    if (spi->dev == RX_SPI_INSTANCE) {
        spi->leadingEdge = true;
    }
#endif

    XMC_SPI_CH_CONFIG_t config =
    {
    	.baudrate 		= 1000000U,
		.bus_mode 		= XMC_SPI_CH_BUS_MODE_MASTER,
		.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
		.parity_mode	= XMC_USIC_CH_PARITY_MODE_NONE,
    };
    XMC_SPI_CH_Init((XMC_USIC_CH_t*)spi->dev, &config);

    XMC_SPI_CH_DisableFEM((XMC_USIC_CH_t*)spi->dev);
    XMC_SPI_CH_SetBitOrderMsbFirst((XMC_USIC_CH_t*)spi->dev);
    XMC_SPI_CH_SetWordLength((XMC_USIC_CH_t*)spi->dev, 8);
    XMC_SPI_CH_SetFrameLength((XMC_USIC_CH_t*)spi->dev, 64);

    IOInit(IOGetByTag(spi->sck),  OWNER_SPI_SCK,  RESOURCE_INDEX(device));
    IOInit(IOGetByTag(spi->miso), OWNER_SPI_MISO, RESOURCE_INDEX(device));
    IOInit(IOGetByTag(spi->mosi), OWNER_SPI_MOSI, RESOURCE_INDEX(device));

    if (spi->leadingEdge == true)
        XMC_SPI_CH_ConfigureShiftClockOutput((XMC_USIC_CH_t*)spi->dev,
        									  XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_ENABLED,
											  XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
    else
    	XMC_SPI_CH_ConfigureShiftClockOutput((XMC_USIC_CH_t*)spi->dev,
    										  XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED,
											  XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);

    IOConfigGPIOAF(IOGetByTag(spi->miso), SPI_IO_AF_MISO_CFG, spi->misoAF);
    XMC_SPI_CH_SetInputSource((XMC_USIC_CH_t*)spi->dev, XMC_SPI_CH_INPUT_DIN0, spi->misoSRC);

    XMC_SPI_CH_Start((XMC_USIC_CH_t*)spi->dev);

    IOConfigGPIOAF(IOGetByTag(spi->sck), SPI_IO_AF_SCK_CFG, spi->sckAF);
    IOConfigGPIOAF(IOGetByTag(spi->mosi), SPI_IO_AF_MOSI_CFG, spi->mosiAF);

	switch((uint32_t)spi->dev)
	{
		case (uint32_t)USIC0_CH0:
		case (uint32_t)USIC1_CH0:
		case (uint32_t)USIC2_CH0:
			XMC_USIC_CH_TXFIFO_Configure((XMC_USIC_CH_t*)spi->dev, 0, XMC_USIC_CH_FIFO_SIZE_16WORDS, 1);
			XMC_USIC_CH_RXFIFO_Configure((XMC_USIC_CH_t*)spi->dev, 16, XMC_USIC_CH_FIFO_SIZE_16WORDS, 0);
		break;
		case (uint32_t)USIC0_CH1:
		case (uint32_t)USIC1_CH1:
		case (uint32_t)USIC2_CH1:
			XMC_USIC_CH_TXFIFO_Configure((XMC_USIC_CH_t*)spi->dev, 32, XMC_USIC_CH_FIFO_SIZE_16WORDS, 1);
			XMC_USIC_CH_RXFIFO_Configure((XMC_USIC_CH_t*)spi->dev, 48, XMC_USIC_CH_FIFO_SIZE_16WORDS, 0);
		break;
	}
}

uint8_t spiTransferByte(SPI_TypeDef *instance, uint8_t txByte)
{
    uint32_t spiTimeout = 0x10000;

    while (XMC_USIC_CH_TXFIFO_IsFull((XMC_USIC_CH_t*)instance))
    	if ((spiTimeout--) == 0)
    		return spiTimeoutUserCallback(instance);

    XMC_SPI_CH_Transmit((XMC_USIC_CH_t*)instance, txByte, XMC_SPI_CH_MODE_STANDARD);

    while (XMC_USIC_CH_RXFIFO_IsEmpty((XMC_USIC_CH_t*)instance))
    	if ((spiTimeout--) == 0)
    	    return spiTimeoutUserCallback(instance);

    return XMC_SPI_CH_GetReceivedData((XMC_USIC_CH_t*)instance);
}

/**
 * Return true if the bus is currently in the middle of a transmission.
 */
bool spiIsBusBusy(SPI_TypeDef *instance)
{
	return !XMC_USIC_CH_TXFIFO_IsEmpty((XMC_USIC_CH_t*)instance);
}

bool spiTransfer(SPI_TypeDef *instance, const uint8_t *txData, uint8_t *rxData, int len)
{
	uint32_t spiTimeout = 0x10000;
	int rxPos = 0;

	uint8_t* txBuffer = malloc(len);
	uint8_t* rxBuffer = malloc(len);

	memset(txBuffer, 0xff, len);
	memset(rxBuffer, 0xff, len);

	if (txData != NULL)
		memcpy(txBuffer, txData, len);

	for (int i=0; i<len; i++)
	{
		while (XMC_USIC_CH_TXFIFO_IsFull((XMC_USIC_CH_t*)instance))
			if ((spiTimeout--) == 0)
				return spiTimeoutUserCallback(instance);

		XMC_SPI_CH_Transmit((XMC_USIC_CH_t*)instance, txBuffer[i], XMC_SPI_CH_MODE_STANDARD);

		uint8_t level = XMC_USIC_CH_RXFIFO_GetLevel((XMC_USIC_CH_t*)instance);

		for (uint8_t j=0; j<level; j++)
			rxBuffer[rxPos++] = XMC_SPI_CH_GetReceivedData((XMC_USIC_CH_t*)instance);
	}

	while (rxPos < len)
	{
		uint8_t level = XMC_USIC_CH_RXFIFO_GetLevel((XMC_USIC_CH_t*)instance);

		if (level)
			for (uint8_t j=0; j<level; j++)
				rxBuffer[rxPos++] = XMC_SPI_CH_GetReceivedData((XMC_USIC_CH_t*)instance);
		else
			if ((spiTimeout--) == 0)
				return spiTimeoutUserCallback(instance);

	}

	if (rxData != NULL)
		memcpy(rxData, rxBuffer, len);

	free(txBuffer);
	free(rxBuffer);

    return true;
}

void spiSetDivisor(SPI_TypeDef *instance, uint16_t divisor)
{
	XMC_SPI_CH_SetBaudrate((XMC_USIC_CH_t*)instance, SystemCoreClock / divisor);
}

void spiSlaveInitDevice(SPIDevice device)
{
    spiDevice_t *spi = &(spiDevice[device]);

    IOInit(IOGetByTag(spi->sck),  OWNER_SPI_SCK,  RESOURCE_INDEX(device));
    IOInit(IOGetByTag(spi->miso), OWNER_SPI_MISO, RESOURCE_INDEX(device));
    IOInit(IOGetByTag(spi->mosi), OWNER_SPI_MOSI, RESOURCE_INDEX(device));
    IOInit(IOGetByTag(spi->cs), OWNER_SPI_CS, RESOURCE_INDEX(device));

    IOConfigGPIO(IOGetByTag(spi->sck),  IOCFG_IN_FLOATING);
    IOConfigGPIO(IOGetByTag(spi->cs),   IOCFG_IN_FLOATING);
    IOConfigGPIO(IOGetByTag(spi->mosi), IOCFG_IN_FLOATING);
    IOConfigGPIOAF(IOGetByTag(spi->miso), IOCFG_AF_PP, spi->misoAF);

    XMC_SPI_CH_CONFIG_t config =
    {
    	.bus_mode 	 = XMC_SPI_CH_BUS_MODE_SLAVE,
		.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE,
    };

    XMC_SPI_CH_Init((XMC_USIC_CH_t*)spi->dev, &config);
    XMC_SPI_CH_SetBitOrderMsbFirst((XMC_USIC_CH_t*)spi->dev);

    XMC_SPI_CH_SetWordLength((XMC_USIC_CH_t*)spi->dev, 8);
    XMC_SPI_CH_SetFrameLength((XMC_USIC_CH_t*)spi->dev, 64);

    XMC_SPI_CH_SetInputSource((XMC_USIC_CH_t*)spi->dev, XMC_SPI_CH_INPUT_DIN0, spi->mosiSRC);
    XMC_SPI_CH_SetInputSource((XMC_USIC_CH_t*)spi->dev, XMC_SPI_CH_INPUT_SLAVE_SCLKIN, spi->sckSRC);
    XMC_SPI_CH_SetInputSource((XMC_USIC_CH_t*)spi->dev, XMC_SPI_CH_INPUT_SLAVE_SELIN, spi->csSRC);
    XMC_SPI_CH_EnableInputInversion((XMC_USIC_CH_t*)spi->dev, XMC_SPI_CH_INPUT_SLAVE_SELIN);

	switch((uint32_t)spi->dev)
	{
		case (uint32_t)USIC0_CH0:
		case (uint32_t)USIC1_CH0:
		case (uint32_t)USIC2_CH0:
			XMC_USIC_CH_TXFIFO_Configure((XMC_USIC_CH_t*)spi->dev, 0, XMC_USIC_CH_FIFO_SIZE_16WORDS, 1);
			XMC_USIC_CH_RXFIFO_Configure((XMC_USIC_CH_t*)spi->dev, 16, XMC_USIC_CH_FIFO_SIZE_16WORDS, 0);
		break;
		case (uint32_t)USIC0_CH1:
		case (uint32_t)USIC1_CH1:
		case (uint32_t)USIC2_CH1:
			XMC_USIC_CH_TXFIFO_Configure((XMC_USIC_CH_t*)spi->dev, 32, XMC_USIC_CH_FIFO_SIZE_16WORDS, 1);
			XMC_USIC_CH_RXFIFO_Configure((XMC_USIC_CH_t*)spi->dev, 48, XMC_USIC_CH_FIFO_SIZE_16WORDS, 0);
		break;
	}

	switch(spi->rxIrq)
	{
		case USIC0_0_IRQn:
		case USIC1_0_IRQn:
		case USIC2_0_IRQn:
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 0);
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, 0);
			break;
		case USIC0_1_IRQn:
		case USIC1_1_IRQn:
		case USIC2_1_IRQn:
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 1);
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, 1);
			break;
		case USIC0_2_IRQn:
		case USIC1_2_IRQn:
		case USIC2_2_IRQn:
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 2);
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, 2);
			break;
		case USIC0_3_IRQn:
		case USIC1_3_IRQn:
		case USIC2_3_IRQn:
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 3);
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, 3);
			break;
		case USIC0_4_IRQn:
		case USIC1_4_IRQn:
		case USIC2_4_IRQn:
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 4);
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, 4);
			break;
		case USIC0_5_IRQn:
		case USIC1_5_IRQn:
		case USIC2_5_IRQn:
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 5);
			XMC_USIC_CH_RXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, 5);
			break;
	}
	XMC_USIC_CH_RXFIFO_EnableEvent((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);

	switch(spi->txIrq)
	{
		case USIC0_0_IRQn:
		case USIC1_0_IRQn:
		case USIC2_0_IRQn:
			XMC_USIC_CH_TXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 0);
			break;
		case USIC0_1_IRQn:
		case USIC1_1_IRQn:
		case USIC2_1_IRQn:
			XMC_USIC_CH_TXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 1);
			break;
		case USIC0_2_IRQn:
		case USIC1_2_IRQn:
		case USIC2_2_IRQn:
			XMC_USIC_CH_TXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 2);
			break;
		case USIC0_3_IRQn:
		case USIC1_3_IRQn:
		case USIC2_3_IRQn:
			XMC_USIC_CH_TXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 3);
			break;
		case USIC0_4_IRQn:
		case USIC1_4_IRQn:
		case USIC2_4_IRQn:
			XMC_USIC_CH_TXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 4);
			break;
		case USIC0_5_IRQn:
		case USIC1_5_IRQn:
		case USIC2_5_IRQn:
			XMC_USIC_CH_TXFIFO_SetInterruptNodePointer((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 5);
			break;
	}

	XMC_USIC_CH_TXFIFO_EnableEvent((XMC_USIC_CH_t*)spi->dev, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = spi->rxIrq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRIORITY_BASE(spi->rxPriority);
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_PRIORITY_SUB(spi->rxPriority);
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = spi->txIrq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRIORITY_BASE(spi->txPriority);
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_PRIORITY_SUB(spi->txPriority);
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	XMC_SPI_CH_Start((XMC_USIC_CH_t*)spi->dev);
}

#ifdef USE_SPIS_DEVICE_3

void USIC1_0_IRQHandler(void)
{
	spiDevice_t* spi = &spiDevice[SPIDEV_3];
	spiSlaveRxIrqHandler(spi);
}

void USIC1_1_IRQHandler(void)
{
	spiDevice_t* spi = &spiDevice[SPIDEV_3];
	spiSlaveTxIrqHandler(spi);
}

#endif

#endif

