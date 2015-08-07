#include <sys/types.h>
#include <stdio.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

#include "sock.h"
#include "packet.h"

void usage() {
	fprintf(stderr, "options:\n"
		"  -i <iface>        interface to use\n"
		"  -h                this text\n");
}

int main(int argc, char *argv[]) {
	int fd, opt;
	char pktbuf[1500], *iface_name = NULL;
	ssize_t len;

	while((opt = getopt(argc, argv, "hi:")) != -1) {
		switch (opt) {
			case 'i':
				iface_name = optarg;
				break;
			case 'h':
			default:
				usage();
				return EXIT_FAILURE;
		}
	}

	if (iface_name == NULL) {
		fprintf(stderr, "No interface set\n");
		return EXIT_FAILURE;
	}

	
	fd = sock_open_raw(iface_name);
	if (fd < 0) {
		perror("sock_open_raw");
		return EXIT_FAILURE;
	}
	
	len = packet_read(STDIN_FILENO, pktbuf, sizeof(pktbuf));
	if (len < 0) {
		perror("packet_read");
		return EXIT_FAILURE;
	}
	
	close(STDIN_FILENO);
	if (packet_write(fd, pktbuf, (size_t)len) != len) {
		perror("packet_write");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
