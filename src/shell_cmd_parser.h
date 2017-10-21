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

#define COMMAND_HELP 	"help"
#define COMMAND_TRACK 	"track"
#define COMMAND_EXIT 	"exit"

#define COMMAND_HELP_TEXT "\nCommand List: \n\n" \
						  " \thelp  	 	- information about the commands\n" \
						  " \tstart 	 	- starts sniffing packets\n" \
						  " \tstop  	 	- stops sniffing packets\n" \
						  " \tcount arg1 	- reveals captured packets for a proper ip placed as an arg1."\
						  " Example: count 192.168.1.1\n" \
						  " \tstats 	 	- reveals statistics as to the sniffed packets\n" \
						  " \ttrack arg1 	- tracks a proper ip as a source of incoming packets." \
						  " See \"count\" for usage example\n\n" \

#define DELIMITER " \n"

enum PARSING_RESULT{

	PARSING_OK,
	PARSING_EMPTY,
	PARSING_FAILED

};

enum COMMAND{

	HELP,
	START,
	STOP,
	TRACK,
	STATUS,
	COUNT,
	STATS,
	EXIT

};

struct Command{

	enum COMMAND command;
	char * ip_c;
	int ip_i;
};

enum PARSING_RESULT parse(struct Command * command, char * line, char ** result_desc);

#endif /* SHELL_CMD_PARSER_H_ */
