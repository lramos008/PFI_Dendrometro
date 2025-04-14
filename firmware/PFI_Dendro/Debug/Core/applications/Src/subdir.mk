################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/applications/Src/date_and_time.c \
../Core/applications/Src/fs_interface.c \
../Core/applications/Src/rtc_manager.c 

OBJS += \
./Core/applications/Src/date_and_time.o \
./Core/applications/Src/fs_interface.o \
./Core/applications/Src/rtc_manager.o 

C_DEPS += \
./Core/applications/Src/date_and_time.d \
./Core/applications/Src/fs_interface.d \
./Core/applications/Src/rtc_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/applications/Src/%.o Core/applications/Src/%.su Core/applications/Src/%.cyclo: ../Core/applications/Src/%.c Core/applications/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Middleware/fatfs" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/applications/Inc" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-applications-2f-Src

clean-Core-2f-applications-2f-Src:
	-$(RM) ./Core/applications/Src/date_and_time.cyclo ./Core/applications/Src/date_and_time.d ./Core/applications/Src/date_and_time.o ./Core/applications/Src/date_and_time.su ./Core/applications/Src/fs_interface.cyclo ./Core/applications/Src/fs_interface.d ./Core/applications/Src/fs_interface.o ./Core/applications/Src/fs_interface.su ./Core/applications/Src/rtc_manager.cyclo ./Core/applications/Src/rtc_manager.d ./Core/applications/Src/rtc_manager.o ./Core/applications/Src/rtc_manager.su

.PHONY: clean-Core-2f-applications-2f-Src

