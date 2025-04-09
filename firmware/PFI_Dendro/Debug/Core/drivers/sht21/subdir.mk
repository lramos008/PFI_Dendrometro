################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/sht21/crc8.c \
../Core/drivers/sht21/sht21_driver.c 

OBJS += \
./Core/drivers/sht21/crc8.o \
./Core/drivers/sht21/sht21_driver.o 

C_DEPS += \
./Core/drivers/sht21/crc8.d \
./Core/drivers/sht21/sht21_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/sht21/%.o Core/drivers/sht21/%.su Core/drivers/sht21/%.cyclo: ../Core/drivers/sht21/%.c Core/drivers/sht21/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/rtc" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/dht22" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/sht21" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/services/environment_measure" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/services/rtc_manager" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-sht21

clean-Core-2f-drivers-2f-sht21:
	-$(RM) ./Core/drivers/sht21/crc8.cyclo ./Core/drivers/sht21/crc8.d ./Core/drivers/sht21/crc8.o ./Core/drivers/sht21/crc8.su ./Core/drivers/sht21/sht21_driver.cyclo ./Core/drivers/sht21/sht21_driver.d ./Core/drivers/sht21/sht21_driver.o ./Core/drivers/sht21/sht21_driver.su

.PHONY: clean-Core-2f-drivers-2f-sht21

