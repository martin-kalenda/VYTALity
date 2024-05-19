solver: main.o dimacs.o solver.o
	g++ -o ../solver main.o dimacs.o solver.o

main.o: main.cpp
	g++ -c main.cpp

dimacs.o: lib/dimacs.cpp lib/dimacs.hpp
	g++ -c lib/dimacs.cpp

solver.o: lib/solver.cpp lib/solver.hpp
	g++ -c lib/solver.cpp
