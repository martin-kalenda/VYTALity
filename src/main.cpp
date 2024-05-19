#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
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

	vector<vector<int>> cnf;

	cnf_read_all(input, cnf, a, b);

	for (int i = 0; i < cnf.size(); i++) {
		for (int j = 0; j < cnf[i].size(); j++) {
			cout << cnf[i][j] << " ";
		}
		cout << endl;
	}

	vector<int> asg;


	vector<vector<int>> test = { { 2, 5 }, { 3 }, { -3 } };

	if (solve(test, asg)) {
		cout << "error" << endl;
	} else {
		cout << "UNSAT" << endl;
	}

	return 0;
}
