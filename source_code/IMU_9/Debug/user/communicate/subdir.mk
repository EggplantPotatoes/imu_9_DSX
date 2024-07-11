################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/communicate/shell_driver.c \
../user/communicate/user_shell.c 

OBJS += \
./user/communicate/shell_driver.o \
./user/communicate/user_shell.o 

C_DEPS += \
./user/communicate/shell_driver.d \
./user/communicate/user_shell.d 


# Each subdirectory must supply rules for building sources it contributes
user/communicate/%.o user/communicate/%.su user/communicate/%.cyclo: ../user/communicate/%.c user/communicate/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"E:/my_storage_home/develop_case/IMU/IMU_9/user/acc_gry_mag" -I"E:/my_storage_home/develop_case/IMU/IMU_9/user/bsp" -I"E:/my_storage_home/develop_case/IMU/IMU_9/user/imu_algorithm" -I"E:/my_storage_home/develop_case/IMU/IMU_9/user/data_filter" -I"E:/my_storage_home/develop_case/IMU/IMU_9/user/vofa_debug" -I"E:/my_storage_home/develop_case/IMU/IMU_9/user/communicate" -I"E:/my_storage_home/develop_case/IMU/IMU_9/user/attitude_calculation" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-user-2f-communicate

clean-user-2f-communicate:
	-$(RM) ./user/communicate/shell_driver.cyclo ./user/communicate/shell_driver.d ./user/communicate/shell_driver.o ./user/communicate/shell_driver.su ./user/communicate/user_shell.cyclo ./user/communicate/user_shell.d ./user/communicate/user_shell.o ./user/communicate/user_shell.su

.PHONY: clean-user-2f-communicate

