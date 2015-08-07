#
# This makefile is targeting both FreeBSD and Linux (GNU) make
#

RCS=packet.c sock.c
OBJ=packet.o sock.o
TARGETS=send_link
CC?=clang
CFLAGS?=-O2 -Wall
RM?=rm -f

all: $(TARGETS)

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $< 

send_link: $(OBJ) send_link.c
	$(CC) -o send_link send_link.c $(OBJ)

clean: 
	$(RM) $(OBJ) $(TARGETS)

