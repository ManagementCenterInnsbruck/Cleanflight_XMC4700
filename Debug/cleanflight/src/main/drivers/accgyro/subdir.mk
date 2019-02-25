################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/drivers/accgyro/accgyro_fake.c \
../cleanflight/src/main/drivers/accgyro/accgyro_mpu.c \
../cleanflight/src/main/drivers/accgyro/accgyro_mpu3050.c \
../cleanflight/src/main/drivers/accgyro/accgyro_mpu6050.c \
../cleanflight/src/main/drivers/accgyro/accgyro_mpu6500.c \
../cleanflight/src/main/drivers/accgyro/accgyro_spi_bmi160.c \
../cleanflight/src/main/drivers/accgyro/accgyro_spi_icm20649.c \
../cleanflight/src/main/drivers/accgyro/accgyro_spi_icm20689.c \
../cleanflight/src/main/drivers/accgyro/accgyro_spi_mpu6000.c \
../cleanflight/src/main/drivers/accgyro/accgyro_spi_mpu6500.c \
../cleanflight/src/main/drivers/accgyro/accgyro_spi_mpu9250.c \
../cleanflight/src/main/drivers/accgyro/gyro_sync.c 

OBJS += \
./cleanflight/src/main/drivers/accgyro/accgyro_fake.o \
./cleanflight/src/main/drivers/accgyro/accgyro_mpu.o \
./cleanflight/src/main/drivers/accgyro/accgyro_mpu3050.o \
./cleanflight/src/main/drivers/accgyro/accgyro_mpu6050.o \
./cleanflight/src/main/drivers/accgyro/accgyro_mpu6500.o \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_bmi160.o \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_icm20649.o \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_icm20689.o \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_mpu6000.o \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_mpu6500.o \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_mpu9250.o \
./cleanflight/src/main/drivers/accgyro/gyro_sync.o 

C_DEPS += \
./cleanflight/src/main/drivers/accgyro/accgyro_fake.d \
./cleanflight/src/main/drivers/accgyro/accgyro_mpu.d \
./cleanflight/src/main/drivers/accgyro/accgyro_mpu3050.d \
./cleanflight/src/main/drivers/accgyro/accgyro_mpu6050.d \
./cleanflight/src/main/drivers/accgyro/accgyro_mpu6500.d \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_bmi160.d \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_icm20649.d \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_icm20689.d \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_mpu6000.d \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_mpu6500.d \
./cleanflight/src/main/drivers/accgyro/accgyro_spi_mpu9250.d \
./cleanflight/src/main/drivers/accgyro/gyro_sync.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/drivers/accgyro/%.o: ../cleanflight/src/main/drivers/accgyro/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

