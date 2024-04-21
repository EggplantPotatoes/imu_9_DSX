################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/data_filter/data_filter.c \
../user/data_filter/kalman_filter.c 

OBJS += \
./user/data_filter/data_filter.o \
./user/data_filter/kalman_filter.o 

C_DEPS += \
./user/data_filter/data_filter.d \
./user/data_filter/kalman_filter.d 


# Each subdirectory must supply rules for building sources it contributes
user/data_filter/%.o user/data_filter/%.su user/data_filter/%.cyclo: ../user/data_filter/%.c user/data_filter/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"F:/Jundong/fish_sale/my_board/imu/source_code/IMU_9/user/acc_gry_mag" -I"F:/Jundong/fish_sale/my_board/imu/source_code/IMU_9/user/bsp" -I"F:/Jundong/fish_sale/my_board/imu/source_code/IMU_9/user/imu_algorithm" -I"F:/Jundong/fish_sale/my_board/imu/source_code/IMU_9/user/data_filter" -I"F:/Jundong/fish_sale/my_board/imu/source_code/IMU_9/user/vofa_debug" -I"F:/Jundong/fish_sale/my_board/imu/source_code/IMU_9/user/communicate" -I"F:/Jundong/fish_sale/my_board/imu/source_code/IMU_9/user/attitude_calculation" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-user-2f-data_filter

clean-user-2f-data_filter:
	-$(RM) ./user/data_filter/data_filter.cyclo ./user/data_filter/data_filter.d ./user/data_filter/data_filter.o ./user/data_filter/data_filter.su ./user/data_filter/kalman_filter.cyclo ./user/data_filter/kalman_filter.d ./user/data_filter/kalman_filter.o ./user/data_filter/kalman_filter.su

.PHONY: clean-user-2f-data_filter

