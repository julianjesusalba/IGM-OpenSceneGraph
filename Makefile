## Makefile

CXXFLAGS=-Wall -losg -losgViewer -losgDB
CXX=g++

all: cubo

cubo: cubo.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	rm -f *.exe
