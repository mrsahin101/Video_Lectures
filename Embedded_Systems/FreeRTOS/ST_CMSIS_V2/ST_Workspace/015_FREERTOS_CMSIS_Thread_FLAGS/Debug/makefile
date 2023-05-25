################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 015_FREERTOS_CMSIS_Thread_FLAGS
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
015_FREERTOS_CMSIS_Thread_FLAGS.elf \

MAP_FILES += \
015_FREERTOS_CMSIS_Thread_FLAGS.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
015_FREERTOS_CMSIS_Thread_FLAGS.list \


# All Target
all: main-build

# Main-build Target
main-build: 015_FREERTOS_CMSIS_Thread_FLAGS.elf secondary-outputs

# Tool invocations
015_FREERTOS_CMSIS_Thread_FLAGS.elf 015_FREERTOS_CMSIS_Thread_FLAGS.map: $(OBJS) $(USER_OBJS) C:\Users\mehmet.sahin\Desktop\Video_Lectures\Embedded_Systems\FreeRTOS\ST_CMSIS_V2\ST_Workspace\015_FREERTOS_CMSIS_Thread_FLAGS\STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "015_FREERTOS_CMSIS_Thread_FLAGS.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\mehmet.sahin\Desktop\Video_Lectures\Embedded_Systems\FreeRTOS\ST_CMSIS_V2\ST_Workspace\015_FREERTOS_CMSIS_Thread_FLAGS\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="015_FREERTOS_CMSIS_Thread_FLAGS.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

015_FREERTOS_CMSIS_Thread_FLAGS.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "015_FREERTOS_CMSIS_Thread_FLAGS.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 015_FREERTOS_CMSIS_Thread_FLAGS.elf 015_FREERTOS_CMSIS_Thread_FLAGS.list 015_FREERTOS_CMSIS_Thread_FLAGS.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
