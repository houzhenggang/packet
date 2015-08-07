#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

// read at most count bytes to buf
ssize_t packet_read(int fd, void *buf, size_t count) {
	ssize_t ret, nread = 0;

	while (count > 0) {
		ret = read(fd, buf, count);
		if (ret < 0) {
			return ret;
		} else if (ret == 0) {
			break;
		}

		buf = (uint8_t*)buf +  ret;
		count -= ret;
		nread += ret;
	}

	return nread;
}

ssize_t packet_write(int fd, void *buf, size_t count) {
	return write(fd, buf, count);
}
