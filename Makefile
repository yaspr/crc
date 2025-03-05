CC=gcc
CFLAGS=-Wall -Wextra -g
OFLAGS=-O3

test_crc: test_crc.c
	$(CC) $(CFLAGS) $(OFLAGS) $< crc.c -o $@

clean:
	rm -Rf test_crc
