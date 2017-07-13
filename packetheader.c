int analyze_packet(u_char* packet)
{
	Ethnet_header eth_h;
	Ip_header ip_h;
	Tcp_header tcp_h;
	
	memncpy(eth_h,packet,sizeof(eth_h));
	print_eth(eth_h);
		
	return 0;
}

short int print_eth(Ethnet_header eth)
{
	printf("dst MAC: ");
	for(int i=0;i<6;i++){
		printf("%02X:",eth.dstMac[i]);	
	}
	printf("\r\n");
	printf("src MAC: ");
	for(int i=0;i<6;i++){
		printf("%02X:",eth.srcMac[i]);	
	}
	printf("\r\n");
	//printf("type:");
	return eth.type;
}

char print_Ip(Ip_header iph)
{
	return 0;
}

int print_Tcp(Tcp_header tcph)
{
	return 0;
}
