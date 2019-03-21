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

#include "platform.h"

#ifdef USE_LED_STRIP

#include "common/color.h"
#include "light_ws2811strip.h"
#include "drivers/nvic.h"
#include "dma.h"
#include "drivers/io.h"
#include "drivers/system.h"
#include "rcc.h"
#include "timer.h"

bool ws2811Initialised = false;

void ws2811LedStripHardwareInit(ioTag_t ioTag)
{

}

void ws2811LedStripDMAEnable(void)
{

}
#endif
