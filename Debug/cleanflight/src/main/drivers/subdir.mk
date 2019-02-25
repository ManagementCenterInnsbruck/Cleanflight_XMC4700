################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/drivers/adc.c \
../cleanflight/src/main/drivers/adc_xmc4700.c \
../cleanflight/src/main/drivers/buf_writer.c \
../cleanflight/src/main/drivers/bus.c \
../cleanflight/src/main/drivers/bus_i2c_busdev.c \
../cleanflight/src/main/drivers/bus_i2c_config.c \
../cleanflight/src/main/drivers/bus_i2c_soft.c \
../cleanflight/src/main/drivers/bus_i2c_xmc4700.c \
../cleanflight/src/main/drivers/bus_spi.c \
../cleanflight/src/main/drivers/bus_spi_config.c \
../cleanflight/src/main/drivers/bus_spi_pinconfig.c \
../cleanflight/src/main/drivers/bus_spi_xmc4700.c \
../cleanflight/src/main/drivers/buttons.c \
../cleanflight/src/main/drivers/camera_control.c \
../cleanflight/src/main/drivers/display.c \
../cleanflight/src/main/drivers/display_ug2864hsweg01.c \
../cleanflight/src/main/drivers/dma.c \
../cleanflight/src/main/drivers/exti.c \
../cleanflight/src/main/drivers/flash.c \
../cleanflight/src/main/drivers/flash_m25p16.c \
../cleanflight/src/main/drivers/flash_w25m.c \
../cleanflight/src/main/drivers/inverter.c \
../cleanflight/src/main/drivers/io.c \
../cleanflight/src/main/drivers/light_led.c \
../cleanflight/src/main/drivers/light_ws2811strip.c \
../cleanflight/src/main/drivers/light_ws2811strip_hal.c \
../cleanflight/src/main/drivers/light_ws2811strip_stdperiph.c \
../cleanflight/src/main/drivers/max7456.c \
../cleanflight/src/main/drivers/pinio.c \
../cleanflight/src/main/drivers/pwm_esc_detect.c \
../cleanflight/src/main/drivers/pwm_output.c \
../cleanflight/src/main/drivers/pwm_output_dshot.c \
../cleanflight/src/main/drivers/pwm_output_dshot_hal.c \
../cleanflight/src/main/drivers/resource.c \
../cleanflight/src/main/drivers/sdcard.c \
../cleanflight/src/main/drivers/sdcard_standard.c \
../cleanflight/src/main/drivers/serial.c \
../cleanflight/src/main/drivers/serial_escserial.c \
../cleanflight/src/main/drivers/serial_pinconfig.c \
../cleanflight/src/main/drivers/serial_softserial.c \
../cleanflight/src/main/drivers/serial_spi_slave.c \
../cleanflight/src/main/drivers/serial_uart.c \
../cleanflight/src/main/drivers/serial_uart_init.c \
../cleanflight/src/main/drivers/serial_uart_pinconfig.c \
../cleanflight/src/main/drivers/serial_uart_xmc4700.c \
../cleanflight/src/main/drivers/serial_usb_vcp.c \
../cleanflight/src/main/drivers/sound_beeper.c \
../cleanflight/src/main/drivers/stack_check.c \
../cleanflight/src/main/drivers/system.c \
../cleanflight/src/main/drivers/system_xmc4700.c \
../cleanflight/src/main/drivers/timer.c \
../cleanflight/src/main/drivers/timer_common.c \
../cleanflight/src/main/drivers/timer_xmc4700.c \
../cleanflight/src/main/drivers/transponder_ir_arcitimer.c \
../cleanflight/src/main/drivers/transponder_ir_erlt.c \
../cleanflight/src/main/drivers/transponder_ir_ilap.c \
../cleanflight/src/main/drivers/transponder_ir_io_hal.c \
../cleanflight/src/main/drivers/transponder_ir_io_stdperiph.c \
../cleanflight/src/main/drivers/usb_io.c \
../cleanflight/src/main/drivers/usb_msc_f4xx.c \
../cleanflight/src/main/drivers/usb_msc_f7xx.c \
../cleanflight/src/main/drivers/vtx_common.c \
../cleanflight/src/main/drivers/vtx_rtc6705.c \
../cleanflight/src/main/drivers/vtx_rtc6705_soft_spi.c 

OBJS += \
./cleanflight/src/main/drivers/adc.o \
./cleanflight/src/main/drivers/adc_xmc4700.o \
./cleanflight/src/main/drivers/buf_writer.o \
./cleanflight/src/main/drivers/bus.o \
./cleanflight/src/main/drivers/bus_i2c_busdev.o \
./cleanflight/src/main/drivers/bus_i2c_config.o \
./cleanflight/src/main/drivers/bus_i2c_soft.o \
./cleanflight/src/main/drivers/bus_i2c_xmc4700.o \
./cleanflight/src/main/drivers/bus_spi.o \
./cleanflight/src/main/drivers/bus_spi_config.o \
./cleanflight/src/main/drivers/bus_spi_pinconfig.o \
./cleanflight/src/main/drivers/bus_spi_xmc4700.o \
./cleanflight/src/main/drivers/buttons.o \
./cleanflight/src/main/drivers/camera_control.o \
./cleanflight/src/main/drivers/display.o \
./cleanflight/src/main/drivers/display_ug2864hsweg01.o \
./cleanflight/src/main/drivers/dma.o \
./cleanflight/src/main/drivers/exti.o \
./cleanflight/src/main/drivers/flash.o \
./cleanflight/src/main/drivers/flash_m25p16.o \
./cleanflight/src/main/drivers/flash_w25m.o \
./cleanflight/src/main/drivers/inverter.o \
./cleanflight/src/main/drivers/io.o \
./cleanflight/src/main/drivers/light_led.o \
./cleanflight/src/main/drivers/light_ws2811strip.o \
./cleanflight/src/main/drivers/light_ws2811strip_hal.o \
./cleanflight/src/main/drivers/light_ws2811strip_stdperiph.o \
./cleanflight/src/main/drivers/max7456.o \
./cleanflight/src/main/drivers/pinio.o \
./cleanflight/src/main/drivers/pwm_esc_detect.o \
./cleanflight/src/main/drivers/pwm_output.o \
./cleanflight/src/main/drivers/pwm_output_dshot.o \
./cleanflight/src/main/drivers/pwm_output_dshot_hal.o \
./cleanflight/src/main/drivers/resource.o \
./cleanflight/src/main/drivers/sdcard.o \
./cleanflight/src/main/drivers/sdcard_standard.o \
./cleanflight/src/main/drivers/serial.o \
./cleanflight/src/main/drivers/serial_escserial.o \
./cleanflight/src/main/drivers/serial_pinconfig.o \
./cleanflight/src/main/drivers/serial_softserial.o \
./cleanflight/src/main/drivers/serial_spi_slave.o \
./cleanflight/src/main/drivers/serial_uart.o \
./cleanflight/src/main/drivers/serial_uart_init.o \
./cleanflight/src/main/drivers/serial_uart_pinconfig.o \
./cleanflight/src/main/drivers/serial_uart_xmc4700.o \
./cleanflight/src/main/drivers/serial_usb_vcp.o \
./cleanflight/src/main/drivers/sound_beeper.o \
./cleanflight/src/main/drivers/stack_check.o \
./cleanflight/src/main/drivers/system.o \
./cleanflight/src/main/drivers/system_xmc4700.o \
./cleanflight/src/main/drivers/timer.o \
./cleanflight/src/main/drivers/timer_common.o \
./cleanflight/src/main/drivers/timer_xmc4700.o \
./cleanflight/src/main/drivers/transponder_ir_arcitimer.o \
./cleanflight/src/main/drivers/transponder_ir_erlt.o \
./cleanflight/src/main/drivers/transponder_ir_ilap.o \
./cleanflight/src/main/drivers/transponder_ir_io_hal.o \
./cleanflight/src/main/drivers/transponder_ir_io_stdperiph.o \
./cleanflight/src/main/drivers/usb_io.o \
./cleanflight/src/main/drivers/usb_msc_f4xx.o \
./cleanflight/src/main/drivers/usb_msc_f7xx.o \
./cleanflight/src/main/drivers/vtx_common.o \
./cleanflight/src/main/drivers/vtx_rtc6705.o \
./cleanflight/src/main/drivers/vtx_rtc6705_soft_spi.o 

C_DEPS += \
./cleanflight/src/main/drivers/adc.d \
./cleanflight/src/main/drivers/adc_xmc4700.d \
./cleanflight/src/main/drivers/buf_writer.d \
./cleanflight/src/main/drivers/bus.d \
./cleanflight/src/main/drivers/bus_i2c_busdev.d \
./cleanflight/src/main/drivers/bus_i2c_config.d \
./cleanflight/src/main/drivers/bus_i2c_soft.d \
./cleanflight/src/main/drivers/bus_i2c_xmc4700.d \
./cleanflight/src/main/drivers/bus_spi.d \
./cleanflight/src/main/drivers/bus_spi_config.d \
./cleanflight/src/main/drivers/bus_spi_pinconfig.d \
./cleanflight/src/main/drivers/bus_spi_xmc4700.d \
./cleanflight/src/main/drivers/buttons.d \
./cleanflight/src/main/drivers/camera_control.d \
./cleanflight/src/main/drivers/display.d \
./cleanflight/src/main/drivers/display_ug2864hsweg01.d \
./cleanflight/src/main/drivers/dma.d \
./cleanflight/src/main/drivers/exti.d \
./cleanflight/src/main/drivers/flash.d \
./cleanflight/src/main/drivers/flash_m25p16.d \
./cleanflight/src/main/drivers/flash_w25m.d \
./cleanflight/src/main/drivers/inverter.d \
./cleanflight/src/main/drivers/io.d \
./cleanflight/src/main/drivers/light_led.d \
./cleanflight/src/main/drivers/light_ws2811strip.d \
./cleanflight/src/main/drivers/light_ws2811strip_hal.d \
./cleanflight/src/main/drivers/light_ws2811strip_stdperiph.d \
./cleanflight/src/main/drivers/max7456.d \
./cleanflight/src/main/drivers/pinio.d \
./cleanflight/src/main/drivers/pwm_esc_detect.d \
./cleanflight/src/main/drivers/pwm_output.d \
./cleanflight/src/main/drivers/pwm_output_dshot.d \
./cleanflight/src/main/drivers/pwm_output_dshot_hal.d \
./cleanflight/src/main/drivers/resource.d \
./cleanflight/src/main/drivers/sdcard.d \
./cleanflight/src/main/drivers/sdcard_standard.d \
./cleanflight/src/main/drivers/serial.d \
./cleanflight/src/main/drivers/serial_escserial.d \
./cleanflight/src/main/drivers/serial_pinconfig.d \
./cleanflight/src/main/drivers/serial_softserial.d \
./cleanflight/src/main/drivers/serial_spi_slave.d \
./cleanflight/src/main/drivers/serial_uart.d \
./cleanflight/src/main/drivers/serial_uart_init.d \
./cleanflight/src/main/drivers/serial_uart_pinconfig.d \
./cleanflight/src/main/drivers/serial_uart_xmc4700.d \
./cleanflight/src/main/drivers/serial_usb_vcp.d \
./cleanflight/src/main/drivers/sound_beeper.d \
./cleanflight/src/main/drivers/stack_check.d \
./cleanflight/src/main/drivers/system.d \
./cleanflight/src/main/drivers/system_xmc4700.d \
./cleanflight/src/main/drivers/timer.d \
./cleanflight/src/main/drivers/timer_common.d \
./cleanflight/src/main/drivers/timer_xmc4700.d \
./cleanflight/src/main/drivers/transponder_ir_arcitimer.d \
./cleanflight/src/main/drivers/transponder_ir_erlt.d \
./cleanflight/src/main/drivers/transponder_ir_ilap.d \
./cleanflight/src/main/drivers/transponder_ir_io_hal.d \
./cleanflight/src/main/drivers/transponder_ir_io_stdperiph.d \
./cleanflight/src/main/drivers/usb_io.d \
./cleanflight/src/main/drivers/usb_msc_f4xx.d \
./cleanflight/src/main/drivers/usb_msc_f7xx.d \
./cleanflight/src/main/drivers/vtx_common.d \
./cleanflight/src/main/drivers/vtx_rtc6705.d \
./cleanflight/src/main/drivers/vtx_rtc6705_soft_spi.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/drivers/%.o: ../cleanflight/src/main/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

