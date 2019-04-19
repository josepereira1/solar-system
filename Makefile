IDIR=include/
TINYXMLDIR=tinyxml/
CPP_FILES_TINYXML=$(wildcard tinyxml/*.cpp)
CFLAGS = -std=c++11 -Wall -Wextra -I $(IDIR) -I $(TINYXMLDIR) $(CPP_FILES_TINYXML) 

CPP_FILES_EXCLUDE=src/generator.cpp src/engine.cpp

CPP_FILES_GENERATOR=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp)) src/generator.cpp
CPP_FILES_TESTE=$(filter-out $(CPP_FILES_EXCLUDE), $(wildcard src/*.cpp))

get_generator: src/generator.cpp
	g++ $(CFLAGS) $(CPP_FILES_GENERATOR) -o generator

get_f2l: tests/testef2l.cpp
	g++ $(CFLAGS) $(CPP_FILES_TESTE) tests/testef2l.cpp -o f2l

generate: file.xml install
	generator sphere 50 100 100 sphere1.3d
	generator sphere 10 30 30 sphere2.3d
	generator sphere 2 10 10 sphere3.3d
	generator bezier teapot.patch teapot.3d 10
	cp sphere1.3d sphere2.3d sphere3.3d file.xml teapot.xml teapot.3d engine_CMake/

install: get_generator
	cp generator /usr/local/bin/

uninstall: clean

clean:
	rm -f generator
	rm -f /usr/local/bin/generator
	rm -f *.3d
	rm -f bin/*.3d
	rm -f bin/*.xml
	rm -f bin_windows_engine/*.3d
	rm -f bin_windows_engine/*.xml
	rm -f *.out