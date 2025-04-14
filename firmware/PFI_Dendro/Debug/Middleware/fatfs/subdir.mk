################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/fatfs/diskio.c \
../Middleware/fatfs/ff.c \
../Middleware/fatfs/ffunicode.c 

OBJS += \
./Middleware/fatfs/diskio.o \
./Middleware/fatfs/ff.o \
./Middleware/fatfs/ffunicode.o 

C_DEPS += \
./Middleware/fatfs/diskio.d \
./Middleware/fatfs/ff.d \
./Middleware/fatfs/ffunicode.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/fatfs/%.o Middleware/fatfs/%.su Middleware/fatfs/%.cyclo: ../Middleware/fatfs/%.c Middleware/fatfs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Middleware/fatfs" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/applications/Inc" -I"C:/Users/dramos/Documents/PFI_Dendrometro/firmware/PFI_Dendro/Core/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middleware-2f-fatfs

clean-Middleware-2f-fatfs:
	-$(RM) ./Middleware/fatfs/diskio.cyclo ./Middleware/fatfs/diskio.d ./Middleware/fatfs/diskio.o ./Middleware/fatfs/diskio.su ./Middleware/fatfs/ff.cyclo ./Middleware/fatfs/ff.d ./Middleware/fatfs/ff.o ./Middleware/fatfs/ff.su ./Middleware/fatfs/ffunicode.cyclo ./Middleware/fatfs/ffunicode.d ./Middleware/fatfs/ffunicode.o ./Middleware/fatfs/ffunicode.su

.PHONY: clean-Middleware-2f-fatfs

