################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/Src/crc8.c \
../Core/drivers/Src/fatfs_sd.c \
../Core/drivers/Src/fifo.c \
../Core/drivers/Src/hm10_driver.c \
../Core/drivers/Src/rtc_driver.c \
../Core/drivers/Src/sht21_driver.c 

OBJS += \
./Core/drivers/Src/crc8.o \
./Core/drivers/Src/fatfs_sd.o \
./Core/drivers/Src/fifo.o \
./Core/drivers/Src/hm10_driver.o \
./Core/drivers/Src/rtc_driver.o \
./Core/drivers/Src/sht21_driver.o 

C_DEPS += \
./Core/drivers/Src/crc8.d \
./Core/drivers/Src/fatfs_sd.d \
./Core/drivers/Src/fifo.d \
./Core/drivers/Src/hm10_driver.d \
./Core/drivers/Src/rtc_driver.d \
./Core/drivers/Src/sht21_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/Src/%.o Core/drivers/Src/%.su Core/drivers/Src/%.cyclo: ../Core/drivers/Src/%.c Core/drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Middleware/fatfs" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/applications/Inc" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-Src

clean-Core-2f-drivers-2f-Src:
	-$(RM) ./Core/drivers/Src/crc8.cyclo ./Core/drivers/Src/crc8.d ./Core/drivers/Src/crc8.o ./Core/drivers/Src/crc8.su ./Core/drivers/Src/fatfs_sd.cyclo ./Core/drivers/Src/fatfs_sd.d ./Core/drivers/Src/fatfs_sd.o ./Core/drivers/Src/fatfs_sd.su ./Core/drivers/Src/fifo.cyclo ./Core/drivers/Src/fifo.d ./Core/drivers/Src/fifo.o ./Core/drivers/Src/fifo.su ./Core/drivers/Src/hm10_driver.cyclo ./Core/drivers/Src/hm10_driver.d ./Core/drivers/Src/hm10_driver.o ./Core/drivers/Src/hm10_driver.su ./Core/drivers/Src/rtc_driver.cyclo ./Core/drivers/Src/rtc_driver.d ./Core/drivers/Src/rtc_driver.o ./Core/drivers/Src/rtc_driver.su ./Core/drivers/Src/sht21_driver.cyclo ./Core/drivers/Src/sht21_driver.d ./Core/drivers/Src/sht21_driver.o ./Core/drivers/Src/sht21_driver.su

.PHONY: clean-Core-2f-drivers-2f-Src

