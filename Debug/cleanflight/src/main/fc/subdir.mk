################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/fc/board_info.c \
../cleanflight/src/main/fc/config.c \
../cleanflight/src/main/fc/controlrate_profile.c \
../cleanflight/src/main/fc/fc_core.c \
../cleanflight/src/main/fc/fc_dispatch.c \
../cleanflight/src/main/fc/fc_hardfaults.c \
../cleanflight/src/main/fc/fc_init.c \
../cleanflight/src/main/fc/fc_rc.c \
../cleanflight/src/main/fc/fc_tasks.c \
../cleanflight/src/main/fc/rc_adjustments.c \
../cleanflight/src/main/fc/rc_controls.c \
../cleanflight/src/main/fc/rc_modes.c \
../cleanflight/src/main/fc/runtime_config.c 

OBJS += \
./cleanflight/src/main/fc/board_info.o \
./cleanflight/src/main/fc/config.o \
./cleanflight/src/main/fc/controlrate_profile.o \
./cleanflight/src/main/fc/fc_core.o \
./cleanflight/src/main/fc/fc_dispatch.o \
./cleanflight/src/main/fc/fc_hardfaults.o \
./cleanflight/src/main/fc/fc_init.o \
./cleanflight/src/main/fc/fc_rc.o \
./cleanflight/src/main/fc/fc_tasks.o \
./cleanflight/src/main/fc/rc_adjustments.o \
./cleanflight/src/main/fc/rc_controls.o \
./cleanflight/src/main/fc/rc_modes.o \
./cleanflight/src/main/fc/runtime_config.o 

C_DEPS += \
./cleanflight/src/main/fc/board_info.d \
./cleanflight/src/main/fc/config.d \
./cleanflight/src/main/fc/controlrate_profile.d \
./cleanflight/src/main/fc/fc_core.d \
./cleanflight/src/main/fc/fc_dispatch.d \
./cleanflight/src/main/fc/fc_hardfaults.d \
./cleanflight/src/main/fc/fc_init.d \
./cleanflight/src/main/fc/fc_rc.d \
./cleanflight/src/main/fc/fc_tasks.d \
./cleanflight/src/main/fc/rc_adjustments.d \
./cleanflight/src/main/fc/rc_controls.d \
./cleanflight/src/main/fc/rc_modes.d \
./cleanflight/src/main/fc/runtime_config.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/fc/%.o: ../cleanflight/src/main/fc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

