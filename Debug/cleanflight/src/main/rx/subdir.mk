################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/rx/cc2500_frsky_d.c \
../cleanflight/src/main/rx/cc2500_frsky_shared.c \
../cleanflight/src/main/rx/cc2500_frsky_x.c \
../cleanflight/src/main/rx/crsf.c \
../cleanflight/src/main/rx/flysky.c \
../cleanflight/src/main/rx/fport.c \
../cleanflight/src/main/rx/ibus.c \
../cleanflight/src/main/rx/jetiexbus.c \
../cleanflight/src/main/rx/msp.c \
../cleanflight/src/main/rx/nrf24_cx10.c \
../cleanflight/src/main/rx/nrf24_h8_3d.c \
../cleanflight/src/main/rx/nrf24_inav.c \
../cleanflight/src/main/rx/nrf24_kn.c \
../cleanflight/src/main/rx/nrf24_syma.c \
../cleanflight/src/main/rx/nrf24_v202.c \
../cleanflight/src/main/rx/pwm.c \
../cleanflight/src/main/rx/rx.c \
../cleanflight/src/main/rx/rx_spi.c \
../cleanflight/src/main/rx/sbus.c \
../cleanflight/src/main/rx/sbus_channels.c \
../cleanflight/src/main/rx/spektrum.c \
../cleanflight/src/main/rx/sumd.c \
../cleanflight/src/main/rx/sumh.c \
../cleanflight/src/main/rx/xbus.c 

OBJS += \
./cleanflight/src/main/rx/cc2500_frsky_d.o \
./cleanflight/src/main/rx/cc2500_frsky_shared.o \
./cleanflight/src/main/rx/cc2500_frsky_x.o \
./cleanflight/src/main/rx/crsf.o \
./cleanflight/src/main/rx/flysky.o \
./cleanflight/src/main/rx/fport.o \
./cleanflight/src/main/rx/ibus.o \
./cleanflight/src/main/rx/jetiexbus.o \
./cleanflight/src/main/rx/msp.o \
./cleanflight/src/main/rx/nrf24_cx10.o \
./cleanflight/src/main/rx/nrf24_h8_3d.o \
./cleanflight/src/main/rx/nrf24_inav.o \
./cleanflight/src/main/rx/nrf24_kn.o \
./cleanflight/src/main/rx/nrf24_syma.o \
./cleanflight/src/main/rx/nrf24_v202.o \
./cleanflight/src/main/rx/pwm.o \
./cleanflight/src/main/rx/rx.o \
./cleanflight/src/main/rx/rx_spi.o \
./cleanflight/src/main/rx/sbus.o \
./cleanflight/src/main/rx/sbus_channels.o \
./cleanflight/src/main/rx/spektrum.o \
./cleanflight/src/main/rx/sumd.o \
./cleanflight/src/main/rx/sumh.o \
./cleanflight/src/main/rx/xbus.o 

C_DEPS += \
./cleanflight/src/main/rx/cc2500_frsky_d.d \
./cleanflight/src/main/rx/cc2500_frsky_shared.d \
./cleanflight/src/main/rx/cc2500_frsky_x.d \
./cleanflight/src/main/rx/crsf.d \
./cleanflight/src/main/rx/flysky.d \
./cleanflight/src/main/rx/fport.d \
./cleanflight/src/main/rx/ibus.d \
./cleanflight/src/main/rx/jetiexbus.d \
./cleanflight/src/main/rx/msp.d \
./cleanflight/src/main/rx/nrf24_cx10.d \
./cleanflight/src/main/rx/nrf24_h8_3d.d \
./cleanflight/src/main/rx/nrf24_inav.d \
./cleanflight/src/main/rx/nrf24_kn.d \
./cleanflight/src/main/rx/nrf24_syma.d \
./cleanflight/src/main/rx/nrf24_v202.d \
./cleanflight/src/main/rx/pwm.d \
./cleanflight/src/main/rx/rx.d \
./cleanflight/src/main/rx/rx_spi.d \
./cleanflight/src/main/rx/sbus.d \
./cleanflight/src/main/rx/sbus_channels.d \
./cleanflight/src/main/rx/spektrum.d \
./cleanflight/src/main/rx/sumd.d \
./cleanflight/src/main/rx/sumh.d \
./cleanflight/src/main/rx/xbus.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/rx/%.o: ../cleanflight/src/main/rx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

