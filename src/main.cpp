#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>




using namespace std;

#include "lib/dimacs.hpp"
//#include "lib/solver.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr << "Invalid amount of arguments." << endl;
		cerr << "usage: solver filepath" << endl;
		return 1;
	}

	ifstream input(argv[1]);

	int a;
	int b;

	skip_comments(input);
	read_params(input, a, b);
	cout << "read: " << a << b << endl;

	return 0;
}
