################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/sd_card/fatfs_sd.c 

OBJS += \
./Core/drivers/sd_card/fatfs_sd.o 

C_DEPS += \
./Core/drivers/sd_card/fatfs_sd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/sd_card/%.o Core/drivers/sd_card/%.su Core/drivers/sd_card/%.cyclo: ../Core/drivers/sd_card/%.c Core/drivers/sd_card/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/rtc" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/sht21" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/services/rtc_manager" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/sd_card" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/services/file_handling" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Middleware/fatfs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-sd_card

clean-Core-2f-drivers-2f-sd_card:
	-$(RM) ./Core/drivers/sd_card/fatfs_sd.cyclo ./Core/drivers/sd_card/fatfs_sd.d ./Core/drivers/sd_card/fatfs_sd.o ./Core/drivers/sd_card/fatfs_sd.su

.PHONY: clean-Core-2f-drivers-2f-sd_card

