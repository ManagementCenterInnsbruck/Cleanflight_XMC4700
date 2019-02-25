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

#include <stdint.h>
#include <stdbool.h>

#include "platform.h"

#include "drivers/serial_spi_slave.h"
#include "drivers/bus_spi_impl.h"

#include "io/serial.h"

#ifdef USE_SPI

static void spiSlaveWrite(serialPort_t *instance, uint8_t c)
{
	spiDevice_t *spi = (spiDevice_t*)instance;
	spi->port.txBuffer[spi->port.txBufferHead] = c;
    if (spi->port.txBufferHead + 1 >= spi->port.txBufferSize) {
    	spi->port.txBufferHead = 0;
    } else {
    	spi->port.txBufferHead++;
    }

	switch (spi->txIrq)
	{
		case USIC0_0_IRQn:
		case USIC1_0_IRQn:
		case USIC2_0_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 0);
			break;
		case USIC0_1_IRQn:
		case USIC1_1_IRQn:
		case USIC2_1_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 1);
			break;
		case USIC0_2_IRQn:
		case USIC1_2_IRQn:
		case USIC2_2_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 2);
			break;
		case USIC0_3_IRQn:
		case USIC1_3_IRQn:
		case USIC2_3_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 3);
			break;
		case USIC0_4_IRQn:
		case USIC1_4_IRQn:
		case USIC2_4_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 4);
			break;
		case USIC0_5_IRQn:
		case USIC1_5_IRQn:
		case USIC2_5_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 5);
			break;
	}
}

static uint32_t spiSlaveTotalRxWaiting(const serialPort_t *instance)
{
    const spiDevice_t *s = (const spiDevice_t*)instance;

    if (s->port.rxBufferHead >= s->port.rxBufferTail) {
        return s->port.rxBufferHead - s->port.rxBufferTail;
    } else {
        return s->port.rxBufferSize + s->port.rxBufferHead - s->port.rxBufferTail;
    }
}

static uint32_t spiSlaveTxBytesFree(const serialPort_t *instance)
{
    const spiDevice_t *s = (const spiDevice_t*)instance;

    uint32_t bytesUsed;

    if (s->port.txBufferHead >= s->port.txBufferTail) {
        bytesUsed = s->port.txBufferHead - s->port.txBufferTail;
    } else {
        bytesUsed = s->port.txBufferSize + s->port.txBufferHead - s->port.txBufferTail;
    }

    return (s->port.txBufferSize - 1) - bytesUsed;
}

static uint8_t spiSlaveRead(serialPort_t *instance)
{
    uint8_t ch;
    spiDevice_t *s = (spiDevice_t *)instance;

	ch = s->port.rxBuffer[s->port.rxBufferTail];
	if (s->port.rxBufferTail + 1 >= s->port.rxBufferSize) {
		s->port.rxBufferTail = 0;
	} else {
		s->port.rxBufferTail++;
	}

    return ch;
}

static bool isSpiSlaveTransmitBufferEmpty(const serialPort_t *instance)
{
    const spiDevice_t *s = (const spiDevice_t *)instance;

    return s->port.txBufferTail == s->port.txBufferHead;
}

static void spiSlaveWriteBuf(serialPort_t *instance, const void *data, int count)
{
	spiDevice_t *spi = (spiDevice_t*)instance;

	for (int i=0; i<count; i++)
	{
		spi->port.txBuffer[spi->port.txBufferHead] = ((uint8_t*)data)[i];
		if (spi->port.txBufferHead + 1 >= spi->port.txBufferSize) {
			spi->port.txBufferHead = 0;
		} else {
			spi->port.txBufferHead++;
		}
	}
}

static void spiSlaveEndWrite(serialPort_t *instance)
{
	spiDevice_t *spi = (spiDevice_t*)instance;

	switch (spi->txIrq)
	{
		case USIC0_0_IRQn:
		case USIC1_0_IRQn:
		case USIC2_0_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 0);
			break;
		case USIC0_1_IRQn:
		case USIC1_1_IRQn:
		case USIC2_1_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 1);
			break;
		case USIC0_2_IRQn:
		case USIC1_2_IRQn:
		case USIC2_2_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 2);
			break;
		case USIC0_3_IRQn:
		case USIC1_3_IRQn:
		case USIC2_3_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 3);
			break;
		case USIC0_4_IRQn:
		case USIC1_4_IRQn:
		case USIC2_4_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 4);
			break;
		case USIC0_5_IRQn:
		case USIC1_5_IRQn:
		case USIC2_5_IRQn:
			XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t*)spi->dev, 5);
			break;
	}
}

static const struct serialPortVTable spisVTable[] = {
    {
        .serialWrite = spiSlaveWrite,
        .serialTotalRxWaiting = spiSlaveTotalRxWaiting,
        .serialTotalTxFree = spiSlaveTxBytesFree,
        .serialRead = spiSlaveRead,
        .serialSetBaudRate = NULL,
        .isSerialTransmitBufferEmpty = isSpiSlaveTransmitBufferEmpty,
        .setMode = NULL,
        .setCtrlLineStateCb = NULL,
        .setBaudRateCb = NULL,
        .writeBuf = spiSlaveWriteBuf,
        .beginWrite = NULL,
        .endWrite = spiSlaveEndWrite,
    }
};

serialPort_t *spiSlaveOpen(SPIDevice device, serialReceiveCallbackPtr rxCallback, void *rxCallbackData, uint32_t baudRate, portMode_e mode, portOptions_e options)
{
	spiDevice_t* spiDev =  &spiDevice[device];
	serialPort_t* s = &spiDev->port;

	s->vTable = spisVTable;
	s->rxCallback = rxCallback;
	s->baudRate = baudRate;
	s->mode = mode;
	s->options = options;

	s->rxBuffer = spiDev->rxBuffer;
	s->txBuffer = spiDev->txBuffer;

	s->rxBufferSize = sizeof(spiDev->rxBuffer);
	s->txBufferSize = sizeof(spiDev->txBuffer);

	s->rxBufferHead = s->rxBufferTail = 0;
	s->txBufferHead = s->txBufferTail = 0;

	return s;
}

void spiSlaveRxIrqHandler(spiDevice_t* spi)
{
	while (!XMC_USIC_CH_RXFIFO_IsEmpty((XMC_USIC_CH_t*)spi->dev))
	{
		if (spi->port.rxCallback)
			spi->port.rxCallback(XMC_SPI_CH_GetReceivedData((XMC_USIC_CH_t*)spi->dev), spi->port.rxCallbackData);
		else
		{
			spi->port.rxBuffer[spi->port.rxBufferHead++] = XMC_SPI_CH_GetReceivedData((XMC_USIC_CH_t*)spi->dev);
			if (spi->port.rxBufferHead >= spi->port.rxBufferSize)
				spi->port.rxBufferHead = 0;
		}
	}
}

void spiSlaveTxIrqHandler(spiDevice_t* spi)
{
	while(spi->port.txBufferTail != spi->port.txBufferHead &&
		  !XMC_USIC_CH_TXFIFO_IsFull((XMC_USIC_CH_t*)spi->dev))
	{
		XMC_SPI_CH_Transmit((XMC_USIC_CH_t*)spi->dev, spi->port.txBuffer[spi->port.txBufferTail++], XMC_SPI_CH_MODE_STANDARD);
		if (spi->port.txBufferTail >= spi->port.txBufferSize)
			spi->port.txBufferTail = 0;
	}
}

#endif
