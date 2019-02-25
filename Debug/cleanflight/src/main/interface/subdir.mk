################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/interface/cli.c \
../cleanflight/src/main/interface/msp.c \
../cleanflight/src/main/interface/msp_box.c \
../cleanflight/src/main/interface/settings.c \
../cleanflight/src/main/interface/smartaudio_protocol.c \
../cleanflight/src/main/interface/tramp_protocol.c 

OBJS += \
./cleanflight/src/main/interface/cli.o \
./cleanflight/src/main/interface/msp.o \
./cleanflight/src/main/interface/msp_box.o \
./cleanflight/src/main/interface/settings.o \
./cleanflight/src/main/interface/smartaudio_protocol.o \
./cleanflight/src/main/interface/tramp_protocol.o 

C_DEPS += \
./cleanflight/src/main/interface/cli.d \
./cleanflight/src/main/interface/msp.d \
./cleanflight/src/main/interface/msp_box.d \
./cleanflight/src/main/interface/settings.d \
./cleanflight/src/main/interface/smartaudio_protocol.d \
./cleanflight/src/main/interface/tramp_protocol.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/interface/%.o: ../cleanflight/src/main/interface/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.
