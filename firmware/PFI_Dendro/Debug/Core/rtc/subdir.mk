################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/rtc/date_and_time.c \
../Core/rtc/rtc_driver.c \
../Core/rtc/rtc_manager.c 

OBJS += \
./Core/rtc/date_and_time.o \
./Core/rtc/rtc_driver.o \
./Core/rtc/rtc_manager.o 

C_DEPS += \
./Core/rtc/date_and_time.d \
./Core/rtc/rtc_driver.d \
./Core/rtc/rtc_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/rtc/%.o Core/rtc/%.su Core/rtc/%.cyclo: ../Core/rtc/%.c Core/rtc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/dht22" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/rtc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-rtc

clean-Core-2f-rtc:
	-$(RM) ./Core/rtc/date_and_time.cyclo ./Core/rtc/date_and_time.d ./Core/rtc/date_and_time.o ./Core/rtc/date_and_time.su ./Core/rtc/rtc_driver.cyclo ./Core/rtc/rtc_driver.d ./Core/rtc/rtc_driver.o ./Core/rtc/rtc_driver.su ./Core/rtc/rtc_manager.cyclo ./Core/rtc/rtc_manager.d ./Core/rtc/rtc_manager.o ./Core/rtc/rtc_manager.su

.PHONY: clean-Core-2f-rtc

