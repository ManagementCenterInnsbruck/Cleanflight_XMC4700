################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/telemetry/crsf.c \
../cleanflight/src/main/telemetry/frsky_hub.c \
../cleanflight/src/main/telemetry/hott.c \
../cleanflight/src/main/telemetry/ibus.c \
../cleanflight/src/main/telemetry/ibus_shared.c \
../cleanflight/src/main/telemetry/jetiexbus.c \
../cleanflight/src/main/telemetry/ltm.c \
../cleanflight/src/main/telemetry/mavlink.c \
../cleanflight/src/main/telemetry/msp_shared.c \
../cleanflight/src/main/telemetry/smartport.c \
../cleanflight/src/main/telemetry/srxl.c \
../cleanflight/src/main/telemetry/telemetry.c 

OBJS += \
./cleanflight/src/main/telemetry/crsf.o \
./cleanflight/src/main/telemetry/frsky_hub.o \
./cleanflight/src/main/telemetry/hott.o \
./cleanflight/src/main/telemetry/ibus.o \
./cleanflight/src/main/telemetry/ibus_shared.o \
./cleanflight/src/main/telemetry/jetiexbus.o \
./cleanflight/src/main/telemetry/ltm.o \
./cleanflight/src/main/telemetry/mavlink.o \
./cleanflight/src/main/telemetry/msp_shared.o \
./cleanflight/src/main/telemetry/smartport.o \
./cleanflight/src/main/telemetry/srxl.o \
./cleanflight/src/main/telemetry/telemetry.o 

C_DEPS += \
./cleanflight/src/main/telemetry/crsf.d \
./cleanflight/src/main/telemetry/frsky_hub.d \
./cleanflight/src/main/telemetry/hott.d \
./cleanflight/src/main/telemetry/ibus.d \
./cleanflight/src/main/telemetry/ibus_shared.d \
./cleanflight/src/main/telemetry/jetiexbus.d \
./cleanflight/src/main/telemetry/ltm.d \
./cleanflight/src/main/telemetry/mavlink.d \
./cleanflight/src/main/telemetry/msp_shared.d \
./cleanflight/src/main/telemetry/smartport.d \
./cleanflight/src/main/telemetry/srxl.d \
./cleanflight/src/main/telemetry/telemetry.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/telemetry/%.o: ../cleanflight/src/main/telemetry/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

