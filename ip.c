#include <sys/types.h>
#include <stdio.h>

struct packet {
	uint8_t version : 4;
	uint8_t ihl : 4;
	uint8_t service;
	uint16_t length;
	uint16_t identity;
	uint16_t flags : 3;
	uint16_t offset : 13;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t chksum;
	uint8_t src[4];
	uint8_t dst[4];
};

int
get_ihl(const u_char *data, int offset)
{
	struct packet *packet = (struct packet *)(data + offset);

	return packet->ihl * 4;
}

int
get_tot_len(const u_char *data, int offset)
{
	struct packet *packet = (struct packet *)(data + offset);

	return packet->length;
}

void
print_ip_fields(const u_char *data, int offset)
{
	struct packet *packet = (struct packet *)(data + offset);

	printf("\"version, 0x%01x\",", packet->version);
	printf("\"ihl, %d\",", packet->ihl * 4);
	printf("\"tos, 0x%02x\",", packet->service);
	printf("\"datagram_len, %d\",", packet->length);
	printf("\"id, 0x%04x\",", packet->identity);
	printf("\"flags, 0x%01x\",", packet->flags);
	printf("\"frag_off, 0x%04x\",", packet->offset);
	printf("\"ttl, 0x%02x\",", packet->ttl);
	printf("\"protocol, 0x%02x\",", packet->protocol);
	printf("\"header checksum, 0x%04x\",", packet->chksum);
	printf("\"src_ip, %03d.%03d.%03d.%03d\",",
	    packet->src[0], packet->src[1], packet->src[2], packet->src[3]);
	printf("\"dst_ip, %03d.%03d.%03d.%03d\",",
	    packet->dst[0], packet->dst[1], packet->dst[2], packet->dst[3]);
}
