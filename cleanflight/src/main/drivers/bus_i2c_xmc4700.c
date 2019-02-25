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

#include "platform.h"

#if defined(USE_I2C) && !defined(SOFT_I2C)

#include "build/debug.h"

#include "drivers/system.h"
#include "drivers/io.h"
#include "drivers/io_impl.h"

#include "drivers/bus_i2c.h"
#include "drivers/bus_i2c_impl.h"

#define IOCFG_I2C_PU XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN
#define IOCFG_I2C    XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN

#define I2C_HIGHSPEED_TIMING  400000
#define I2C_STANDARD_TIMING   100000

static uint32_t i2cTimeout;

static volatile uint16_t i2cErrorCount = 0;

const i2cHardware_t i2cHardware[I2CDEV_COUNT] = {
#ifdef USE_I2C_DEVICE_5
	{
		.device = I2CDEV_5,
		.reg = (I2C_TypeDef*)XMC_USIC2_CH0,
		.sclPins = { I2CPINDEF(P52, XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT1, 0) },
		.sdaPins = { I2CPINDEF(P50, XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT1, 1) },
	}
#endif
};

i2cDevice_t i2cDevice[I2CDEV_COUNT];

///////////////////////////////////////////////////////////////////////////////
// I2C TimeoutUserCallback
///////////////////////////////////////////////////////////////////////////////

uint32_t i2cTimeoutUserCallback(void)
{
    i2cErrorCount++;
    return false;
}

void i2cInit(I2CDevice device)
{
    if (device == I2CINVALID || device > I2CDEV_COUNT) {
        return;
    }

    i2cDevice_t *pDev = &i2cDevice[device];
    const i2cHardware_t *hw = pDev->hardware;

    if (!hw) {
        return;
    }

    I2C_TypeDef *I2Cx = pDev->reg;

    XMC_I2C_CH_CONFIG_t config =
    {
    	.baudrate = (pDev->overClock ? I2C_HIGHSPEED_TIMING : I2C_STANDARD_TIMING),
		.address = 0,
    };

    XMC_I2C_CH_Init((XMC_USIC_CH_t*)I2Cx, &config);
    XMC_USIC_CH_SetInputSource((XMC_USIC_CH_t*)I2Cx, XMC_USIC_CH_INPUT_DX0, pDev->sdaSource);
    XMC_USIC_CH_SetInputSource((XMC_USIC_CH_t*)I2Cx, XMC_USIC_CH_INPUT_DX1, pDev->sclSource);

    switch((uint32_t)I2Cx)
    {
		case (uint32_t)USIC0_CH0:
		case (uint32_t)USIC1_CH0:
		case (uint32_t)USIC2_CH0:
		    XMC_USIC_CH_TXFIFO_Configure((XMC_USIC_CH_t*)I2Cx, 0, XMC_USIC_CH_FIFO_SIZE_16WORDS, 1);
		    XMC_USIC_CH_RXFIFO_Configure((XMC_USIC_CH_t*)I2Cx, 16, XMC_USIC_CH_FIFO_SIZE_16WORDS, 0);
			break;
		case (uint32_t)USIC0_CH1:
		case (uint32_t)USIC1_CH1:
		case (uint32_t)USIC2_CH1:
		    XMC_USIC_CH_TXFIFO_Configure((XMC_USIC_CH_t*)I2Cx, 32, XMC_USIC_CH_FIFO_SIZE_16WORDS, 1);
		    XMC_USIC_CH_RXFIFO_Configure((XMC_USIC_CH_t*)I2Cx, 48, XMC_USIC_CH_FIFO_SIZE_16WORDS, 0);
			break;
    }

    XMC_I2C_CH_Start((XMC_USIC_CH_t*)I2Cx);

    IO_t scl = pDev->scl;
    IO_t sda = pDev->sda;

    IOInit(scl, OWNER_I2C_SCL, RESOURCE_INDEX(device));
    IOConfigGPIOAF(scl, pDev->pullUp ? IOCFG_I2C_PU : IOCFG_I2C, pDev->sclAF);

    IOInit(sda, OWNER_I2C_SDA, RESOURCE_INDEX(device));
    IOConfigGPIOAF(sda, pDev->pullUp ? IOCFG_I2C_PU : IOCFG_I2C, pDev->sdaAF);
}

uint16_t i2cGetErrorCounter(void)
{
    return i2cErrorCount;
}

bool i2cWrite(I2CDevice device, uint8_t addr_, uint8_t reg, uint8_t data)
{
    if (device == I2CINVALID || device > I2CDEV_COUNT) {
        return false;
    }

    I2C_TypeDef *I2Cx = i2cDevice[device].reg;

    if (!I2Cx) {
        return false;
    }

    addr_ <<= 1;

    i2cTimeout = I2C_LONG_TIMEOUT;
    while(!XMC_USIC_CH_TXFIFO_IsEmpty((XMC_USIC_CH_t*)I2Cx))
    {
    	if (i2cTimeout-- == 0)
    		return i2cTimeoutUserCallback();
    }

    XMC_I2C_CH_MasterStart((XMC_USIC_CH_t*)I2Cx, addr_, XMC_I2C_CH_CMD_WRITE);
    XMC_I2C_CH_MasterTransmit((XMC_USIC_CH_t*)I2Cx, reg);
    XMC_I2C_CH_MasterTransmit((XMC_USIC_CH_t*)I2Cx, data);
    XMC_I2C_CH_MasterStop((XMC_USIC_CH_t*)I2Cx);

    i2cTimeout = I2C_LONG_TIMEOUT;
    while(!XMC_USIC_CH_TXFIFO_IsEmpty((XMC_USIC_CH_t*)I2Cx))
    {
    	if (i2cTimeout-- == 0)
    		return i2cTimeoutUserCallback();
    }

    return true;
}

bool i2cRead(I2CDevice device, uint8_t addr_, uint8_t reg, uint8_t len, uint8_t* buf)
{
	uint32_t pos = 0;
	uint8_t level = 0;

    if (device == I2CINVALID || device > I2CDEV_COUNT) {
        return false;
    }

    I2C_TypeDef *I2Cx = i2cDevice[device].reg;

    if (!I2Cx) {
        return false;
    }

    addr_ <<= 1;

        i2cTimeout = I2C_LONG_TIMEOUT;
        while(!XMC_USIC_CH_TXFIFO_IsEmpty((XMC_USIC_CH_t*)I2Cx))
        {
        	if (i2cTimeout-- == 0)
        		return i2cTimeoutUserCallback();
        }


        XMC_I2C_CH_MasterStart((XMC_USIC_CH_t*)I2Cx, addr_, XMC_I2C_CH_CMD_WRITE);
        XMC_I2C_CH_MasterTransmit((XMC_USIC_CH_t*)I2Cx, reg);
        XMC_I2C_CH_MasterRepeatedStart((XMC_USIC_CH_t*)I2Cx, addr_, XMC_I2C_CH_CMD_READ);

        for(uint32_t i=0; i<len-1; i++)
        {
        	i2cTimeout = I2C_LONG_TIMEOUT;
        	while(XMC_USIC_CH_TXFIFO_IsFull((XMC_USIC_CH_t*)I2Cx))
            {
            	if (i2cTimeout-- == 0)
            		return i2cTimeoutUserCallback();
            }

        	XMC_I2C_CH_MasterReceiveAck((XMC_USIC_CH_t*)I2Cx);

        	level = XMC_USIC_CH_RXFIFO_GetLevel((XMC_USIC_CH_t*)I2Cx);
        	for (uint8_t i=0; i<level; i++)
        		buf[pos++] = XMC_I2C_CH_GetReceivedData((XMC_USIC_CH_t*)I2Cx);
        }

        i2cTimeout = I2C_LONG_TIMEOUT;
        while(XMC_USIC_CH_TXFIFO_IsFull((XMC_USIC_CH_t*)I2Cx))
        {
        	if (i2cTimeout-- == 0)
        		return i2cTimeoutUserCallback();
        }
        XMC_I2C_CH_MasterReceiveNack((XMC_USIC_CH_t*)I2Cx);
        i2cTimeout = I2C_LONG_TIMEOUT;
        while(XMC_USIC_CH_TXFIFO_IsFull((XMC_USIC_CH_t*)I2Cx))
        {
        	if (i2cTimeout-- == 0)
        		return i2cTimeoutUserCallback();
        }
        XMC_I2C_CH_MasterStop((XMC_USIC_CH_t*)I2Cx);

        i2cTimeout = I2C_LONG_TIMEOUT;
        while (pos < len)
        {
        	level = XMC_USIC_CH_RXFIFO_GetLevel((XMC_USIC_CH_t*)I2Cx);
        	for (uint8_t i=0; i<level; i++)
        		buf[pos++] = XMC_I2C_CH_GetReceivedData((XMC_USIC_CH_t*)I2Cx);

    		if (i2cTimeout-- == 0)
    			return i2cTimeoutUserCallback();
        }

        /* If all operations OK */
        return true;
}

#endif
