/*
 * shell_cmd_resolver.c
 *
 *  Created on: Oct 20, 2017
 *      Author: soierr
 */
#include "shell_cmd_executor.h"

static pthread_t thread;

void execute(struct Command * command, char ** result_desc){

	switch(command->command){

		case HELP:{

			printf("%s", COMMAND_HELP_TEXT);
			printf("sniffer-demo>");
			break;

		}case START:{

			printf("\n");
			pthread_create(&thread, NULL, pcap_start, (void *) command);

			/*Start workaround to avoid terminal window clearing*/
			WINDOW * w = initscr();
			cbreak();
			noecho();
			nodelay(w, 1);
			getch();
			nodelay(w, 0);
			endwin();
			/*Stop workaround to avoid terminal window clearing*/

			initscr();
			cbreak();
			noecho();
			keypad(stdscr, TRUE);

			while(getch()!= 'q'){}

			is_stop_capturing = 1;

			endwin();

			printf("sniffer-demo>");
			break;

		}case TRACK:{

			printf("\n");
			pthread_create(&thread, NULL, pcap_track, (void *) command);

			/*Start workaround to avoid terminal window clearing*/
			WINDOW * w = initscr();
			cbreak();
			noecho();
			nodelay(w, 1);
			getch();
			nodelay(w, 0);
			endwin();
			/*Stop workaround to avoid terminal window clearing*/

			initscr();
			cbreak();
			noecho();
			keypad(stdscr, TRUE);

			while(getch()!= 'q'){}

			is_stop_capturing = 1;

			endwin();

			printf("sniffer-demo>");
			break;

		}case COUNT:{

			command->count = get_count(command->ip_i_src);

			if(command->count){

				printf("\n");
				printf("IP: %s Packet count: %d \n", command->ip_c_src, command->count);
				printf("\n");

			}else{

				printf("\n");
				printf("No IP found\n");
				printf("\n");
			}

			printf("sniffer-demo>");

			break;

		}case STATS:{

			struct TreeStats * ts;

			ts = get_stats();

			struct sockaddr_in s_addr_in;
			s_addr_in.sin_addr.s_addr = ts->max_count_ip;

			printf("\n");
			printf("IP, max count: %s", inet_ntoa(s_addr_in.sin_addr));
			printf("	Max count: %d\n", ts->max_count);

			s_addr_in.sin_addr.s_addr = ts->min_count_ip;

			printf("IP, min count: %s", inet_ntoa(s_addr_in.sin_addr));
			printf("	Min count: %d\n", ts->min_count);

			printf("Total IPs: %d\n", ts->total_ip);

			printf("\n");

			printf("sniffer-demo>");
			break;

		}case EXIT:{
			break;

		}default:{
			printf("\n");
			printf("Command is not defined\n");
			printf("\n");
			printf("sniffer-demo>");
			break;
		}
	}
}
