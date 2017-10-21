/*
 * shell_cmd_resolver.c
 *
 *  Created on: Oct 20, 2017
 *      Author: soierr
 */
#include "shell_cmd_executor.h"

void execute(struct Command * command, char ** result_desc){

	switch(command->command){

		case HELP:{

			printf("%s", COMMAND_HELP_TEXT);
			break;

		}case TRACK:{

			pcap_track(command->ip_c, result_desc);
			break;

		}case EXIT:{
			break;

		}default: break;
	}
}
