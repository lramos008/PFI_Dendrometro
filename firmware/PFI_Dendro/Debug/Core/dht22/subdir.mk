################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/dht22/delay_us.c \
../Core/dht22/dht22_driver.c \
../Core/dht22/environment_data.c 

OBJS += \
./Core/dht22/delay_us.o \
./Core/dht22/dht22_driver.o \
./Core/dht22/environment_data.o 

C_DEPS += \
./Core/dht22/delay_us.d \
./Core/dht22/dht22_driver.d \
./Core/dht22/environment_data.d 


# Each subdirectory must supply rules for building sources it contributes
Core/dht22/%.o Core/dht22/%.su Core/dht22/%.cyclo: ../Core/dht22/%.c Core/dht22/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/dht22" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/rtc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-dht22

clean-Core-2f-dht22:
	-$(RM) ./Core/dht22/delay_us.cyclo ./Core/dht22/delay_us.d ./Core/dht22/delay_us.o ./Core/dht22/delay_us.su ./Core/dht22/dht22_driver.cyclo ./Core/dht22/dht22_driver.d ./Core/dht22/dht22_driver.o ./Core/dht22/dht22_driver.su ./Core/dht22/environment_data.cyclo ./Core/dht22/environment_data.d ./Core/dht22/environment_data.o ./Core/dht22/environment_data.su

.PHONY: clean-Core-2f-dht22

