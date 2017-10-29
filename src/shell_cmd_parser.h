/*
 * shell_cmd_parser.h
 *
 *  Created on: Oct 20, 2017
 *      Author: soierr
 */

#ifndef SHELL_CMD_PARSER_H_
#define SHELL_CMD_PARSER_H_

#define RESULT_DESC_OK 					"OK"
#define RESULT_DESC_MISSING_ARGUMENT 	"Missing argument"

#define COMMAND_HELP 		"help"
#define COMMAND_START 		"start"
#define COMMAND_TRACK 		"track"
#define COMMAND_COUNT 		"count"
#define COMMAND_STATS 		"stats"
#define COMMAND_EXIT 		"exit"

#define COMMAND_HELP_TEXT "\nCommand List: \n\n" \
						  " \thelp  	 	- information about the commands\n" \
						  " \tstart 	 	- starts sniffing packets. Press \"q\" for stopping\n" \
						  " \tcount arg1 	- reveals captured packets for a proper ip placed as an arg1."\
						  " Example: count 192.168.1.1\n" \
						  " \tstats 	 	- reveals statistics as to the sniffed packets\n" \
						  " \ttrack arg1 	- tracks a proper ip as a source of incoming packets." \
						  " See \"count\" for usage example. Press \"q\" for stopping\n\n" \


#define INFO_INTRO "\nThis is SNIFFER-DEMO application for tcp packets capturing\n" \
				   "For all commands list type \"help\" \n\n"


#define DELIMITER " \n"

enum RESULT_PARSING{

	PARSING_OK,
	PARSING_EMPTY,
	PARSING_FAILED

};

enum COMMAND{

	NOT_SET_CMD,
	HELP,
	START,
	TRACK,
	COUNT,
	STATS,
	EXIT

};

enum RESULT_COMMAND_LAUNCH{

	START_OK,
	START_FAILED
};

struct Command{

	enum RESULT_COMMAND_LAUNCH result_launch;
	enum COMMAND command;
	char * ip_c_dst;
	int ip_i_dst;
	char * ip_c_src;
	int ip_i_src;
	char * result_desc;
	unsigned int count;
};

enum RESULT_PARSING parse(struct Command * command, char * line, char ** result_desc);

#endif /* SHELL_CMD_PARSER_H_ */
