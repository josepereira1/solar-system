IDIR=include/
TINYXMLDIR=tinyxml/
CPP_FILES_TINYXML=$(wildcard tinyxml/*.cpp)
CFLAGS = -std=c++11 -Wall -Wextra -I $(IDIR) -I $(TINYXMLDIR) $(CPP_FILES_TINYXML) 

get_teste: testeXML.cpp xmlParser.cpp
	g++ $(CFLAGS) xmlParser.cpp testeXML.cpp -o xmlTest

clean:
	rm -f xmlTest