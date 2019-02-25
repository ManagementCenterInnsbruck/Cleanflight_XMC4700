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

/*
 * jflyper - Refactoring, cleanup and made pin-configurable
 */

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "drivers/system.h"
#include "drivers/io.h"
#include "drivers/nvic.h"

#include "drivers/serial.h"
#include "drivers/serial_uart.h"
#include "drivers/serial_uart_impl.h"

#ifdef USE_UART

const uartHardware_t uartHardware[UARTDEV_COUNT] = {
#ifdef USE_UART1
	{
		.device = UARTDEV_1,
		.reg = (USART_TypeDef*)XMC_USIC0_CH0,
		.rxPins = { UARTPINDEF(P15, 0, 0), UARTPINDEF(P14, 0, 1), UARTPINDEF(P50, 0, 3) },
		.txPins = { UARTPINDEF(P15, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2, 0), UARTPINDEF(P17, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2, 0), UARTPINDEF(P51, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1, 0) },
		.txIrq = USIC0_0_IRQn,
		.rxIrq = USIC0_1_IRQn,
		.txPriority = NVIC_PRIO_SERIALUART1,
		.rxPriority = NVIC_PRIO_SERIALUART1,
	},
#endif
#ifdef USE_UART4
    {
        .device = UARTDEV_4,
        .reg = (USART_TypeDef*)XMC_USIC1_CH1,
        .rxPins = { UARTPINDEF(P00, 0, 3) },
        .txPins = { UARTPINDEF(P01, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2, 0), UARTPINDEF(P19, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4, 0) },
        .txIrq = USIC1_2_IRQn,
		.rxIrq = USIC1_3_IRQn,
        .txPriority = NVIC_PRIO_SERIALUART4,
        .rxPriority = NVIC_PRIO_SERIALUART4,
    },
#endif
#ifdef USE_UART6
    {
        .device = UARTDEV_6,
        .reg = (USART_TypeDef*)XMC_USIC2_CH1,
        .rxPins = { UARTPINDEF(P35, 0, 0), UARTPINDEF(P34, 0, 1), UARTPINDEF(P40, 0, 2) },
        .txPins = { UARTPINDEF(P35, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1, 0) },
        .txIrq = USIC2_2_IRQn,
		.rxIrq = USIC2_3_IRQn,
        .txPriority = NVIC_PRIO_SERIALUART6,
        .rxPriority = NVIC_PRIO_SERIALUART6,
    },
#endif
};

uartPort_t *serialUART(UARTDevice_e device, uint32_t baudRate, portMode_e mode, portOptions_e options)
{
    uartDevice_t *uart = uartDevmap[device];
    if (!uart) return NULL;

    const uartHardware_t *hardware = uart->hardware;

    if (!hardware) return NULL; // XXX Can't happen !?

    uartPort_t *s = &(uart->port);
    s->port.vTable = uartVTable;

    s->port.baudRate = baudRate;

    s->port.rxBuffer = uart->rxBuffer;
    s->port.txBuffer = uart->txBuffer;
    s->port.rxBufferSize = sizeof(uart->rxBuffer);
    s->port.txBufferSize = sizeof(uart->txBuffer);

    s->USARTx = hardware->reg;

    IO_t txIO = IOGetByTag(uart->tx);
    IO_t rxIO = IOGetByTag(uart->rx);

    if (options & SERIAL_BIDIR) {
        IOInit(txIO, OWNER_SERIAL_TX, RESOURCE_INDEX(device));
        IOConfigGPIOAF(txIO, (options & SERIAL_BIDIR_PP) ? IOCFG_AF_PP : IOCFG_AF_OD, uart->txAF);
    } else {
        if ((mode & MODE_TX) && txIO) {
            IOInit(txIO, OWNER_SERIAL_TX, RESOURCE_INDEX(device));
            IOConfigGPIOAF(txIO, IOCFG_AF_PP, uart->txAF);
        }

        if ((mode & MODE_RX) && rxIO) {
            IOInit(rxIO, OWNER_SERIAL_RX, RESOURCE_INDEX(device));
            IOConfigGPIO(rxIO, IOCFG_IN_FLOATING);
        }
    }

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = hardware->rxIrq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRIORITY_BASE(hardware->rxPriority);
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_PRIORITY_SUB(hardware->rxPriority);
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = hardware->txIrq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRIORITY_BASE(hardware->txPriority);
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_PRIORITY_SUB(hardware->txPriority);
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

    return s;
}

void uartTxIrqHandler(uartPort_t *s)
{
	if (s->port.txBufferTail != s->port.txBufferHead)
	{
		while(XMC_USIC_CH_TXFIFO_IsFull((XMC_USIC_CH_t*)s->USARTx));
		XMC_UART_CH_Transmit((XMC_USIC_CH_t*)s->USARTx, s->port.txBuffer[s->port.txBufferTail++]);
		if (s->port.txBufferTail >= s->port.txBufferSize)
			s->port.txBufferTail = 0;
	}
}

void uartRxIrqHandler(uartPort_t *s)
{
	while (!XMC_USIC_CH_RXFIFO_IsEmpty((XMC_USIC_CH_t*)s->USARTx))
	{
		if (s->port.rxCallback)
			s->port.rxCallback(XMC_UART_CH_GetReceivedData((XMC_USIC_CH_t*)s->USARTx), s->port.rxCallbackData);
		else
		{
			s->port.rxBuffer[s->port.rxBufferHead++] = XMC_UART_CH_GetReceivedData((XMC_USIC_CH_t*)s->USARTx);
			if (s->port.rxBufferHead >= s->port.rxBufferSize)
			{
				s->port.rxBufferHead = 0;
			}
		}
	}
}
#endif
