/*
 * user_shell.h
 *
 *  Created on: Apr 1, 2024
 *      Author: liu
 */

#ifndef SHELL_USER_SHELL_H_
#define SHELL_USER_SHELL_H_



#include "shell_driver.h"


void user_shell_init(void);
int user_shell_recive_bytes(uint8_t *data,int len);

#endif /* SHELL_USER_SHELL_H_ */
