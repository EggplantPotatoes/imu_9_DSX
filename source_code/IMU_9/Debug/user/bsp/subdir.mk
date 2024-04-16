################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/bsp/IIC_bus.c \
../user/bsp/crc8_table.c \
../user/bsp/in_flash.c 

OBJS += \
./user/bsp/IIC_bus.o \
./user/bsp/crc8_table.o \
./user/bsp/in_flash.o 

C_DEPS += \
./user/bsp/IIC_bus.d \
./user/bsp/crc8_table.d \
./user/bsp/in_flash.d 


# Each subdirectory must supply rules for building sources it contributes
user/bsp/%.o user/bsp/%.su user/bsp/%.cyclo: ../user/bsp/%.c user/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/acc_gry_mag" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/bsp" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/imu_algorithm" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/data_filter" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/vofa_debug" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/communicate" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/attitude_calculation" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-user-2f-bsp

clean-user-2f-bsp:
	-$(RM) ./user/bsp/IIC_bus.cyclo ./user/bsp/IIC_bus.d ./user/bsp/IIC_bus.o ./user/bsp/IIC_bus.su ./user/bsp/crc8_table.cyclo ./user/bsp/crc8_table.d ./user/bsp/crc8_table.o ./user/bsp/crc8_table.su ./user/bsp/in_flash.cyclo ./user/bsp/in_flash.d ./user/bsp/in_flash.o ./user/bsp/in_flash.su

.PHONY: clean-user-2f-bsp
