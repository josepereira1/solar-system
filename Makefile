IDIR=include/
TINYXMLDIR=tinyxml/
CFLAGS = -Wall -Wextra -I $(IDIR) -I $(TINYXMLDIR) $(CPP_FILES_TINYXML)

CPP_FILES_EXCLUDE=src/generator.cpp src/engine.cpp

CPP_FILES_GENERATOR=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp)) src/generator.cpp
CPP_FILES_TINYXML=$(wildcard tinyxml/*.cpp)

get_generator:
	g++ $(CFLAGS) $(CPP_FILES_GENERATOR) -o generator

get_xml:
	g++ $(CFLAGS) tests/testeXML.cpp -o xml

generate:
	generator cone 10 10 10 10 a.3d
	generator sphere 10 10 10 b.3d
	cp a.3d b.3d bin_linux
	cp a.3d b.3d bin_windows
	cp a.3d b.3d bin_osx


install: get_generator
	cp generator /usr/local/bin/

uninstall: clean

clean:
	rm -f generator
	rm -f /usr/local/bin/generator
	rm -f xml
