################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../empty.syscfg 

C_SRCS += \
./syscfg/ti_msp_dl_config.c \
D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c \
../main_freertos.c \
../ti_drivers_config.c 

GEN_CMDS += \
./syscfg/device_linker.cmd 

GEN_FILES += \
./syscfg/device_linker.cmd \
./syscfg/device.opt \
./syscfg/ti_msp_dl_config.c 

GEN_MISC_DIRS += \
./syscfg 

C_DEPS += \
./syscfg/ti_msp_dl_config.d \
./startup_mspm0g350x_ticlang.d \
./main_freertos.d \
./ti_drivers_config.d 

GEN_OPTS += \
./syscfg/device.opt 

OBJS += \
./syscfg/ti_msp_dl_config.o \
./startup_mspm0g350x_ticlang.o \
./main_freertos.o \
./ti_drivers_config.o 

GEN_MISC_FILES += \
./syscfg/device.cmd.genlibs \
./syscfg/ti_msp_dl_config.h \
./syscfg/Event.dot 

GEN_MISC_DIRS__QUOTED += \
"syscfg" 

OBJS__QUOTED += \
"syscfg\ti_msp_dl_config.o" \
"startup_mspm0g350x_ticlang.o" \
"main_freertos.o" \
"ti_drivers_config.o" 

GEN_MISC_FILES__QUOTED += \
"syscfg\device.cmd.genlibs" \
"syscfg\ti_msp_dl_config.h" \
"syscfg\Event.dot" 

C_DEPS__QUOTED += \
"syscfg\ti_msp_dl_config.d" \
"startup_mspm0g350x_ticlang.d" \
"main_freertos.d" \
"ti_drivers_config.d" 

GEN_FILES__QUOTED += \
"syscfg\device_linker.cmd" \
"syscfg\device.opt" \
"syscfg\ti_msp_dl_config.c" 

SYSCFG_SRCS__QUOTED += \
"../empty.syscfg" 

C_SRCS__QUOTED += \
"./syscfg/ti_msp_dl_config.c" \
"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c" \
"../main_freertos.c" \
"../ti_drivers_config.c" 


