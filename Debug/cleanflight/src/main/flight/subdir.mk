################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/flight/failsafe.c \
../cleanflight/src/main/flight/gps_rescue.c \
../cleanflight/src/main/flight/imu.c \
../cleanflight/src/main/flight/mixer.c \
../cleanflight/src/main/flight/mixer_tricopter.c \
../cleanflight/src/main/flight/pid.c \
../cleanflight/src/main/flight/position.c \
../cleanflight/src/main/flight/servos.c \
../cleanflight/src/main/flight/servos_tricopter.c 

OBJS += \
./cleanflight/src/main/flight/failsafe.o \
./cleanflight/src/main/flight/gps_rescue.o \
./cleanflight/src/main/flight/imu.o \
./cleanflight/src/main/flight/mixer.o \
./cleanflight/src/main/flight/mixer_tricopter.o \
./cleanflight/src/main/flight/pid.o \
./cleanflight/src/main/flight/position.o \
./cleanflight/src/main/flight/servos.o \
./cleanflight/src/main/flight/servos_tricopter.o 

C_DEPS += \
./cleanflight/src/main/flight/failsafe.d \
./cleanflight/src/main/flight/gps_rescue.d \
./cleanflight/src/main/flight/imu.d \
./cleanflight/src/main/flight/mixer.d \
./cleanflight/src/main/flight/mixer_tricopter.d \
./cleanflight/src/main/flight/pid.d \
./cleanflight/src/main/flight/position.d \
./cleanflight/src/main/flight/servos.d \
./cleanflight/src/main/flight/servos_tricopter.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/flight/%.o: ../cleanflight/src/main/flight/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

