#include <stdio.h>
struct Ethnet_header{
	unsigned char dstMac[6];
	unsigned char srcMac[6];
	unsigned char type[2];
};

struct Ip4_header{
	unsigned char ver_len;
	unsigned char type;
	unsigned short int total_length;
	unsigned short int id;
	unsigned short int flag_frag;
	unsigned char TTL;
	unsigned char protocol;
	unsigned short int checksum;
	unsigned int src;
	unsigned int dst;
	unsigned char opt[40];
	//+options
};

struct Tcp_header{
	unsigned short int src_port;
	unsigned short int dst_port;
	unsigned int sequence;
	unsigned int ack;
	unsigned char offset;
	unsigned char flags;
	unsigned short int window;
	unsigned short int checksum;
	unsigned short int urgp;
	//+options
};

int analyze_packet( char* packet )
{
	struct Ethnet_header* eth_hp;
	struct Ip4_header* ip4_hp;
	struct Tcp_header* tcp_hp;	

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
		}
		
	}
	//printf("%x,%x,%x,%d,%x",packet,eth_hp,ip4_hp,((ip4_hp->ver_len)%16),tcp_hp);
		
	return 0;
}

int print_eth(struct Ethnet_header* eth)
{
	struct Ethnet_header eth_;
	memcpy(&eth_,eth,sizeof(eth_));

	printf("dst MAC: ");
	printf("%02X:%02X:%02X:%02X:%02X:%02X\n",eth_.dstMac[0],eth_.dstMac[1],eth_.dstMac[2],eth_.dstMac[3],eth_.dstMac[4],eth_.dstMac[5]);	

	printf("src MAC: ");
	printf("%02X:%02X:%02X:%02X:%02X:%02X\n",eth_.srcMac[0],eth_.srcMac[1],eth_.srcMac[2],eth_.srcMac[3],eth_.srcMac[4],eth_.srcMac[5]);	
	
	return 0;
}

int print_Ip4(struct Ip4_header* iph)
{
	struct Ip4_header iph_;
	memcpy(&iph_,iph,sizeof(iph_));

	printf("src IP: ");
	printf("%d.%d.%d.%d\n",iph_.src<<24>>24,iph_.src<<16>>24,iph_.src<<8>>24,iph_.src>>24);

	printf("dst IP: ");
	printf("%d.%d.%d.%d\n",iph_.dst<<24>>24,iph_.dst<<16>>24,iph_.dst<<8>>24,iph_.dst>>24);

	return 0;
}

int print_Tcp(struct Tcp_header* tcph)
{
	struct Tcp_header tcph_;
	memcpy(&tcph_,tcph,sizeof(&tcph_));
	printf("src port: %d\n",tcph_.src_port);
	printf("dst port: %d\n",tcph_.dst_port);
	return 0;
}

