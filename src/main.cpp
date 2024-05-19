#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>

using namespace std;

#include "lib/dimacs.hpp"
#include "lib/solver.hpp"

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

	vector<set<int>> cnf;
	vector<int> thruths;

	cnf_read_all(input, cnf, a, b);
	solve(cnf, thruths);

	return 0;
}
