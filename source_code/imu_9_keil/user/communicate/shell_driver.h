/*
 * shell_driver.h
 *
 *  Created on: Apr 1, 2024
 *      Author: liu
 */

#ifndef SHELL_SHELL_DRIVER_H_
#define SHELL_SHELL_DRIVER_H_


#include "main.h"
#include "stdbool.h"


#define SHELL_BUFFER_SIZE       (128)
#define SHELL_MAX_ARGS          (21)

typedef int (*cmd_func_t)(void *context, int argc, char** argv);

typedef struct console_cmd_tbl
{
    char *name;	                               /**< Command name */
    cmd_func_t cmd;                            /**< Callback function */
    struct console_cmd_tbl *argv1_tbl;   /**< Next command */
}console_cmds_t;


typedef struct
{
	UART_HandleTypeDef *uart_port;   /**< Compatible for SDK 1.0.6 and before. */
	UART_HandleTypeDef * console_port; /**< Printf port selection, refer to @ref PORT_SELECT */
    console_cmds_t *tbl; /**< Usage of console cmd, refer to @ref console_cmds_t */
    char *prompt;      /**< String of Console prompt */
    char head[10];      /**< String of Console prompt */
    const int cmd_char_len;
}bsp_console_parm;


typedef struct
{

//    enum input_mode mode;

    /*! prompt string */
    char *prompt;
    /*! special key status */
//    enum fun_key_status stat;
    /* consult buffer */
    char line[SHELL_BUFFER_SIZE];
    uint16_t c_sel[SHELL_MAX_ARGS];  /* current select bar idx*/
    uint16_t c_sel_idx;              /* how many layer*/
    uint16_t root_cmd_num;           /* number of root user commands*/
    uint16_t cur_cmd_num;           /* number of user commands */
    uint16_t l_pos;                  /* total line postion */
    uint16_t c_pos;                  /* current line postion */
    int  parm_buf[10];
    int parm_len;
//    struct shell_ops_struct ops;    /* IO interface operation */
//    shell_cmd_tbl_t root_cmd_tab;   /* command tables */
//    shell_cmd_tbl_t cur_cmd_tab;    /* for cache used */
//    cmd_function_t local_input_cb;
//#if SHELL_USE_HISTORY
//    uint8_t hist_current;
//    uint8_t hist_count;
//    uint8_t hist_search;
//    char *hist_buf[SHELL_HIST_MAX];
//#endif
    bool exit;
} shell_context_struct;


void console_driver_init(bsp_console_parm *p_cnl_parm);
int shell_console_hande(uint8_t *dat,uint16_t len);





#endif /* SHELL_SHELL_DRIVER_H_ */
