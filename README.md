# imu_9_DSF
基于STM32G431结合三轴加速度计，三轴陀螺仪，三轴磁力计实现的九轴数据融合，可输出欧拉角，四元数等相关数据

# 硬件平台介绍 

# 算法说明

以STM32G431为主控MCU，三轴加速度计和三轴陀螺仪使用LSM6DS3TR，三轴磁力计使用LIS2MDLTR，姿态融合算法使用Fusion,该算法基于 Madgwick 博士论文第 7 章中提出的修订版 AHRS 算法，这是与第 3 章中介绍的更为人所知的初始 AHRS 算法（通常称为 Madgwick 算法）不同的算法。

原始算法开源地址链接https://github.com/xioTechnologies/Fusion?tab=readme-ov-file

# 使用说明

