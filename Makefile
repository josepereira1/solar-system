IDIR=include/
TINYXMLDIR=tinyxml/
CFLAGS = -Wall -I $(IDIR) -I $(TINYXMLDIR) $(CPP_FILES_TINYXML)

CPP_FILES_EXCLUDE=src/generator.cpp src/engine.cpp

CPP_FILES_GENERATOR=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp)) src/generator.cpp
CPP_FILES_PARSER=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp)) tests/testeParser.cpp
CPP_FILES_TINYXML=$(wildcard tinyxml/*.cpp)
CPP_FILES_FILE_TESTE=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp)) tests/FILE_teste.cpp

get_generator:
	g++ $(CFLAGS) $(CPP_FILES_GENERATOR) -o generator

get_parser:
	g++ $(CFLAGS) $(CPP_FILES_PARSER) -o parser

#get_FILE:
#	g++ $(CFLAGS) $(CPP_FILES_FILE_TESTE) -o teste

install: get_generator
	cp generator /usr/local/bin/

uninstall: clean

clean:
	rm -f generator
	rm -f parser
	rm -f teste
	rm -f /usr/local/bin/generator
	rm -f *.o