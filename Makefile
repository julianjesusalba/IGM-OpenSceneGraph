## Makefile

CXXFLAGS=-Wall -losg -losgViewer -losgDB -losgGA
CXX=g++

all: cubo

cubo: cubo.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	rm -f *.exe
