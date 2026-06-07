################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
freertos/croutine.o: D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/croutine.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/include" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"freertos/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

freertos/event_groups.o: D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/event_groups.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/include" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"freertos/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

freertos/heap_4.o: D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/MemMang/heap_4.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/include" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"freertos/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

freertos/list.o: D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/list.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/include" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"freertos/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

freertos/queue.o: D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/queue.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/include" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"freertos/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

freertos/stream_buffer.o: D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/stream_buffer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/include" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"freertos/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

freertos/tasks.o: D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/tasks.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/include" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"freertos/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

freertos/timers.o: D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/timers.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -I"D:/compitation/NUEDC/diansai/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source/ti/posix/ticlang" -I"D:/LeStoreDownload/CCS/mspm0_sdk_2_10_00_04/source" -I"D:/LeStoreDownload/CCS/ti_cgt_arm_llvm_4.0.2.LTS/include" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"freertos/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


