#include <stdio.h>
struct Ethnet_header{
	unsigned char dstMac[6];
	unsigned char srcMac[6];
	unsigned short int type;
};

struct Ip_header{
	
};

struct Tcp_header{
	
};

int analyze_packet( void* header )
{
	struct Ethnet_header eth_h;
	struct Ip_header ip_h;
	struct Tcp_header tcp_h;
	
	memcpy(&eth_h,header,sizeof(eth_h));
	print_eth(&eth_h);
	
	if(eth_h.type==0x0800){
		printf("It\'s IPv4");
	}
		
	return 0;
}

int print_eth(struct Ethnet_header* eth)
{
	struct Ethnet_header eth_;
	memcpy(&eth_,&eth,sizeof(eth_));
	printf("dst MAC: ");
	printf("%02X:%02X:%02X:%02X:%02X:%02X\n",eth_.dstMac[0],eth_.dstMac[1],eth_.dstMac[2],eth_.dstMac[3],eth_.dstMac[4],eth_.dstMac[5]);	

	printf("src MAC: ");
	printf("%02X:%02X:%02X:%02X:%02X:%02X\n",eth_.srcMac[0],eth_.srcMac[1],eth_.srcMac[2],eth_.srcMac[3],eth_.srcMac[4],eth_.srcMac[5]);	
	
	return 0;
}

char print_Ip(struct Ip_header* iph)
{
	return 0;
}

int print_Tcp(struct Tcp_header* tcph)
{
	return 0;
}
