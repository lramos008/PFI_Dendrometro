################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/rtc_driver.c 

OBJS += \
./Core/drivers/rtc_driver.o 

C_DEPS += \
./Core/drivers/rtc_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/%.o Core/drivers/%.su Core/drivers/%.cyclo: ../Core/drivers/%.c Core/drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/leonardo/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-drivers

clean-Core-2f-drivers:
	-$(RM) ./Core/drivers/rtc_driver.cyclo ./Core/drivers/rtc_driver.d ./Core/drivers/rtc_driver.o ./Core/drivers/rtc_driver.su

.PHONY: clean-Core-2f-drivers

