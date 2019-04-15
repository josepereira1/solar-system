IDIR=include/
TINYXMLDIR=tinyxml/
CPP_FILES_TINYXML=$(wildcard tinyxml/*.cpp)
CFLAGS = -std=c++11 -Wall -Wextra -I $(IDIR) -I $(TINYXMLDIR) $(CPP_FILES_TINYXML) 

CPP_FILES_EXCLUDE=src/testeXML.cpp src/testeFigura.cpp

CPP_FILES_GENERATOR=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp)) src/testeXML.cpp
CPP_FILES_TESTE=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp))

teste: src/testeXML.cpp
	g++ $(CFLAGS) $(CPP_FILES_GENERATOR) -o teste

clean:
	rm -f teste