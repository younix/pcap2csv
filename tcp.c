#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>

struct segment {
	uint16_t src;
	uint16_t dst;
	uint32_t seq;
	uint32_t ack;
	uint8_t off : 4;
	uint8_t res : 4;
	uint8_t flag;
	uint16_t win;
	uint16_t chk;
	uint16_t ptr;
};

void
print_tcp_fields(const u_char *data, int offset)
{
	struct segment *segment = (struct segment *)(data + offset);

	printf("\"src_port, %d\",", ntohs(segment->src));
	printf("\"dst_port, %d\",", ntohs(segment->dst));
	printf("\"seq_num, %u\",", ntohl(segment->seq));
	printf("\"ack_num, %u\",", ntohl(segment->ack));
	printf("\"tcp_head_len, %d\",", segment->off);
	printf("\"cntrl_bits, 0x%x\",", segment->flag);
	printf("\"window, %d\",", ntohs(segment->win));
	printf("\"chksum, 0x%x\",", ntohs(segment->chk));
	printf("\"urg_ptr, 0x%x\",", ntohs(segment->ptr));
}
