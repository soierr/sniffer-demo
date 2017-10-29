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

#include "tree_init.h"
#include "tree_save.h"

#define DEFAULT_TREE_ROOT "127.0.0.1"
#define DEFAULT_TREE_ROOT_INT 16777343

int main(void) {

	size_t size = 0;
	char * line = NULL;

	struct Command command;

	char * result_desc = NULL;

	struct sockaddr_in sockaddr_in_s;

	enum RESULT_PCAP res_pcap;
	enum RESULT_TREE res_tree;
	enum RESULT_PARSING res_parsing;

	printf(INFO_INTRO);
	printf("Initialization section start\n");

	res_pcap = pcap_init(&result_desc);

	switch(res_pcap){

		case P_OK: {
			printf("%s\n", result_desc);
			break;

		}case P_IFACE_NOT_FOUND:{
			printf("%s\n", result_desc);
			return -1;

		}default: {
			printf("%s\n", result_desc);
			return -1;
		}
	}

	inet_pton(AF_INET, DEFAULT_TREE_ROOT, &(sockaddr_in_s.sin_addr));

	res_tree = tree_init(sockaddr_in_s.sin_addr.s_addr, &result_desc);

	switch(res_tree){

		case T_OK:{
			printf("%s\n", result_desc);
			break;

		}case T_FAILED:{
			printf("%s\n", result_desc);
			return -1;

		}default:{
			break;
		}
	}

	printf("Initialization section stop\n\n");
	printf("sniffer-demo>");

	do{

		getline(&line, &size, stdin);

		command.command = NOT_SET_CMD;

		res_parsing = parse(&command, line, &result_desc);

		if(res_parsing == PARSING_EMPTY){
			printf("sniffer-demo>");
			continue;
		}else if(res_parsing == PARSING_FAILED){

			printf("\nCommand parsing failed\n\n");
			printf("sniffer-demo>");
			continue;
		}

		execute(&command, &result_desc);


	}while(command.command != EXIT);

	if(tree_save(&result_desc)!= T_OK){
		printf("\n%s\n", result_desc);
	}

	return EXIT_SUCCESS;
}

