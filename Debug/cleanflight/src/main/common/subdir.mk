################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/common/bitarray.c \
../cleanflight/src/main/common/colorconversion.c \
../cleanflight/src/main/common/crc.c \
../cleanflight/src/main/common/encoding.c \
../cleanflight/src/main/common/explog_approx.c \
../cleanflight/src/main/common/filter.c \
../cleanflight/src/main/common/gps_conversion.c \
../cleanflight/src/main/common/huffman.c \
../cleanflight/src/main/common/huffman_table.c \
../cleanflight/src/main/common/maths.c \
../cleanflight/src/main/common/printf.c \
../cleanflight/src/main/common/streambuf.c \
../cleanflight/src/main/common/string_light.c \
../cleanflight/src/main/common/strtol.c \
../cleanflight/src/main/common/time.c \
../cleanflight/src/main/common/typeconversion.c 

OBJS += \
./cleanflight/src/main/common/bitarray.o \
./cleanflight/src/main/common/colorconversion.o \
./cleanflight/src/main/common/crc.o \
./cleanflight/src/main/common/encoding.o \
./cleanflight/src/main/common/explog_approx.o \
./cleanflight/src/main/common/filter.o \
./cleanflight/src/main/common/gps_conversion.o \
./cleanflight/src/main/common/huffman.o \
./cleanflight/src/main/common/huffman_table.o \
./cleanflight/src/main/common/maths.o \
./cleanflight/src/main/common/printf.o \
./cleanflight/src/main/common/streambuf.o \
./cleanflight/src/main/common/string_light.o \
./cleanflight/src/main/common/strtol.o \
./cleanflight/src/main/common/time.o \
./cleanflight/src/main/common/typeconversion.o 

C_DEPS += \
./cleanflight/src/main/common/bitarray.d \
./cleanflight/src/main/common/colorconversion.d \
./cleanflight/src/main/common/crc.d \
./cleanflight/src/main/common/encoding.d \
./cleanflight/src/main/common/explog_approx.d \
./cleanflight/src/main/common/filter.d \
./cleanflight/src/main/common/gps_conversion.d \
./cleanflight/src/main/common/huffman.d \
./cleanflight/src/main/common/huffman_table.d \
./cleanflight/src/main/common/maths.d \
./cleanflight/src/main/common/printf.d \
./cleanflight/src/main/common/streambuf.d \
./cleanflight/src/main/common/string_light.d \
./cleanflight/src/main/common/strtol.d \
./cleanflight/src/main/common/time.d \
./cleanflight/src/main/common/typeconversion.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/common/%.o: ../cleanflight/src/main/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

