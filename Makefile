IDIR=lib
CC=gcc

CFLAGS = -Wall -I$(IDIR)


C_FILES=$(wildcard $(IDIR)/*.c)

get_teste:
	$(CC) $(CFLAGS) $(C_FILES) -o teste

get_generator:
	$(CC) $(CFLAGS) generator.c -o generator

get_design:
	$(CC) $(CFLAGS) $(C_FILES) design.cpp -o design

run:
	clear
	rm exe
	rm dados.txt
	gcc src/generator.c src/filterPoints.c src/file2list.c src/ArrayList.c src/Point.c src/list2file.c  generators/boxGenerator.c generators/coneGenerator.c generators/sphereGenerator.c generators/planeGenerator.c -I include/ -o exe

install:
	cp generator /usr/local/bin/

uninstall:
	make clean

clean:
	rm -f teste
	rm -f *.3d
	rm -f generator
	rm -f /usr/local/bin/generator
