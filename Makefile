CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -fPIC
LIBS = -lQt5Widgets -lQt5Core -lQt5Gui

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp $(LIBS)

clean:
	rm -f main
