################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../cleanflight/src/main/startup/startup_XMC4700.S 

OBJS += \
./cleanflight/src/main/startup/startup_XMC4700.o 

S_UPPER_DEPS += \
./cleanflight/src/main/startup/startup_XMC4700.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/startup/%.o: ../cleanflight/src/main/startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC Assembler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -x assembler-with-cpp -DXMC4700_F100x2048 -Wall -Wa,-adhlns="$@.lst" -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

