/*
 * user_shell.c
 *
 *  Created on: Apr 1, 2024
 *      Author: liu
 */
#include "user_shell.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "debug.h"
#include "imu_9.h"
#include "in_flash.h"

#define user_shell_debug 0

extern UART_HandleTypeDef huart1;
#define shell_printf usb_printf

/// @brief 校准
/// @param context
/// @param argc
/// @param argv
/// @return
int cmd_cali(void *context, int argc, char **argv)
{
// 在这里执行 read 命令的逻辑
#if user_shell_debug
    shell_printf("cmd_res_read...parm-num:%d\n", argc);
#endif
    if (argc >= 1)
    {
    	if(strcmp(*argv,"a+g")==0)
    	{
    		shell_printf("cali a+g \r\n");
    		imu_9.shell_cmd_ok = 1;
    		imu_9.cali_flag = 1;

    	}
    	if(strcmp(*argv,"mag")==0)
    	{
    		shell_printf("cali mag \r\n");
    		imu_9.shell_cmd_ok = 1;
    		imu_9.cali_flag = 2;
    	}

    }
    return 0; // 返回执行结果，根据需要进行修改
}
/// @brief 复位
/// @param context
/// @param argc
/// @param argv
/// @return test ok  24.4.3 liu
int cmd_reset(void *context, int argc, char **argv)
{
// 在这里执行 read 命令的逻辑
#if user_shell_debug
    shell_printf("cmd_reset...parm-num:%d\n", argc);
#endif
    __disable_fault_irq();
    NVIC_SystemReset();



    return 0; // 返回执行结果，根据需要进行修改
}
/// @brief 读ad 值
/// @param context
/// @param argc
/// @param argv
/// @return
int cmd_output(void *context, int argc, char **argv)
{
// 在这里执行 read 命令的逻辑
#if user_shell_debug
    shell_printf("cmd_ad_read...parm-num:%d\n", argc);
#endif

    if (argc >= 1)
    {
    	if(strcmp(*argv,"euler")==0)
    	{
    		shell_printf("output euler \r\n");
    		imu_9.shell_cmd_ok = 1;
    		imu_9.output_flag = 1;
    		imu_9.output_mode = 0;
    	}
    	if(strcmp(*argv,"quaternion")==0)
    	{
    		shell_printf("output quaternion \r\n");
    		imu_9.shell_cmd_ok = 1;
    		imu_9.output_flag = 1;
    		imu_9.output_mode = 1;
    	}

    	if(strcmp(*argv,"earth_a")==0)
    	{
    		shell_printf("output earth_a \r\n");
    		imu_9.shell_cmd_ok = 1;
    		imu_9.output_flag = 1;
    		imu_9.output_mode = 2;
    	}

    	if(strcmp(*argv,"acc")==0)
    	{
    		shell_printf("output acc \r\n");
    		imu_9.shell_cmd_ok = 1;
    		imu_9.output_flag = 1;
    		imu_9.output_mode = 3;
    	}

    	if(strcmp(*argv,"gyro")==0)
    	{
    		shell_printf("output gyro \r\n");
    		imu_9.shell_cmd_ok = 1;
    		imu_9.output_flag = 1;
    		imu_9.output_mode = 4;
    	}

    	if(strcmp(*argv,"mag")==0)
    	{
    		shell_printf("output mag \r\n");
    		imu_9.shell_cmd_ok = 1;
    		imu_9.output_flag = 1;
    		imu_9.output_mode = 5;
    	}

    	if(strcmp(*argv,"acc_gyro_mag")==0)
    	{
    		shell_printf("output acc_gyro_mag \r\n");
    		imu_9.shell_cmd_ok = 1;
    		imu_9.output_flag = 1;
    		imu_9.output_mode = 6;
    	}
    }

    return 0; // 返回执行结果，根据需要进行修改
}


int cmd_version_read(void *context, int argc, char **argv)
{
// 在这里执行 read 命令的逻辑
#if user_shell_debug
    shell_printf("cmd_version_read...parm-num:%d\n", argc);
#endif
    if (argc == 1)
    {
        shell_printf("Param1: %s\n", argv[0]);
    }

    return 0; // 返回执行结果，根据需要进行修改
}

static console_cmds_t cmds[] = {
    {"cali", cmd_cali, NULL},
    {"reset", cmd_reset, NULL},
    {"output", cmd_output, NULL},


};
/*console*/
static bsp_console_parm console_parm = {
    .uart_port = &huart1,
    .tbl = (console_cmds_t *)cmds,
    .prompt = 0,
    .head = {0}};

void user_shell_init(void)
{
    char addr_str[10] = {0};

    strcpy(console_parm.head, addr_str);

    console_driver_init(&console_parm);
    for (int i = 1; i < sizeof(cmds) / (sizeof(console_cmds_t)); i++) // 链表初始化
    {
        cmds[i - 1].argv1_tbl = &cmds[i];
    }
}
int user_shell_recive_bytes(uint8_t *data, int len)
{
    int ret = 0;
    ret = shell_console_hande(data, len);

    return ret;
}

void user_shell_console_process()
{
}
