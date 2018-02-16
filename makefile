CC ?= cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g

pcap2csv: pcap2csv.o eth2.o ip.o tcp.o
	$(CC) -o pcap2csv pcap2csv.o eth2.o ip.o tcp.o -l pcap

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

pcap2csv.o: pcap2csv.c eth2.h ip.h tcp.h

.PHONY: clean
clean:
	find . -maxdepth 1 -type f -perm 775 -delete
	find . -maxdepth 1 -type f -iname '*.o' -delete
