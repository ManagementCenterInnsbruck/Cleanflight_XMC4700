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

#include "drivers/accgyro/accgyro_mpu.h"
#include "drivers/exti.h"
#include "drivers/nvic.h"
#include "drivers/system.h"

void SystemCoreClockSetup(void)
{
	const XMC_SCU_CLOCK_CONFIG_t CLOCK_XMC4_0_CONFIG =
	{
		.syspll_config.n_div = 128U,
		.syspll_config.p_div = 3U,
		.syspll_config.k_div = 2U,
		.syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
		.syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
		.enable_oschp = true,
		.enable_osculp = false,
		.calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
		.fstdby_clksrc = XMC_SCU_HIB_STDBYCLKSRC_OSI,
		.fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
		.fsys_clkdiv = 2U,
		.fcpu_clkdiv = 1U,
		.fccu_clkdiv = 1U,
		.fperipheral_clkdiv = 1U
	};
	XMC_SCU_CLOCK_Init(&CLOCK_XMC4_0_CONFIG);
	XMC_SCU_HIB_SetRtcClockSource(XMC_SCU_HIB_RTCCLKSRC_OSI);
	XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
	XMC_SCU_CLOCK_SetUsbClockDivider(4U);
	XMC_SCU_CLOCK_StartUsbPll(1U, 32U);
	XMC_SCU_CLOCK_SetWdtClockSource(XMC_SCU_CLOCK_WDTCLKSRC_OFI);
	XMC_SCU_CLOCK_SetWdtClockDivider(1U);
	XMC_SCU_CLOCK_SetEbuClockDivider(1U);
}


void systemReset(void)
{
    if (mpuResetFn) {
        mpuResetFn();
    }

    __disable_irq();
    NVIC_SystemReset();
}

void systemResetToBootloader(void)
{
    if (mpuResetFn) {
        mpuResetFn();
    }

    __disable_irq();
    NVIC_SystemReset();
}

void systemInit(void)
{
    // Init cycle counter
    cycleCounterInit();

    // SysTick
    SysTick_Config(SystemCoreClock / 1000);
}

bool isMPUSoftReset(void)
{
    return false;
}
