#include <stdio.h>
#include <stdint.h>
#include <netinet/if_ether.h> //for ETHERTYPE_IP and others
#include <netinet/in.h> //for IPPROTO_TCP and others
//for inet_ntoa()
#include <sys/socket.h>
#include <arpa/inet.h>

struct Ethnet_header{
	unsigned char dstMac[6];
	unsigned char srcMac[6];
	uint16_t type;
};

struct Ip4_header{
	unsigned char ver_len;
	unsigned char type;
	uint16_t total_length;
	unsigned short int id;
	unsigned short int flag_frag;
	unsigned char TTL;
	unsigned char protocol;
	unsigned short int checksum;
	unsigned int src;
	unsigned int dst;
	unsigned char opt[40];
};

struct Tcp_header{
	uint16_t src_port;
	uint16_t dst_port;
	unsigned int sequence;
	unsigned int ack;
	unsigned char offset;
	unsigned char flags;
	unsigned short int window;
	unsigned short int checksum;
	unsigned short int urgp;
	unsigned char opt[40];
};

int analyze_packet( char* packet )
{
	struct Ethnet_header* eth_hp;
	struct Ip4_header* ip4_hp;
	struct Tcp_header* tcp_hp;
	char* data;
	unsigned int data_size;


	eth_hp = packet;
	
	if( ntohs(eth_hp->type) == ETHERTYPE_IP ){ //IPv4
		ip4_hp = packet + sizeof(*eth_hp);
		if( ip4_hp->protocol == IPPROTO_TCP ){
			printf("It\'s TCP\n");
			tcp_hp = packet + sizeof(*eth_hp) + ((ip4_hp->ver_len)%16)*4;

			print_eth(eth_hp);			
			print_Ip4(ip4_hp);
			print_Tcp(tcp_hp);
			
			data = packet + sizeof(*eth_hp) + ((ip4_hp->ver_len)%16)*4 + ((tcp_hp->offset)>>4)*4;
			data_size = ntohs(ip4_hp->total_length) - ((ip4_hp->ver_len)%16)*4 + ((tcp_hp->offset)>>4)*4;
			print_body(data,data_size);
		}
	}
	//printf("%x,%x,%x,%d,%x",packet,eth_hp,ip4_hp,((ip4_hp->ver_len)%16),tcp_hp);
		
	return 0;
}

int print_eth(struct Ethnet_header* eth)
{
	printf("dst MAC: ");
	printf("%02X:%02X:%02X:%02X:%02X:%02X\n",(*eth).dstMac[0],(*eth).dstMac[1],(*eth).dstMac[2],(*eth).dstMac[3],(*eth).dstMac[4],(*eth).dstMac[5]);	

	printf("src MAC: ");
	printf("%02X:%02X:%02X:%02X:%02X:%02X\n",(*eth).srcMac[0],(*eth).srcMac[1],(*eth).srcMac[2],(*eth).srcMac[3],(*eth).srcMac[4],(*eth).srcMac[5]);
	
	return 0;
}

int print_Ip4(struct Ip4_header* iph)
{
	printf("src IP: ");
	printf("%s\n", inet_ntoa( *(struct in_addr*)( &((*iph).src ))) );

	printf("dst IP: ");
	printf("%s\n", inet_ntoa( *(struct in_addr*)( &((*iph).dst ))) );

	return 0;
}

int print_Tcp(struct Tcp_header* tcph)
{
	printf("src port: %d\n", ntohs((*tcph).src_port) );
	printf("dst port: %d\n", ntohs((*tcph).dst_port) );

	return 0;
}

int print_body( unsigned char* start, uint32_t len ){
	int i;
	printf("data size(except header): %d\n",len);
	for(i=0;i<len;i++){
		printf("%02X ",(unsigned char)*(start+i));
	}
	printf("\n");
	return 0;
} 





