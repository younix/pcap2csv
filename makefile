CC ?= cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g

pcap2csv: pcap2csv.o eth2.o ip.o tcp.o
	$(CC) -o pcap2csv pcap2csv.o eth2.o ip.o tcp.o -l pcap

pcap2csv.o: pcap2csv.c eth2.h ip.h tcp.h
	$(CC) $(CFLAGS) -c pcap2csv.c

ip.o: ip.c
	$(CC) $(CFLAGS) -c ip.c

eth2.o: eth2.c
	$(CC) $(CFLAGS) -c eth2.c

tcp.o: tcp.c
	$(CC) $(CFLAGS) -c tcp.c

.PHONY: clean
clean:
	find . -maxdepth 1 -type f -perm 775 -delete
	find . -maxdepth 1 -type f -iname '*.o' -delete

test: test.py csv2sql.py
	python -m unittest test
