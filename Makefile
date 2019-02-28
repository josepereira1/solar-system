get_generator:
	gcc -Wall generator.c -o generator

install:
	cp generator /usr/local/bin/

uninstall:
	make clean

clean:
	rm -f *.3d
	rm -f generator
	rm -f /usr/local/bin/generator
