#include <stdio.h>
struct Ethnet_header{
	char dstMac[6];
	char srcMac[6];
	short int type;
};

struct Ip_header{
	
};

struct Tcp_header{
	
};

int analyze_packet( void* packet )
{
	struct Ethnet_header eth_h;
	struct Ip_header ip_h;
	struct Tcp_header tcp_h;
	
	memncpy(eth_h,packet,sizeof(eth_h));
	print_eth(&eth_h);
		
	return 0;
}

int print_eth(struct Ethnet_header* eth)
{
	struct Ethnet_header eth_;
	int i;
	memncpy(eth_,eth,sizeof(eth_));
	printf("dst MAC: ");
	for(i=0;i<6;i++){
		printf("%02X:",eth_.dstMac[i]);	
	}
	printf("\r\n");
	printf("src MAC: ");
	for(i=0;i<6;i++){
		printf("%02X:",eth_.srcMac[i]);	
	}
	printf("\r\n");
	//printf("type:");
	return eth_.type;
}

char print_Ip(struct Ip_header* iph)
{
	return 0;
}

int print_Tcp(struct Tcp_header* tcph)
{
	return 0;
}
