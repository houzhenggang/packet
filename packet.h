#ifndef __PACKET_H
#define __PACKET_H

ssize_t packet_read(int fd, void *buf, size_t count);
ssize_t packet_write(int fd, void *buf, size_t count);

#endif
