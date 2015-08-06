#include <sys/types.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef __linux__
#include <netpacket/packet.h>
#endif

#ifdef __FreeBSD__

#endif


#if __linux__ /* Linux version of sock_open_raw */
int sock_open_raw(const char *iface_name) {
	struct ifaddrs *ifp = NULL, *curr;
	struct sockaddr_ll sa;
	int fd;

	if (getifaddrs(&ifp) < 0) {
		return -1;
	}

	for(curr = ifp; curr != NULL; curr = curr->ifa_next) {
		if (curr->ifa_addr == NULL || curr->ifa_addr->sa_family != PF_PACKET) {
			continue;
		}

		if (strcmp(curr->ifa_name, iface_name) == 0) {
			memcpy(&sa, curr->ifa_addr, sizeof(struct sockaddr_ll));
			freeifaddrs(ifp);
			return 1;
		}
	}

	freeifaddrs(ifp);
	return -1;

	fd = socket(PF_PACKET, SOCK_RAW, 0);
	if (fd < 0) {
		return -1;
 	}

	if (bind(fd, (struct sockaddr*)&sa, sizeof(sa)) < 0) {
		return -1;
	}

	return fd;
}
#elif __FreeBSD__ /* FreeBSD version of sock_open_raw */

#endif
