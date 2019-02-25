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

#ifdef USE_ADC

#include "build/debug.h"

#include "drivers/accgyro/accgyro.h"
#include "drivers/system.h"

#include "drivers/io.h"
#include "io_impl.h"
#include "dma.h"

#include "drivers/sensor.h"

#include "adc.h"
#include "adc_impl.h"

#include "pg/adc.h"

// These are missing from STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_adc.h
#ifdef STM32F446xx
#define ADC_Channel_TempSensor ADC_Channel_18
#endif

const adcDevice_t adcHardware[] = {
    { .ADCx = VADC },
};

/* note these could be packed up for saving space */
const adcTagMap_t adcTagMap[] = {
	{ DEFIO_TAG_E__P140,   ADC_DEVICES_1, 0  , VADC_G0}, // G0
	{ DEFIO_TAG_E__P141,   ADC_DEVICES_1, 1  , VADC_G0}, // G0
	{ DEFIO_TAG_E__P142,   ADC_DEVICES_1, 2  , VADC_G0}, // G0
	{ DEFIO_TAG_E__P143,   ADC_DEVICES_1, 3  , VADC_G0}, // G0
	{ DEFIO_TAG_E__P144,   ADC_DEVICES_1, 4  , VADC_G0}, // G0
	{ DEFIO_TAG_E__P145,   ADC_DEVICES_1, 5  , VADC_G0}, // G0
	{ DEFIO_TAG_E__P146,   ADC_DEVICES_1, 6  , VADC_G0}, // G0
	{ DEFIO_TAG_E__P147,   ADC_DEVICES_1, 7  , VADC_G0}, // G0
	{ DEFIO_TAG_E__P148,   ADC_DEVICES_1, 0  , VADC_G1}, // G1
	{ DEFIO_TAG_E__P149,   ADC_DEVICES_1, 1  , VADC_G1}, // G1
	{ DEFIO_TAG_E__P142,   ADC_DEVICES_1, 2  , VADC_G1}, // G1
	{ DEFIO_TAG_E__P143,   ADC_DEVICES_1, 3  , VADC_G1}, // G1
	{ DEFIO_TAG_E__P1412,  ADC_DEVICES_1, 4  , VADC_G1}, // G1
	{ DEFIO_TAG_E__P1413,  ADC_DEVICES_1, 5  , VADC_G1}, // G1
	{ DEFIO_TAG_E__P1414,  ADC_DEVICES_1, 6  , VADC_G1}, // G1
	{ DEFIO_TAG_E__P1415,  ADC_DEVICES_1, 7  , VADC_G1}, // G1
	{ DEFIO_TAG_E__P144,   ADC_DEVICES_1, 0  , VADC_G2}, // G2
	{ DEFIO_TAG_E__P145,   ADC_DEVICES_1, 1  , VADC_G2}, // G2
	{ DEFIO_TAG_E__P152,   ADC_DEVICES_1, 2  , VADC_G2}, // G2
	{ DEFIO_TAG_E__P153,   ADC_DEVICES_1, 3  , VADC_G2}, // G2
	{ DEFIO_TAG_E__P154,   ADC_DEVICES_1, 4  , VADC_G2}, // G2
	{ DEFIO_TAG_E__P155,   ADC_DEVICES_1, 5  , VADC_G2}, // G2
	{ DEFIO_TAG_E__P156,   ADC_DEVICES_1, 6  , VADC_G2}, // G2
	{ DEFIO_TAG_E__P157,   ADC_DEVICES_1, 7  , VADC_G2}, // G2
	{ DEFIO_TAG_E__P158,   ADC_DEVICES_1, 0  , VADC_G3}, // G3
	{ DEFIO_TAG_E__P159,   ADC_DEVICES_1, 1  , VADC_G3}, // G3
	{ DEFIO_TAG_E__P148,   ADC_DEVICES_1, 2  , VADC_G3}, // G3
	{ DEFIO_TAG_E__P149,   ADC_DEVICES_1, 3  , VADC_G3}, // G3
	{ DEFIO_TAG_E__P1512,  ADC_DEVICES_1, 4  , VADC_G3}, // G3
	{ DEFIO_TAG_E__P1513,  ADC_DEVICES_1, 5  , VADC_G3}, // G3
	{ DEFIO_TAG_E__P1514,  ADC_DEVICES_1, 6  , VADC_G3}, // G3
	{ DEFIO_TAG_E__P1515,  ADC_DEVICES_1, 7  , VADC_G3}, // G3
};

VADC_G_TypeDef* adcGroupByTag(ioTag_t ioTag)
{
    for (uint8_t i = 0; i < ARRAYLEN(adcTagMap); i++) {
        if (ioTag == adcTagMap[i].tag)
            return adcTagMap[i].group;
    }
    return 0;
}

void adcInit(const adcConfig_t *config)
{
    uint8_t i;

    memset(&adcOperatingConfig, 0, sizeof(adcOperatingConfig));

    if (config->vbat.enabled) {
        adcOperatingConfig[ADC_BATTERY].tag = config->vbat.ioTag;
    }

    if (config->rssi.enabled) {
        adcOperatingConfig[ADC_RSSI].tag = config->rssi.ioTag;  //RSSI_ADC_CHANNEL;
    }

    if (config->external1.enabled) {
        adcOperatingConfig[ADC_EXTERNAL1].tag = config->external1.ioTag; //EXTERNAL1_ADC_CHANNEL;
    }

    if (config->current.enabled) {
        adcOperatingConfig[ADC_CURRENT].tag = config->current.ioTag;  //CURRENT_METER_ADC_CHANNEL;
    }

    ADCDevice device = ADC_CFG_TO_DEV(config->device);
    if (device == ADCINVALID)
        return;

    adcDevice_t adc = adcHardware[device];

    bool adcActive = false;
    for (int i = 0; i < ADC_CHANNEL_COUNT; i++) {
        if (!adcVerifyPin(adcOperatingConfig[i].tag, device)) {
            continue;
        }

        adcActive = true;
        IOInit(IOGetByTag(adcOperatingConfig[i].tag), OWNER_ADC_BATT + i, 0);
        adcOperatingConfig[i].adcChannel = adcChannelByTag(adcOperatingConfig[i].tag);
        adcOperatingConfig[i].group = adcGroupByTag(adcOperatingConfig[i].tag);
        adcOperatingConfig[i].enabled = true;
    }

    if (!adcActive) {
        return;
    }

	XMC_VADC_GLOBAL_CONFIG_t global_config;
	memset(&global_config, 0, sizeof(global_config));
	XMC_VADC_GLOBAL_Init(adc.ADCx, &global_config);

	XMC_VADC_GROUP_CONFIG_t group_config;
	memset(&group_config, 0, sizeof(group_config));

	XMC_VADC_GROUP_Init(VADC_G0, &group_config);
	XMC_VADC_GROUP_Init(VADC_G1, &group_config);
	XMC_VADC_GROUP_Init(VADC_G2, &group_config);
	XMC_VADC_GROUP_Init(VADC_G3, &group_config);

	XMC_VADC_GROUP_SetPowerMode(VADC_G0, XMC_VADC_GROUP_POWERMODE_NORMAL);
	XMC_VADC_GROUP_SetPowerMode(VADC_G1, XMC_VADC_GROUP_POWERMODE_NORMAL);
	XMC_VADC_GROUP_SetPowerMode(VADC_G2, XMC_VADC_GROUP_POWERMODE_NORMAL);
	XMC_VADC_GROUP_SetPowerMode(VADC_G3, XMC_VADC_GROUP_POWERMODE_NORMAL);

	XMC_VADC_GLOBAL_StartupCalibration(adc.ADCx);

	XMC_VADC_GLOBAL_CLASS_t global_iclass_config =
	{
		.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT,
		.sample_time_std_conv     = 0,
	};
	XMC_VADC_GLOBAL_InputClassInit(adc.ADCx, global_iclass_config, XMC_VADC_GROUP_CONV_STD, 0);

	const XMC_VADC_BACKGROUND_CONFIG_t backgnd_config =
	{
		.conv_start_mode   = (uint32_t) XMC_VADC_STARTMODE_CIR,
		.req_src_priority  = (uint32_t) XMC_VADC_GROUP_RS_PRIORITY_1,
		.trigger_signal    = (uint32_t) XMC_VADC_REQ_TR_A,
		.trigger_edge      = (uint32_t) XMC_VADC_TRIGGER_EDGE_NONE,
		.gate_signal       = (uint32_t) XMC_VADC_REQ_GT_A,
		.timer_mode        = (uint32_t) 0,
		.external_trigger  = (uint32_t) 0,
		.req_src_interrupt = (uint32_t) 0,
		.enable_auto_scan  = (uint32_t) 1,
		.load_mode         = (uint32_t) XMC_VADC_SCAN_LOAD_OVERWRITE
	};
	XMC_VADC_GLOBAL_BackgroundInit(adc.ADCx, &backgnd_config);

    for (i = 0; i < ADC_CHANNEL_COUNT; i++) {
        if (!adcOperatingConfig[i].enabled) {
            continue;
        }
        XMC_VADC_CHANNEL_CONFIG_t ch_config =
		{
			.input_class                = XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,
			.lower_boundary_select 	    = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
			.upper_boundary_select 	    = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
			.event_gen_criteria         = XMC_VADC_CHANNEL_EVGEN_NEVER,
			.sync_conversion  		    = 0,
			.alternate_reference        = XMC_VADC_CHANNEL_REF_INTREF,
			.result_reg_number          = adcOperatingConfig[i].adcChannel,
			.use_global_result          = 0,
			.result_alignment           = XMC_VADC_RESULT_ALIGN_RIGHT,
			.broken_wire_detect_channel = XMC_VADC_CHANNEL_BWDCH_VAGND,
			.broken_wire_detect		    = 0,
			.bfl                        = 0,
			.channel_priority           = 0,
			.alias_channel              = -1,
		};
		XMC_VADC_GROUP_ChannelInit(adcOperatingConfig[i].group, adcOperatingConfig[i].adcChannel, &ch_config);

		XMC_VADC_RESULT_CONFIG_t result_config =
		{
			.data_reduction_control  = 0,
			.post_processing_mode    = XMC_VADC_DMM_REDUCTION_MODE,
			.wait_for_read_mode  	 = 0,
			.part_of_fifo       	 = 0,
			.event_gen_enable   	 = 0
		};
		XMC_VADC_GROUP_ResultInit(adcOperatingConfig[i].group, adcOperatingConfig[i].adcChannel, &result_config);

		uint8_t group_index = 0;

		if (adcOperatingConfig[i].group == VADC_G0)
			group_index = 0;
		else if (adcOperatingConfig[i].group == VADC_G1)
			group_index = 1;
		else if (adcOperatingConfig[i].group == VADC_G2)
			group_index = 2;
		else if (adcOperatingConfig[i].group == VADC_G3)
			group_index = 3;

		XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, group_index, adcOperatingConfig[i].adcChannel);
    }

    XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);
}
#endif
