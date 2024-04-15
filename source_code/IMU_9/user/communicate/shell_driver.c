/*
 * shell_driver.c
 *
 *  Created on: Apr 1, 2024
 *      Author: liu
 */

#include "shell_driver.h"
#include "string.h"
#include "stdio.h"

#define shell_debug  0

static bsp_console_parm *shell_con=0;
 shell_context_struct shell_context={0};

 static void parseCommand(shell_context_struct *context, const char* command) {
     char commandCopy[SHELL_BUFFER_SIZE+1];  // 复制命令，以便进行修改
     char *cmd_ptr;
     char* argv[10] = {};
	 char* param=NULL;
	 int valid_cmd=0;
	 char* cmd_head;
	 const char *header="cmd";

     strcpy(commandCopy, command);
     console_cmds_t *cmds=NULL;

     if(shell_con==0)
         {
        	 return ;
         }

     cmd_head = strtok(commandCopy, " ");  // 使用空格和换行符分割命令
     if((strcmp(shell_con->head,cmd_head)!=0)&&(strcmp(cmd_head,header)!=0))//
     {
#if shell_debug
    	 usb_printf("parseAddrCommand err: %s\n", cmd_head);
#endif
				 return;
     }

     char* cmd = strtok(NULL, " \r\n");  // 使用空格和换行符分割命令
     if(strstr(cmd,"\r\n"))
     {

     }

     cmds=shell_con->tbl;
     if (cmd != NULL) {
    	 while(cmds!=NULL)
    	 {
    		 cmd_ptr=cmds->name;
			 if (strcmp(cmd, cmd_ptr) == 0)
			 {
#if shell_debug
				 usb_printf("parseCommand cmd: %s\n", cmd);
#endif
				 valid_cmd=1;
				 int param_len=0;
				 param = strtok(NULL, " ");
				 while((param!=NULL)&&(param_len<9))
				 {
#if shell_debug
					 usb_printf("Param: %s\r\n", param);
#endif
					 argv[param_len]=param;
					 param_len++;
					 if(param_len>=10)
					 {
						 return;
					 }
					 param = strtok(NULL, " ");
				 }

				 cmds->cmd(context,param_len,argv);

			 }
			 cmds=cmds->argv1_tbl;
    	 }

     }
     if(valid_cmd==0)
     {
    	 usb_printf("Invalid command....\r\n");
     }



 }

static int shell_driver_main_loop(uint8_t ch)
{

   shell_context.line[shell_context.c_pos++]=ch;
   if(shell_context.c_pos>=SHELL_BUFFER_SIZE)
   {
	   shell_context.c_pos=0;
	   usb_printf("shell_driver_main_loop pos err \r\n");
   }

   if(ch=='\n')//检测到换行符，增加\0
   {
	   shell_context.line[shell_context.c_pos]='\0';
	   parseCommand(&shell_context, shell_context.line);
	   shell_context.c_pos=0;//解析完清0

   }

	return 0;
}


int shell_console_hande(uint8_t *dat,uint16_t len)
{
	while(len--)
	{
		shell_driver_main_loop(*dat++);
	}

	return 0;

}



void console_driver_init(bsp_console_parm *p_cnl_parm)
{
  if(p_cnl_parm==0)
  {
	  usb_printf("console_driver_init prr is null \r\n");
	  return;
  }
  shell_con=p_cnl_parm;
  shell_context.c_pos=0;


}








