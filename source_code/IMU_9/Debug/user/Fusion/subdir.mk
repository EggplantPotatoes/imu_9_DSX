################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/Fusion/FusionAhrs.c \
../user/Fusion/FusionCompass.c \
../user/Fusion/FusionOffset.c 

OBJS += \
./user/Fusion/FusionAhrs.o \
./user/Fusion/FusionCompass.o \
./user/Fusion/FusionOffset.o 

C_DEPS += \
./user/Fusion/FusionAhrs.d \
./user/Fusion/FusionCompass.d \
./user/Fusion/FusionOffset.d 


# Each subdirectory must supply rules for building sources it contributes
user/Fusion/%.o user/Fusion/%.su user/Fusion/%.cyclo: ../user/Fusion/%.c user/Fusion/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/acc_gry_mag" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/bsp" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/imu_algorithm" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/data_filter" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/vofa_debug" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/Fusion" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/communicate" -I"E:/my_storage_home/develop_case/my_products/IMU_9/user/attitude_calculation" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-user-2f-Fusion

clean-user-2f-Fusion:
	-$(RM) ./user/Fusion/FusionAhrs.cyclo ./user/Fusion/FusionAhrs.d ./user/Fusion/FusionAhrs.o ./user/Fusion/FusionAhrs.su ./user/Fusion/FusionCompass.cyclo ./user/Fusion/FusionCompass.d ./user/Fusion/FusionCompass.o ./user/Fusion/FusionCompass.su ./user/Fusion/FusionOffset.cyclo ./user/Fusion/FusionOffset.d ./user/Fusion/FusionOffset.o ./user/Fusion/FusionOffset.su

.PHONY: clean-user-2f-Fusion

