#include <stdio.h>
struct Ethnet_header{
	unsigned char dstMac[6];
	unsigned char srcMac[6];
	unsigned char type[2];
};

struct Ip4_header{
	unsigned char ver_len;
	unsigned char type;
	unsigned char total_length[2];
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
	unsigned char src_port[2];
	unsigned char dst_port[2];
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
	unsigned int i;


	eth_hp = packet;
	char IPv4[]={0x08,0x00};
	if( !memcmp(eth_hp->type,IPv4,2) ){
		ip4_hp = packet+sizeof(*eth_hp);
		if( ip4_hp->protocol == 6 ){
			printf("It\'s TCP\n");
			tcp_hp = packet+sizeof(*eth_hp)+((ip4_hp->ver_len)%16)*4;

			print_eth(eth_hp);			
			print_Ip4(ip4_hp);
			print_Tcp(tcp_hp);
			
			data = packet + sizeof(*eth_hp)+((ip4_hp->ver_len)%16)*4+((tcp_hp->offset)>>4)*4;
			data_size = ip4_hp->total_length[0]*256+ip4_hp->total_length[1] - ((ip4_hp->ver_len)%16)*4+((tcp_hp->offset)>>4)*4;
			printf("data size(except header): %d\n",data_size);
			for(i=0;i<data_size;i++){
				printf("%02X ",(unsigned char)*(data+i));
			}
			printf("\n");
			
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
	printf("%d.%d.%d.%d\n",(*iph).src<<24>>24,(*iph).src<<16>>24,(*iph).src<<8>>24,(*iph).src>>24);

	printf("dst IP: ");
	printf("%d.%d.%d.%d\n",(*iph).dst<<24>>24,(*iph).dst<<16>>24,(*iph).dst<<8>>24,(*iph).dst>>24);

	return 0;
}

int print_Tcp(struct Tcp_header* tcph)
{
	printf("src port: %d\n",(*tcph).src_port[0]*256 + (*tcph).src_port[1]);
	printf("dst port: %d\n",(*tcph).dst_port[0]*256 + (*tcph).dst_port[1]);
	return 0;
}

