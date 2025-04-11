################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/services/rtc_manager/date_and_time.c \
../Core/services/rtc_manager/rtc_manager.c 

OBJS += \
./Core/services/rtc_manager/date_and_time.o \
./Core/services/rtc_manager/rtc_manager.o 

C_DEPS += \
./Core/services/rtc_manager/date_and_time.d \
./Core/services/rtc_manager/rtc_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/services/rtc_manager/%.o Core/services/rtc_manager/%.su Core/services/rtc_manager/%.cyclo: ../Core/services/rtc_manager/%.c Core/services/rtc_manager/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/rtc" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/sht21" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/services/rtc_manager" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/sd_card" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-services-2f-rtc_manager

clean-Core-2f-services-2f-rtc_manager:
	-$(RM) ./Core/services/rtc_manager/date_and_time.cyclo ./Core/services/rtc_manager/date_and_time.d ./Core/services/rtc_manager/date_and_time.o ./Core/services/rtc_manager/date_and_time.su ./Core/services/rtc_manager/rtc_manager.cyclo ./Core/services/rtc_manager/rtc_manager.d ./Core/services/rtc_manager/rtc_manager.o ./Core/services/rtc_manager/rtc_manager.su

.PHONY: clean-Core-2f-services-2f-rtc_manager

