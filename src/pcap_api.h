/*
 * pcap.h
 *
 *  Created on: Oct 20, 2017
 *      Author: soierr
 */

#ifndef PCAP_API_H_
#define PCAP_API_H_

#include <stdlib.h>
#include <string.h>

#include <pcap.h>
#include <pcap/pcap.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include "shell_cmd_executor.h"

#include "tree_manipulate.h"

#define IP_LENTH			16
#define LENGTH_PCAP_FILTER	128

#define SIZE_ETHERNET 		14
#define SIZE_BEFORE_IP_SRC	12

enum RESULT_PCAP{

	P_OK,
	P_IFACE_NOT_FOUND

};

struct Device{

	char * name;
	char * ip;
	struct Device * next;
};

enum RESULT_PCAP pcap_init(char ** result_desc);

void * pcap_track(void * command_in);

void * pcap_start();

#endif /* PCAP_API_H_ */
