IDIR=include/
TINYXMLDIR=tinyxml/
CFLAGS = -std=c++11 -Wall -Wextra -I $(IDIR) -I $(TINYXMLDIR) $(CPP_FILES_TINYXML) 

CPP_FILES_EXCLUDE=src/generator.cpp src/engine.cpp

CPP_FILES_GENERATOR=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp)) src/generator.cpp
CPP_FILES_TINYXML=$(wildcard tinyxml/*.cpp)

get_generator: 
	g++ $(CFLAGS) $(CPP_FILES_GENERATOR) -o generator

teste_xml:
	g++ $(CFLAGS) src/group.cpp src/operation.cpp tests/testeXML.cpp -o xml

teste_f2l:
	g++ $(CFLAGS) src/file2list.cpp tests/testef2l.cpp -o f2l

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
	rm -f f2l