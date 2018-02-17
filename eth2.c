#include <sys/types.h>
#include <stdio.h>

struct frame {
	uint8_t dst[6];
	uint8_t src[6];
	/* TODO: handl optional Q-Tag */
	uint16_t type;
};

void
print_ether_fields(const u_char *data, int offset)
{
	struct frame *frame = (struct frame *)(data + offset);

	printf("\"dest_mac, %02x:%02x:%02x:%02x:%02x:%02x\",",
	    frame->dst[0], frame->dst[1], frame->dst[2],
	    frame->dst[3], frame->dst[4], frame->dst[5]);

	printf("\"src_mac, %02x:%02x:%02x:%02x:%02x:%02x\",",
	    frame->src[0], frame->src[1], frame->src[2],
	    frame->src[3], frame->src[4], frame->src[5]);

	printf("\"ether_type, 0x%04x\",", ntohs(frame->type));
}
