CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++14 -O4
CXX=g++

all: simulation t_lattice t_direction
	rm -f @^
	make simulation
	make t_lattice
	./t_lattice

simulation: main.cpp
	$(CXX) -o $@ $(CXXFLAGS) $^

t_lattice: lattice.o t_lattice.cpp direction.hpp
	$(CXX) -o $@ $(CXXFLAGS) $^

lattice.o: lattice.hpp lattice.cpp direction.hpp

t_direction: direction.o t_direction.cpp
	$(CXX) -o $@ $(CXXFLAGS) $^

direction.o: direction.cpp
