################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/pg/adc.c \
../cleanflight/src/main/pg/beeper.c \
../cleanflight/src/main/pg/beeper_dev.c \
../cleanflight/src/main/pg/board.c \
../cleanflight/src/main/pg/bus_i2c.c \
../cleanflight/src/main/pg/bus_spi.c \
../cleanflight/src/main/pg/dashboard.c \
../cleanflight/src/main/pg/flash.c \
../cleanflight/src/main/pg/max7456.c \
../cleanflight/src/main/pg/pg.c \
../cleanflight/src/main/pg/pinio.c \
../cleanflight/src/main/pg/piniobox.c \
../cleanflight/src/main/pg/rcdevice.c \
../cleanflight/src/main/pg/rx.c \
../cleanflight/src/main/pg/rx_pwm.c \
../cleanflight/src/main/pg/rx_spi.c \
../cleanflight/src/main/pg/sdcard.c \
../cleanflight/src/main/pg/sdio.c \
../cleanflight/src/main/pg/timerio.c \
../cleanflight/src/main/pg/usb.c \
../cleanflight/src/main/pg/vcd.c 

OBJS += \
./cleanflight/src/main/pg/adc.o \
./cleanflight/src/main/pg/beeper.o \
./cleanflight/src/main/pg/beeper_dev.o \
./cleanflight/src/main/pg/board.o \
./cleanflight/src/main/pg/bus_i2c.o \
./cleanflight/src/main/pg/bus_spi.o \
./cleanflight/src/main/pg/dashboard.o \
./cleanflight/src/main/pg/flash.o \
./cleanflight/src/main/pg/max7456.o \
./cleanflight/src/main/pg/pg.o \
./cleanflight/src/main/pg/pinio.o \
./cleanflight/src/main/pg/piniobox.o \
./cleanflight/src/main/pg/rcdevice.o \
./cleanflight/src/main/pg/rx.o \
./cleanflight/src/main/pg/rx_pwm.o \
./cleanflight/src/main/pg/rx_spi.o \
./cleanflight/src/main/pg/sdcard.o \
./cleanflight/src/main/pg/sdio.o \
./cleanflight/src/main/pg/timerio.o \
./cleanflight/src/main/pg/usb.o \
./cleanflight/src/main/pg/vcd.o 

C_DEPS += \
./cleanflight/src/main/pg/adc.d \
./cleanflight/src/main/pg/beeper.d \
./cleanflight/src/main/pg/beeper_dev.d \
./cleanflight/src/main/pg/board.d \
./cleanflight/src/main/pg/bus_i2c.d \
./cleanflight/src/main/pg/bus_spi.d \
./cleanflight/src/main/pg/dashboard.d \
./cleanflight/src/main/pg/flash.d \
./cleanflight/src/main/pg/max7456.d \
./cleanflight/src/main/pg/pg.d \
./cleanflight/src/main/pg/pinio.d \
./cleanflight/src/main/pg/piniobox.d \
./cleanflight/src/main/pg/rcdevice.d \
./cleanflight/src/main/pg/rx.d \
./cleanflight/src/main/pg/rx_pwm.d \
./cleanflight/src/main/pg/rx_spi.d \
./cleanflight/src/main/pg/sdcard.d \
./cleanflight/src/main/pg/sdio.d \
./cleanflight/src/main/pg/timerio.d \
./cleanflight/src/main/pg/usb.d \
./cleanflight/src/main/pg/vcd.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/pg/%.o: ../cleanflight/src/main/pg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

