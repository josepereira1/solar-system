IDIR=include/
LIBXML2DIR=libxml2-2.9.8/
CC=gcc
CFLAGS = -Wall -I $(IDIR)

C_FILES_GENERATOR=src/ArrayList.c src/filterPoints.c src/list2file.c src/Point.c generators/boxGenerator.c generators/coneGenerator.c generators/sphereGenerator.c generators/planeGenerator.c src/generator.c 

get_generator:
	$(CC) $(CFLAGS) $(C_FILES_GENERATOR) -o generator

install:
	cp generator /usr/local/bin/

uninstall:
	make clean

clean:
	rm -f *.3d
	rm -f generator
	rm -f /usr/local/bin/generator