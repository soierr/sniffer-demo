/*
 * pcap.c
 *
 *  Created on: Oct 20, 2017
 *      Author: soierr
 */
#include "pcap_api.h"

int is_stop_capturing = 0;

static pcap_t * handle;

static char * dev;

static char ip_a[IP_LENTH];

static char ip_dst[IP_LENTH];

static char * netmask_string;

static bpf_u_int32 netmask = 0;

static char result_buf[PCAP_ERRBUF_SIZE];

static void process_packet(const u_char * packet);

static void prepare_capturing(char* ip_src, char* id_dst, char* result_desc);

enum RESULT_PCAP pcap_init(char ** result_desc){

	pcap_if_t *alldevs;

	struct pcap_if * e_int;

	struct pcap_addr * dev_addr;

	struct sockaddr * dev_sockaddr;

	struct sockaddr * dev_sockaddr_netmask;

	struct sockaddr_in * dev_sockaddr_in;

	struct sockaddr_in * dev_sockaddr_in_netmask;

	char * ip_string;

	char netmask_a[IP_LENTH];

	pcap_findalldevs(&alldevs, result_buf);

	if(alldevs == NULL){

		*result_desc = "No device found: %s\n";
		return P_IFACE_NOT_FOUND;
	}

	e_int = alldevs;

	do{

		if(e_int->flags == (PCAP_IF_UP | PCAP_IF_RUNNING)){

			if(strcmp(e_int->name, "any")){

				dev_addr = e_int->addresses;

				do{

					dev_sockaddr = (struct sockaddr *) dev_addr->addr;

					dev_sockaddr_in = (struct sockaddr_in *) dev_sockaddr;

					if(dev_sockaddr_in->sin_family == AF_INET){

						ip_string = inet_ntoa(dev_sockaddr_in->sin_addr);

						strcpy(ip_dst, ip_string);

						dev_sockaddr_netmask = (struct sockaddr *) dev_addr->netmask;

						dev_sockaddr_in_netmask = (struct sockaddr_in *) dev_sockaddr_netmask;

						netmask = dev_sockaddr_in_netmask->sin_addr.s_addr;

						netmask_string = inet_ntoa(dev_sockaddr_in_netmask->sin_addr);

						strcpy(netmask_a, netmask_string);

						dev = e_int->name;
					}

				}while((dev_addr = dev_addr->next));
			}
		}

	}while((e_int = e_int->next));

	*result_desc = "   PCAP. Successful initialization";

	return P_OK;
}

void * pcap_start(){

	struct pcap_pkthdr packet_header;

	const u_char * packet;

	prepare_capturing(NULL, ip_dst, result_buf);

	while(!is_stop_capturing){

		packet = pcap_next(handle, &packet_header);

		process_packet(packet);
	}

	pcap_close(handle);

	is_stop_capturing = 0;

	pthread_exit(NULL);
}

void * pcap_track(void * command_in){

	struct Command * command = (struct Command *) command_in;

	struct pcap_pkthdr packet_header;

	const u_char * packet;

	prepare_capturing(command->ip_c_src, ip_dst, result_buf);

	while(!is_stop_capturing){

		packet = pcap_next(handle, &packet_header);

		process_packet(packet);
	}

	pcap_close(handle);

	is_stop_capturing = 0;

	pthread_exit(NULL);
}

static void prepare_capturing(char * ip_src, char * ip_dst, char* result_buf){

	int packet_count_limit = 1;

	int timeout_limit = 200;

	struct bpf_program fp;

	char filter_exp[LENGTH_PCAP_FILTER] = "tcp && (dst ";

	if(NULL != ip_src){

		char * filter_exp_part3 = " && src ";
		char * filter_exp_part4 = ")";

		strcat(filter_exp, ip_dst);

		strcat(filter_exp, filter_exp_part3);

		strcat(filter_exp, ip_src);

		strcat(filter_exp, filter_exp_part4);

	}else{

		char * filter_exp_part2 = ")";

		strcat(filter_exp, ip_dst);

		strcat(filter_exp, filter_exp_part2);
	}

	handle = pcap_open_live(dev, BUFSIZ, packet_count_limit, timeout_limit, result_buf);

	if (pcap_compile(handle, &fp, filter_exp, 0, netmask) == -1) {
		 fprintf(stderr, "Couldn't parse filter %s: %s\r\n", filter_exp, pcap_geterr(handle));
		 return;
	}

	if (pcap_setfilter(handle, &fp) == -1) {
		fprintf(stderr, "Couldn't install filter %s: %s\r\n", filter_exp, pcap_geterr(handle));
		return;
	}

}

static void process_packet(const u_char * packet){

	const struct ether_header * ethernet;

	const struct ip * ip;
	const struct tcphdr * tcp;

	u_int size_ip;
	u_int size_tcp;
	u_int size_payload;

	char * ip_string;

	ethernet = (struct ether_header*)(packet);

	if(ethernet->ether_dhost == NULL){
		return;
	}

	ip = (struct ip *)(packet + SIZE_ETHERNET);
	size_ip = ip->ip_hl;

	if (size_ip < FIVE_WORDS) {
		return;
	}

	ip_string = inet_ntoa(ip->ip_src);

	strcpy(ip_a, ip_string);

	tcp = (struct tcphdr *)(packet + SIZE_ETHERNET + (size_ip * FOUR_BYTES_ONE_WORD));
	size_tcp = tcp->th_off;

	if (size_tcp < FIVE_WORDS) {
		return;
	}

	size_payload = htons(ip->ip_len) - ((size_ip * FOUR_BYTES_ONE_WORD) + (size_tcp * FOUR_BYTES_ONE_WORD));

	if(size_payload > 0){

		printf("Get packet with data from: %s; length: %d bytes\r\n", ip_a, size_payload);
		insert_node(ip->ip_src.s_addr);
	}

}
