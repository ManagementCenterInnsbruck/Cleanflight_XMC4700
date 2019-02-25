################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/drivers/compass/compass_ak8963.c \
../cleanflight/src/main/drivers/compass/compass_ak8975.c \
../cleanflight/src/main/drivers/compass/compass_fake.c \
../cleanflight/src/main/drivers/compass/compass_hmc5883l.c \
../cleanflight/src/main/drivers/compass/compass_qmc5883l.c 

OBJS += \
./cleanflight/src/main/drivers/compass/compass_ak8963.o \
./cleanflight/src/main/drivers/compass/compass_ak8975.o \
./cleanflight/src/main/drivers/compass/compass_fake.o \
./cleanflight/src/main/drivers/compass/compass_hmc5883l.o \
./cleanflight/src/main/drivers/compass/compass_qmc5883l.o 

C_DEPS += \
./cleanflight/src/main/drivers/compass/compass_ak8963.d \
./cleanflight/src/main/drivers/compass/compass_ak8975.d \
./cleanflight/src/main/drivers/compass/compass_fake.d \
./cleanflight/src/main/drivers/compass/compass_hmc5883l.d \
./cleanflight/src/main/drivers/compass/compass_qmc5883l.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/drivers/compass/%.o: ../cleanflight/src/main/drivers/compass/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

