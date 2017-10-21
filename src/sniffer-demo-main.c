/*
 ============================================================================
 Name        : sniffer-demo.c
 Author      : soierr
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include "shell_cmd_parser.h"
#include "shell_cmd_executor.h"

#include "pcap_api.h"

int main(void) {

	size_t size = 0;
	char * line = NULL;

	enum PARSING_RESULT result;
	struct Command command;
	char * result_desc = NULL;

	if(pcap_init(&result_desc) != P_OK){

		printf("%s\n", result_desc);
		return -1;

	}else{
		printf("%s\n", result_desc);
	}

	do{

		printf("sniffer-demo>");
		getline(&line, &size, stdin);
		result = parse(&command, line, result_desc);

		if(result == PARSING_EMPTY){
			continue;
		}

		execute(&command, result_desc);

	}while(command.command != EXIT);


	return EXIT_SUCCESS;
}

