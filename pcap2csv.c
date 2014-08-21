/*
 * Use pcap_open_offline() to open a savefile, containing packet capture data,
 * and use the print_addrs() routine to print the source and destination IP
 * addresses from the packet capture data to stdout.
 */

#include <stdio.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include "eth2.h"
#include "ip.h"
#include "tcp.h"

int packets = 0;   /* running count of packets read in */

void print_pkt_fields(u_char *user, const struct pcap_pkthdr *hdr, const u_char *data);

int
main(int argc, char **argv)
{
  pcap_t *p;               /* packet capture descriptor */
  char filename[80];       /* name of savefile to read packet data from */
  char errbuf[PCAP_ERRBUF_SIZE];  /* buffer to hold error text */
  char prestr[80];         /* prefix string for errors from pcap_perror */

  if (argc >= 2)
    strcpy(filename,argv[1]);

  /*
   * Open a file containing packet capture data. This must be called
   * before processing any of the packet capture data. The file
   * containing pcaket capture data should have been generated by a
   * previous call to pcap_open_live().
   */
  if (!(p = pcap_open_offline(filename, errbuf))) {
    fprintf(stderr,
	    "Error in opening savefile, %s, for reading: %s\n",
	    filename, errbuf);
    exit(2);
  }

  /*
   * Call pcap_dispatch() with a count of 0 which will cause
   * pcap_dispatch() to read and process packets until an error or EOF
   * occurs. For each packet read from the savefile, the output routine,
   * print_pkt_fields(), will be called to print the source and destinations
   * addresses from the IP header in the packet capture data.
   * Note that packet in this case may not be a complete packet. The
   * amount of data captured per packet is determined by the snaplen
   * variable which was passed into pcap_open_live() when the savefile
   * was created.
   */
  if (pcap_dispatch(p, 0, &print_pkt_fields, (u_char *)0) < 0) {
    /*
     * Print out appropriate text, followed by the error message
     * generated by the packet capture library.
     */
    sprintf(prestr,"Error reading packets from filename %s",
	    filename);
    pcap_perror(p,prestr);
    exit(4);
  }

  /*
   * Close the packet capture device and free the memory used by the
   * packet capture descriptor.
   */

  pcap_close(p);
  return 0;
}

void
print_pkt_fields(u_char *user, const struct pcap_pkthdr *hdr, const u_char *data)
{
  int ihl;
  int tot_len_ip;
  int offset = 0;

  if (hdr->caplen < 0) {
    /* captured data is not long enough to extract mac address */
    fprintf(stderr,
	    "Error: not enough captured packet data present to extract MAC addresses.\n");
    return;
  }

  if (hdr->caplen >= 14) {
    print_ether_fields(data, offset);
  }

  if (hdr->caplen >= 34) {
    offset = 14;
    print_ip_fields(data, offset);
    ihl = get_ihl(data, offset);
    tot_len_ip = get_tot_len(data, offset);
    
  }

  if (tot_len_ip - ihl >= 20) {
    offset = ihl + 14;
    print_tcp_fields(data, offset);
  }
  
  printf("\n");
  packets++; /* keep a running total of number of packets read in */
}
