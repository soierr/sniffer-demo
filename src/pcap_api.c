/*
 * pcap.c
 *
 *  Created on: Oct 20, 2017
 *      Author: soierr
 */
#include "pcap_api.h"

static pcap_t * handle;

static char * dev;

static char ip_a[IP_LENTH];

static char * netmask_string;

static bpf_u_int32 netmask = 0;

static void print_packet(const u_char * packet);

enum PCAP_RESULT pcap_init(char ** result_desc){

	static struct Device * device;

	static struct Device * device_prev;

	pcap_if_t *alldevs;

	struct pcap_if * e_int;

	char errbuf[PCAP_ERRBUF_SIZE];

	struct pcap_addr * dev_addr;

	struct sockaddr * dev_sockaddr;

	struct sockaddr * dev_sockaddr_netmask;

	struct sockaddr_in * dev_sockaddr_in;

	struct sockaddr_in * dev_sockaddr_in_netmask;

	char * ip_string;

	char netmask_a[IP_LENTH];

	pcap_findalldevs(&alldevs, errbuf);

// ===============



// ===============

	if(alldevs == NULL){

		*result_desc = "No device found: %s\n";
		return P_IFACE_NOT_FOUND;
	}

	e_int = alldevs;

	do{

/*		printf("Name: %s\n", e_int->name);
		printf("Flag: %d\n", e_int->flags);*/

		if(e_int->flags == (PCAP_IF_UP | PCAP_IF_RUNNING)){

			if(strcmp(e_int->name, "any")){

				dev_addr = e_int->addresses;

				do{

					dev_sockaddr = (struct sockaddr *) dev_addr->addr;

					dev_sockaddr_in = (struct sockaddr_in *) dev_sockaddr;

					if(dev_sockaddr_in->sin_family == AF_INET){

						device = malloc(sizeof(struct Device));

						device->next = (device_prev == NULL) ? device_prev : NULL;

						ip_string = inet_ntoa(dev_sockaddr_in->sin_addr);

						device->ip = ip_string;

						device->name = e_int->name;

						strcpy(ip_a, ip_string);

						printf("IP %s\n: ", ip_string);

						dev_sockaddr_netmask = (struct sockaddr *) dev_addr->netmask;

						dev_sockaddr_in_netmask = (struct sockaddr_in *) dev_sockaddr_netmask;

						netmask = dev_sockaddr_in_netmask->sin_addr.s_addr;

						netmask_string = inet_ntoa(dev_sockaddr_in_netmask->sin_addr);

						strcpy(netmask_a, netmask_string);

						device_prev = device;
					}

				}while((dev_addr = dev_addr->next));

			}
		}

	}while((e_int = e_int->next));

	*result_desc = "Successfully initialized";

	return P_OK;
}

enum PCAP_RESULT pcap_track(char * ip, char ** result_desc){

	int packet_count_limit = 1000000;

	int timeout_limit = 5000;

	char filter_exp[LENGTH_PCAP_FILTER] = "tcp && (dst ";	/* The filter expression */
	char * filter_exp_part3 = " && (src ";
	char * filter_exp_part4 = " )";

	struct bpf_program fp;

	struct pcap_pkthdr packet_header;

	const u_char * packet;

	strcat(filter_exp, ip_a);

	strcat(filter_exp, ")");

	strcat(filter_exp, filter_exp_part3);

	strcat(filter_exp, ip);

	strcat(filter_exp, filter_exp_part4);

	handle = pcap_open_live(dev, BUFSIZ, packet_count_limit, timeout_limit, *result_desc);

	if (pcap_compile(handle, &fp, filter_exp, 0, netmask) == -1) {
			 fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
			 return(2);
	}

	if (pcap_setfilter(handle, &fp) == -1) {
				fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
				return(2);
	}

	while(1){

		packet = pcap_next(handle, &packet_header);

		print_packet(packet);
	}

	return P_OK;
}

static void print_packet(const u_char * packet){

	const struct sniff_ethernet * ethernet;
	const struct sniff_ip * ip;
	const struct sniff_tcp * tcp;
	const u_char * payload;

	u_int size_ip;
	u_int size_tcp;

	ethernet = (struct sniff_ethernet*)(packet);

	if(ethernet->ether_dhost == NULL){

		return;
	}

	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;

	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}

	tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
	size_tcp = TH_OFF(tcp)*4;

	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return;
	}

	payload = (u_char *) (packet + SIZE_ETHERNET + size_ip + size_tcp);

	printf("Payload: %s\n", payload);


}

