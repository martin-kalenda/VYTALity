solver: main.o dimacs.o
	g++ -o ../solver main.o dimacs.o

solver.o: main.cpp
	g++ -c main.cpp

dimacs.o: lib/dimacs.cpp lib/dimacs.hpp
	g++ -c lib/dimacs.cpp
