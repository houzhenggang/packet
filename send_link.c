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

int main(int argc, char *argv[]) {
	int fd;
	char pktbuf[1500];
	ssize_t len;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <iface-name>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	len = packet_read(STDIN_FILENO, pktbuf, sizeof(pktbuf));
	if (len < 0) {
		perror("packet_read");
		return EXIT_FAILURE;
	}
	
	close(STDIN_FILENO); 
	fd = sock_open_raw(argv[1]);
	if (fd < 0) {
		perror("sock_open_raw");
		return EXIT_FAILURE;
	}

	if (write(fd, pktbuf, (size_t)len) != len) {
		perror("sendto");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
