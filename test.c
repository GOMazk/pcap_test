#include <stdio.h>
#include <stdint.h>

uint16_t my_ntohs(uint16_t val){
	return (val%256)*256 + val/256;
}
uint16_t my_ntohs2(){
}

int main(){
	char packet[] = {0x00,0x50};
	uint16_t port;
	port = my_ntohs( *(uint16_t*)packet );
	printf("%d\n",port);
}
