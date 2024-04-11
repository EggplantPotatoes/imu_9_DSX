# imu_9_DSF
  一款IMU九轴姿态传感器，基于STM32G431RBT6结合三轴加速度计，三轴陀螺仪，三轴磁力计实现的九轴数据融合，可输出欧拉角，四元数等相关数据

# 硬件介绍 

以STM32G431为主控MCU，三轴加速度计和三轴陀螺仪使用LSM6DS3TR，三轴磁力计使用LIS2MDLTR

![image](https://github.com/EggplantPotatoes/imu_9_DSF/assets/50572578/39094977-7f73-438c-897c-242705e7231c)        

使用USB_TypeC供电，引出12路IO口，其中包括3路UART，可用于二次开发

![image](https://github.com/EggplantPotatoes/imu_9_DSF/assets/50572578/ad68d0ac-a39e-4054-aff9-eaf613fa6b94)

USB输出数据，使用USB CDC（VCP）虚拟串口连接VOFA+上位机软件查看相关数据波形，无需外接U转串模块，也不需要安装驱动

![image](https://github.com/EggplantPotatoes/imu_9_DSF/assets/50572578/bcfadb9a-b447-4928-8106-482de14f5186)

![image](https://github.com/EggplantPotatoes/imu_9_DSF/assets/50572578/3149374a-db99-4ee6-ac98-71a8e6f76845)


# 软件介绍

  软件开发使用STM32CubeMX生成底层驱动，使用STM32CubeIDE开发代码
  
  两路硬件IIC分别连接六轴LSM6DS3TR和地磁LIS2MDLTR
  
  USB使用CDC虚拟出串口，与上位机vofa+通信
  
  硬件定时器TIM2定时1ms中断采集九轴数据，进行数据融合并输出数据，故数据融合算法的运行频率是1000Hz
  
  使用命令行修改配置
  
  姿态融合算法使用Fusion,该算法基于 Madgwick 博士论文第 7 章中提出的修订版 AHRS 算法，这是与第 3 章中介绍的更为人所知的初始 AHRS 算法（通常称为 Madgwick 算法）不同的算法。
  
  原始算法开源地址链接https://github.com/xioTechnologies/Fusion?tab=readme-ov-file
  
  数据融合算法坐标系使用ENU，即X轴指正北，Y指正东，Z轴指天，代码中有宏定义可以修改相关坐标系，但是要注意地磁的轴向与六轴不一致，需要手动调整
# 使用说明

  USB_Type线（手机充电线）连接电脑，电脑端会出现一个COM口，使用串口工具既可以看到相关数据输出，默认欧拉角输出，可以输出欧拉角，四元数，去掉重力之后的三轴加速度，三轴加速度原始数据，三轴陀螺仪原始数据，三轴地磁原始数据

  校准：
  
  使用之前需要校准，校准可以提高传感器精度。六轴校准，需要将板子水平放置；地磁校准需要将板子三个轴向转动。
  
  校准使用命令行，命令行格式是以 空格分割，回车换行结束命令。相关命令如下：
	
        加速度和陀螺仪校准	  cmd cali a+g 
        
          地磁校准	          cmd cali mag 

  校准一次之后零点存到G431内部Flash中，掉电保存。
 
  数据输出：
  
  数据输出可选，默认是欧拉角输出使用命令行进行切换，相关命令如下：
  
        欧拉角     cmd output euler 
      
        四元数    cmd output quaternion 
      
        除重力后加速度   cmd output earth_a 
      
        三轴加速度    cmd output acc 
      
        三轴陀螺仪    cmd output gyro 
      
        三轴地磁    cmd output mag 
      
        九轴原始数据  cmd output acc_gyro_mag 
      
 修改数据输出模式之后存到G431内部Flash中，掉电保存。

  欧拉角数据输出：
![image](https://github.com/EggplantPotatoes/imu_9_DSF/assets/50572578/28d125b1-96ab-4d65-be14-47c66dbbb821)


九轴原始数据输出：

![image](https://github.com/EggplantPotatoes/imu_9_DSF/assets/50572578/c867346f-cf3f-42a0-9d66-2fca4e2a18f2)

