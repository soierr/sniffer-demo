/*
 * shell_cmd_resolver.h
 *
 *  Created on: Oct 20, 2017
 *      Author: soierr
 */

#ifndef SHELL_CMD_EXECUTOR_H_
#define SHELL_CMD_EXECUTOR_H_

#include <stdio.h>
#include "shell_cmd_parser.h"

#include "pcap_api.h"

void execute(struct Command * command, char ** result_desc);

#endif /* SHELL_CMD_EXECUTOR_H_ */
