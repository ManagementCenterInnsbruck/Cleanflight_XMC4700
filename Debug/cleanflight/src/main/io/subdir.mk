################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cleanflight/src/main/io/beeper.c \
../cleanflight/src/main/io/dashboard.c \
../cleanflight/src/main/io/displayport_crsf.c \
../cleanflight/src/main/io/displayport_max7456.c \
../cleanflight/src/main/io/displayport_msp.c \
../cleanflight/src/main/io/displayport_oled.c \
../cleanflight/src/main/io/displayport_srxl.c \
../cleanflight/src/main/io/flashfs.c \
../cleanflight/src/main/io/gps.c \
../cleanflight/src/main/io/ledstrip.c \
../cleanflight/src/main/io/osd.c \
../cleanflight/src/main/io/osd_slave.c \
../cleanflight/src/main/io/pidaudio.c \
../cleanflight/src/main/io/piniobox.c \
../cleanflight/src/main/io/rcdevice.c \
../cleanflight/src/main/io/rcdevice_cam.c \
../cleanflight/src/main/io/serial.c \
../cleanflight/src/main/io/serial_4way.c \
../cleanflight/src/main/io/serial_4way_avrootloader.c \
../cleanflight/src/main/io/serial_4way_stk500v2.c \
../cleanflight/src/main/io/spektrum_rssi.c \
../cleanflight/src/main/io/spektrum_vtx_control.c \
../cleanflight/src/main/io/statusindicator.c \
../cleanflight/src/main/io/transponder_ir.c \
../cleanflight/src/main/io/usb_cdc_hid.c \
../cleanflight/src/main/io/usb_msc.c \
../cleanflight/src/main/io/vtx.c \
../cleanflight/src/main/io/vtx_control.c \
../cleanflight/src/main/io/vtx_rtc6705.c \
../cleanflight/src/main/io/vtx_smartaudio.c \
../cleanflight/src/main/io/vtx_string.c \
../cleanflight/src/main/io/vtx_tramp.c 

OBJS += \
./cleanflight/src/main/io/beeper.o \
./cleanflight/src/main/io/dashboard.o \
./cleanflight/src/main/io/displayport_crsf.o \
./cleanflight/src/main/io/displayport_max7456.o \
./cleanflight/src/main/io/displayport_msp.o \
./cleanflight/src/main/io/displayport_oled.o \
./cleanflight/src/main/io/displayport_srxl.o \
./cleanflight/src/main/io/flashfs.o \
./cleanflight/src/main/io/gps.o \
./cleanflight/src/main/io/ledstrip.o \
./cleanflight/src/main/io/osd.o \
./cleanflight/src/main/io/osd_slave.o \
./cleanflight/src/main/io/pidaudio.o \
./cleanflight/src/main/io/piniobox.o \
./cleanflight/src/main/io/rcdevice.o \
./cleanflight/src/main/io/rcdevice_cam.o \
./cleanflight/src/main/io/serial.o \
./cleanflight/src/main/io/serial_4way.o \
./cleanflight/src/main/io/serial_4way_avrootloader.o \
./cleanflight/src/main/io/serial_4way_stk500v2.o \
./cleanflight/src/main/io/spektrum_rssi.o \
./cleanflight/src/main/io/spektrum_vtx_control.o \
./cleanflight/src/main/io/statusindicator.o \
./cleanflight/src/main/io/transponder_ir.o \
./cleanflight/src/main/io/usb_cdc_hid.o \
./cleanflight/src/main/io/usb_msc.o \
./cleanflight/src/main/io/vtx.o \
./cleanflight/src/main/io/vtx_control.o \
./cleanflight/src/main/io/vtx_rtc6705.o \
./cleanflight/src/main/io/vtx_smartaudio.o \
./cleanflight/src/main/io/vtx_string.o \
./cleanflight/src/main/io/vtx_tramp.o 

C_DEPS += \
./cleanflight/src/main/io/beeper.d \
./cleanflight/src/main/io/dashboard.d \
./cleanflight/src/main/io/displayport_crsf.d \
./cleanflight/src/main/io/displayport_max7456.d \
./cleanflight/src/main/io/displayport_msp.d \
./cleanflight/src/main/io/displayport_oled.d \
./cleanflight/src/main/io/displayport_srxl.d \
./cleanflight/src/main/io/flashfs.d \
./cleanflight/src/main/io/gps.d \
./cleanflight/src/main/io/ledstrip.d \
./cleanflight/src/main/io/osd.d \
./cleanflight/src/main/io/osd_slave.d \
./cleanflight/src/main/io/pidaudio.d \
./cleanflight/src/main/io/piniobox.d \
./cleanflight/src/main/io/rcdevice.d \
./cleanflight/src/main/io/rcdevice_cam.d \
./cleanflight/src/main/io/serial.d \
./cleanflight/src/main/io/serial_4way.d \
./cleanflight/src/main/io/serial_4way_avrootloader.d \
./cleanflight/src/main/io/serial_4way_stk500v2.d \
./cleanflight/src/main/io/spektrum_rssi.d \
./cleanflight/src/main/io/spektrum_vtx_control.d \
./cleanflight/src/main/io/statusindicator.d \
./cleanflight/src/main/io/transponder_ir.d \
./cleanflight/src/main/io/usb_cdc_hid.d \
./cleanflight/src/main/io/usb_msc.d \
./cleanflight/src/main/io/vtx.d \
./cleanflight/src/main/io/vtx_control.d \
./cleanflight/src/main/io/vtx_rtc6705.d \
./cleanflight/src/main/io/vtx_smartaudio.d \
./cleanflight/src/main/io/vtx_string.d \
./cleanflight/src/main/io/vtx_tramp.d 


# Each subdirectory must supply rules for building sources it contributes
cleanflight/src/main/io/%.o: ../cleanflight/src/main/io/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F100x2048 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DFLASH_SIZE=2048 -D'__TARGET__="LEDUV3"' -D'__REVISION__="1.0"' -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/Core/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/USBD_VCOM" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000" -I"$(PROJECT_LOC)/cleanflight/lib/main/XMC4000/XMCLib/inc" -I"$(PROJECT_LOC)/cleanflight/src/main" -I"$(PROJECT_LOC)/cleanflight/src/main/target/LARIXEDUV3" -O0 -fpack-struct -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

