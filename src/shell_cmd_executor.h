/*
 * shell_cmd_resolver.h
 *
 *  Created on: Oct 20, 2017
 *      Author: soierr
 */

#ifndef SHELL_CMD_EXECUTOR_H_
#define SHELL_CMD_EXECUTOR_H_

#include <stdio.h>

#include <arpa/inet.h>

#include <pthread.h>

#include <curses.h>

#include "shell_cmd_parser.h"

#include "pcap_api.h"

#include "tree_init.h"

#include "tree_manipulate.h"

extern int is_stop_capturing;

void execute(struct Command * command, char ** result_desc);

#endif /* SHELL_CMD_EXECUTOR_H_ */
