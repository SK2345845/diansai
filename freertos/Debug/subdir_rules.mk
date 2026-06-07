################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1313815473: ../empty.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/LeStoreDownload/CCS/sysconfig_1.26.2/sysconfig_cli.bat" --script "D:/compitation/NUEDC/diansai/freertos/empty.syscfg" -o "syscfg" -s "D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/device_linker.cmd: build-1313815473 ../empty.syscfg
syscfg/device.opt: build-1313815473
syscfg/device.cmd.genlibs: build-1313815473
syscfg/ti_msp_dl_config.c: build-1313815473
syscfg/ti_msp_dl_config.h: build-1313815473
syscfg/Event.dot: build-1313815473
syscfg: build-1313815473

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/compitation/NUEDC/diansai/freertos" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -D__MSPM0G3507__ -gdwarf-3 -Wall -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/compitation/NUEDC/diansai/freertos/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/compitation/NUEDC/diansai/freertos" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -D__MSPM0G3507__ -gdwarf-3 -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/compitation/NUEDC/diansai/freertos/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/compitation/NUEDC/diansai/freertos" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -D__MSPM0G3507__ -gdwarf-3 -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/compitation/NUEDC/diansai/freertos/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


