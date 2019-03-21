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

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
	DEF_TIM(CCU41_CC40, CH1, P25, TIM_USE_MOTOR, 0, 0),
	DEF_TIM(CCU41_CC41, CH1, P24, TIM_USE_MOTOR, 0, 0),
	DEF_TIM(CCU41_CC42, CH1, P23, TIM_USE_MOTOR, 0, 0),
	DEF_TIM(CCU41_CC43, CH1, P22, TIM_USE_MOTOR, 0, 0),
	DEF_TIM(CCU40_CC42, CH1, P27, TIM_USE_PPM | TIM_USE_PWM, 0, 2),
};
