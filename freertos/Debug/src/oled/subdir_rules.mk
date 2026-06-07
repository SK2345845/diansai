################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/oled/%.o: ../src/oled/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/compitation/NUEDC/diansai_rtos/freertos" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/compitation/NUEDC/diansai_rtos/freertos_builds_LP_MSPM0G3507_release_ticlang" -D__MSPM0G3507__ -gdwarf-3 -Wall -MMD -MP -MF"src/oled/$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/compitation/NUEDC/diansai_rtos/freertos/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


