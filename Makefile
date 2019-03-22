IDIR=include/
TINYXMLDIR=tinyxml/
CFLAGS = -std=c++11 -Wall -Wextra -I $(IDIR) -I $(TINYXMLDIR) $(CPP_FILES_TINYXML) 

CPP_FILES_EXCLUDE=src/generator.cpp src/engine.cpp

CPP_FILES_GENERATOR=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp)) src/generator.cpp
CPP_FILES_TINYXML=$(wildcard tinyxml/*.cpp)

get_generator: 
	g++ $(CFLAGS) $(CPP_FILES_GENERATOR) -o generator

get_xml:
	g++ $(CFLAGS) tests/testeXML.cpp -o xml

get_test:
	g++ $(CFLAGS) src/group.cpp src/operation.cpp tests/testGROUP_OPERATION.cpp -o teste

get_test_figura:
	clear
	g++ $(CFLAGS) src/figura.cpp tests/testeFigura.cpp -o teste


generate: install
	generator cone 10 10 10 10 cone.3d
	generator sphere 10 10 10 sphere.3d
	generator box 10 10 10 3 box.3d
	cp cone.3d sphere.3d box.3d file.xml bin_linux/
	cp cone.3d sphere.3d box.3d file.xml bin_windows_engine/
	cp cone.3d sphere.3d box.3d file.xml bin_osx/


install: get_generator
	cp generator /usr/local/bin/

uninstall: clean

clean:
	rm -f generator
	rm -f /usr/local/bin/generator
	rm -f xml
	rm -f *.3d
	rm -f bin_osx/*.3d
	rm -f bin_windows_engine/*.3d
	rm -f bin_linux/*.3d
	rm -f *.out
	rm -f teste
	rm -f test
