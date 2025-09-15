################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Src/user_adc.c \
../User/Src/user_can.c 

OBJS += \
./User/Src/user_adc.o \
./User/Src/user_can.o 

C_DEPS += \
./User/Src/user_adc.d \
./User/Src/user_can.d 


# Each subdirectory must supply rules for building sources it contributes
User/Src/%.o User/Src/%.su User/Src/%.cyclo: ../User/Src/%.c User/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/CubeIDE_WorkSpace/EBS_1/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Src

clean-User-2f-Src:
	-$(RM) ./User/Src/user_adc.cyclo ./User/Src/user_adc.d ./User/Src/user_adc.o ./User/Src/user_adc.su ./User/Src/user_can.cyclo ./User/Src/user_can.d ./User/Src/user_can.o ./User/Src/user_can.su

.PHONY: clean-User-2f-Src

