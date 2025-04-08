################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/services/environment_measure/environment_data.c 

OBJS += \
./Core/services/environment_measure/environment_data.o 

C_DEPS += \
./Core/services/environment_measure/environment_data.d 


# Each subdirectory must supply rules for building sources it contributes
Core/services/environment_measure/%.o Core/services/environment_measure/%.su Core/services/environment_measure/%.cyclo: ../Core/services/environment_measure/%.c Core/services/environment_measure/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/rtc" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/dht22" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/sht21" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/services/environment_measure" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/services/rtc_manager" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-services-2f-environment_measure

clean-Core-2f-services-2f-environment_measure:
	-$(RM) ./Core/services/environment_measure/environment_data.cyclo ./Core/services/environment_measure/environment_data.d ./Core/services/environment_measure/environment_data.o ./Core/services/environment_measure/environment_data.su

.PHONY: clean-Core-2f-services-2f-environment_measure

