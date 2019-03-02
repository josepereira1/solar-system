IDIR=lib
CC=gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0` -I$(IDIR)
C_FILES=$(wildcard $(IDIR)/*.c)

get_teste:
	$(CC) $(CFLAGS) $(C_FILES) -o teste

get_generator:
	$(CC) $(CFLAGS) generator.c -o generator

install:
	cp generator /usr/local/bin/

uninstall:
	make clean

clean:
	rm -f teste
	rm -f *.3d
	rm -f generator
	rm -f /usr/local/bin/generator