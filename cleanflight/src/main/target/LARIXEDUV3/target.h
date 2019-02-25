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

#undef USE_BRUSHED_ESC_AUTODETECT
#undef USE_TELEMETRY
#undef USE_CAMERA_CONTROL
#undef USE_LED_STRIP
#undef USE_MSP_DISPLAYPORT

#define TARGET_BOARD_IDENTIFIER "LEDU"
#define USE_TARGET_CONFIG

#define USBD_PRODUCT_STRING "LarixEDU V3"

#define LED0_PIN                P10
#define LED1_PIN                P11
#define LED2_PIN				P12

#define LED0_INVERTED
#define LED1_INVERTED
#define LED2_INVERTED

#define USE_ACC
#define USE_ACC_MPU6500
#define ACC_MPU6500_ALIGN       CW0_DEG

#define MPU_ADDRESS 			0x69
#define USE_GYRO
#define USE_GYRO_MPU6500
#define GYRO_MPU6500_ALIGN      CW0_DEG

#define USE_MAG
#define USE_MPU9250_MAG
#define USE_MAG_AK8963
#define MAG_AK8963_ALIGN        CW90_DEG_FLIP

#define USE_BARO
#define USE_BARO_DPS310

#define USE_SDCARD

#define SDCARD_DETECT_INVERTED
#define SDCARD_DETECT_PIN               P110

#define SDCARD_SPI_INSTANCE             SPI2
#define SDCARD_SPI_CS_PIN               P41

// Divide to under 400kHz for init:
#define SDCARD_SPI_INITIALIZATION_CLOCK_DIVIDER 512 // 281kHz
// Divide to under 25MHz for normal operation:
#define SDCARD_SPI_FULL_SPEED_CLOCK_DIVIDER 8 // 18MHz

#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN            P14
#define UART1_TX_PIN            P15

#define USE_UART4
#define UART4_RX_PIN            P00
#define UART4_TX_PIN            P01

#define USE_UART6
#define UART6_RX_PIN			P34
#define UART6_TX_PIN			P35

#define SERIAL_PORT_COUNT       5

#define USE_SPI
#define USE_SPI_DEVICE_2

#define SPI2_NSS_PIN            P41
#define SPI2_SCK_PIN            P36
#define SPI2_MISO_PIN           P40
#define SPI2_MOSI_PIN           P35

#define USE_SPIS_DEVICE_3

#define SPI3_NSS_PIN            P06
#define SPI3_SCK_PIN            P011
#define SPI3_MISO_PIN           P05
#define SPI3_MOSI_PIN           P04

#define USE_I2C
#define USE_I2C_DEVICE_5
#define I2C_DEVICE              (I2CDEV_5)
#define I2C5_SCL                P52
#define I2C5_SDA                P50
#define I2C5_OVERCLOCK			true

#define USE_ADC
#define VBAT_ADC_PIN            P147

#define VBAT_SCALE_DEFAULT 46

#define ENABLE_BLACKBOX_LOGGING_ON_SDCARD_BY_DEFAULT

#define DEFAULT_FEATURES        (FEATURE_MOTOR_STOP)
#define DEFAULT_RX_FEATURE      FEATURE_RX_SERIAL
#define SERIALRX_UART           SERIAL_PORT_USART6
//#define RX_CHANNELS_TAER

#define USE_SERIAL_4WAY_BLHELI_INTERFACE

#define TARGET_IO_PORT0          0x1fff
#define TARGET_IO_PORT1          0xffff
#define TARGET_IO_PORT2          0xC7ff
#define TARGET_IO_PORT3          0x007f
#define TARGET_IO_PORT4          0x0003
#define TARGET_IO_PORT5          0x0087
#define TARGET_IO_PORT14         0xf3ff
#define TARGET_IO_PORT15         0x030C

#define USABLE_TIMER_CHANNEL_COUNT      13
//#define USED_TIMERS             ( TIM_N(1) | TIM_N(3) | TIM_N(4) | TIM_N(5) | TIM_N(8) )
#define USED_TIMERS             ( TIM_N(1) )

#define SPI2 USIC0_CH1
#define SPI3 USIC1_CH0

#define ADC1 VADC
