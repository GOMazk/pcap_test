#Makefile
all: pcap_test

pcap_test: main.o packetheader.o
	g++ -o pcap_test main.o packetheader.o -lpcap

main.o: packetheader.h main.c

packetheader.o: packetheader.h packetheader.c

clean:
	rm -f pcap_test
	rm -f *.o
