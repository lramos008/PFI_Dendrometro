################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/rtc/rtc_driver.c 

OBJS += \
./Core/drivers/rtc/rtc_driver.o 

C_DEPS += \
./Core/drivers/rtc/rtc_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/rtc/%.o Core/drivers/rtc/%.su Core/drivers/rtc/%.cyclo: ../Core/drivers/rtc/%.c Core/drivers/rtc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/rtc" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/sht21" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/services/rtc_manager" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/sd_card" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-rtc

clean-Core-2f-drivers-2f-rtc:
	-$(RM) ./Core/drivers/rtc/rtc_driver.cyclo ./Core/drivers/rtc/rtc_driver.d ./Core/drivers/rtc/rtc_driver.o ./Core/drivers/rtc/rtc_driver.su

.PHONY: clean-Core-2f-drivers-2f-rtc

