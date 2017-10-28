/*
 * shell_cmd_parser.c
 *
 *  Created on: Oct 20, 2017
 *      Author: soierr
 */
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include "shell_cmd_parser.h"

enum RESULT_PARSING parse(struct Command * command, char * line, char ** result_desc){

	struct sockaddr_in sa;

	char * token = NULL;

	token = strtok(line, DELIMITER);

	if(line[0] == '\n'){

		return PARSING_EMPTY;

	}else if(strcmp(token, COMMAND_START) == 0){

		command->command = START;

		return PARSING_OK;

	}else if(strcmp(token, COMMAND_TRACK) == 0){

		command->command = TRACK;

		token = strtok(NULL, DELIMITER);

		if(token == NULL){

			return PARSING_FAILED;
		}

		inet_pton(AF_INET, token, &(sa.sin_addr));

		command->ip_c_src = token;
		command->ip_i_src = sa.sin_addr.s_addr;

		return PARSING_OK;

	}else if(strcmp(token, COMMAND_COUNT) == 0){

		command->command = COUNT;

		token = strtok(NULL, DELIMITER);

		if(token == NULL){

			return PARSING_FAILED;
		}

		inet_pton(AF_INET, token, &(sa.sin_addr));

		command->ip_c_src = token;
		command->ip_i_src = sa.sin_addr.s_addr;

		return PARSING_OK;

	}else if(strcmp(token, COMMAND_HELP) == 0){

		command->command = HELP;
		return PARSING_OK;

	}else if(strcmp(token, COMMAND_STATS) == 0){

		command->command = STATS;
		return PARSING_OK;

	}else if(strcmp(token, COMMAND_EXIT) == 0){

		command->command = EXIT;
		return PARSING_OK;
	}

	return PARSING_FAILED;

}

