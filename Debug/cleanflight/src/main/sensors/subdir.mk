################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/sensors/acceleration.c \
../cleanflight/src/main/sensors/adcinternal.c \
../cleanflight/src/main/sensors/barometer.c \
../cleanflight/src/main/sensors/battery.c \
../cleanflight/src/main/sensors/boardalignment.c \
../cleanflight/src/main/sensors/compass.c \
../cleanflight/src/main/sensors/current.c \
../cleanflight/src/main/sensors/esc_sensor.c \
../cleanflight/src/main/sensors/gyro.c \
../cleanflight/src/main/sensors/gyroanalyse.c \
../cleanflight/src/main/sensors/initialisation.c \
../cleanflight/src/main/sensors/rangefinder.c \
../cleanflight/src/main/sensors/voltage.c 

OBJS += \
./cleanflight/src/main/sensors/acceleration.o \
./cleanflight/src/main/sensors/adcinternal.o \
./cleanflight/src/main/sensors/barometer.o \
./cleanflight/src/main/sensors/battery.o \
./cleanflight/src/main/sensors/boardalignment.o \
./cleanflight/src/main/sensors/compass.o \
./cleanflight/src/main/sensors/current.o \
./cleanflight/src/main/sensors/esc_sensor.o \
./cleanflight/src/main/sensors/gyro.o \
./cleanflight/src/main/sensors/gyroanalyse.o \
./cleanflight/src/main/sensors/initialisation.o \
./cleanflight/src/main/sensors/rangefinder.o \
./cleanflight/src/main/sensors/voltage.o 

C_DEPS += \
./cleanflight/src/main/sensors/acceleration.d \
./cleanflight/src/main/sensors/adcinternal.d \
./cleanflight/src/main/sensors/barometer.d \
./cleanflight/src/main/sensors/battery.d \
./cleanflight/src/main/sensors/boardalignment.d \
./cleanflight/src/main/sensors/compass.d \
./cleanflight/src/main/sensors/current.d \
./cleanflight/src/main/sensors/esc_sensor.d \
./cleanflight/src/main/sensors/gyro.d \
./cleanflight/src/main/sensors/gyroanalyse.d \
./cleanflight/src/main/sensors/initialisation.d \
./cleanflight/src/main/sensors/rangefinder.d \
./cleanflight/src/main/sensors/voltage.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/sensors/%.o: ../cleanflight/src/main/sensors/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

