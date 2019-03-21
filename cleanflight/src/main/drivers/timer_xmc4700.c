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

#include "platform.h"

#include "common/utils.h"

#include "timer.h"

const timerDef_t timerDefinitions[HARDWARE_TIMER_DEFINITION_COUNT] = {
	{ .TIMx = CCU40_CC40, .inputIrq = CCU40_0_IRQn },
	{ .TIMx = CCU40_CC41, .inputIrq = CCU40_1_IRQn },
	{ .TIMx = CCU40_CC42, .inputIrq = CCU40_2_IRQn },
	{ .TIMx = CCU40_CC43, .inputIrq = CCU40_3_IRQn },
	{ .TIMx = CCU41_CC40, .inputIrq = CCU41_0_IRQn },
	{ .TIMx = CCU41_CC41, .inputIrq = CCU41_1_IRQn },
	{ .TIMx = CCU41_CC42, .inputIrq = CCU41_2_IRQn },
	{ .TIMx = CCU41_CC43, .inputIrq = CCU41_3_IRQn },
	{ .TIMx = CCU42_CC40, .inputIrq = CCU42_0_IRQn },
	{ .TIMx = CCU42_CC41, .inputIrq = CCU42_1_IRQn },
	{ .TIMx = CCU42_CC42, .inputIrq = CCU42_2_IRQn },
	{ .TIMx = CCU42_CC43, .inputIrq = CCU42_3_IRQn },
	{ .TIMx = CCU43_CC40, .inputIrq = CCU43_0_IRQn },
	{ .TIMx = CCU43_CC41, .inputIrq = CCU43_1_IRQn },
	{ .TIMx = CCU43_CC42, .inputIrq = CCU43_2_IRQn },
	{ .TIMx = CCU43_CC43, .inputIrq = CCU43_3_IRQn },
};

uint32_t timerClock(TIM_TypeDef *tim)
{
    UNUSED(tim);
    return SystemCoreClock;
}
