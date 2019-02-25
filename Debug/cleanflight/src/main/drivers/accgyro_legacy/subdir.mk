################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/drivers/accgyro_legacy/accgyro_adxl345.c \
../cleanflight/src/main/drivers/accgyro_legacy/accgyro_bma280.c \
../cleanflight/src/main/drivers/accgyro_legacy/accgyro_l3g4200d.c \
../cleanflight/src/main/drivers/accgyro_legacy/accgyro_l3gd20.c \
../cleanflight/src/main/drivers/accgyro_legacy/accgyro_lsm303dlhc.c \
../cleanflight/src/main/drivers/accgyro_legacy/accgyro_mma845x.c 

OBJS += \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_adxl345.o \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_bma280.o \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_l3g4200d.o \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_l3gd20.o \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_lsm303dlhc.o \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_mma845x.o 

C_DEPS += \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_adxl345.d \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_bma280.d \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_l3g4200d.d \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_l3gd20.d \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_lsm303dlhc.d \
./cleanflight/src/main/drivers/accgyro_legacy/accgyro_mma845x.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/drivers/accgyro_legacy/%.o: ../cleanflight/src/main/drivers/accgyro_legacy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

