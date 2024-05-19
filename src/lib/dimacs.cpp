#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

#include "dimacs.hpp"

// skip leading comments from the stream
void skip_comments(ifstream &input) {
	string line = "";
	streampos pos = 0;

	// return if input is NULL
	if (!input) {
		return;
	}
	// read lines from input
	while (true) {
		// save current stream position
		pos = input.tellg();
		// read line from stream
		getline(input, line);
		// check if line is empty or doesn't start with 'c'
		if (line.empty() || line[0] != 'c') {
			// return stream to saved position
			input.seekg(pos);
			// exit loop
			break;
		}
	}
}

// read the parameter line from given DIMACS filestream
bool cnf_read_params(ifstream &input, int &nbvar, int &nbclauses) {
	string line = "";
	string format = "";

	try {
		// check that input stream is not NULL
		if (!input) {
			throw runtime_error(
				"Provided stream is NULL.");
		}

		// read line from input
		getline(input, line);

		// check if line doesn't start with 'p' or is empty
		if (line.empty() || line[0] != 'p') {
			throw runtime_error(
				"Unable to read parameters.");
		}

		istringstream iss(line);
		// skip "p" and read the next word, expect "cnf"
		iss >> format >> format;

		// read word is not "cnf"
		if (format.compare("cnf") != 0) {
			throw runtime_error(
				"Problem is not CNF.");
		}
  	// extract parameters and check if extraction was successful
  	if (!(iss >> nbvar >> nbclauses)) {
  		throw runtime_error(
  			"Failed to read parameters nbvar and/or nbclauses.");
  	}
		return true;
	}
	catch (const exception &e) {
		cerr << "An exception occured while reading header:\n" << e.what() << endl;
		return false;
	}
}

// read the body of given DIMACS filestream, with parameter check
bool cnf_read_body(ifstream &input, vector<set<int>> &cnf, int &nbvar, int &nbclauses) {
	unordered_set<int> seen;
	int literal = 0;
	string line = "";
	istringstream iss;

	try {
		// check that input stream is not NULL
		if (!input) {
			throw runtime_error(
				"Provided stream is NULL.");
		}

		// read lines from input
		while (getline(input, line)) {
			set<int> clause;
			iss.clear();
			iss.str(line);

			// iterate through all words from current line
			while (iss >> literal) {
				// 0 indicates end of line
				if (literal == 0) {
					break;
				// only literals from range <-nbvar, nbvar> are allowed
				} else if (abs(literal) > nbvar) {
					throw runtime_error(
						"Literal name out of range.");
				// literal l and not(l) cannot be in the same clause
				} else if (clause.find(abs(literal)) == clause.end()) {
					throw runtime_error(
						"A literal and it's negation cannot be present in the same clause.");
				}
				// add pure literal to seen
				seen.insert(abs(literal));
				// add literal to clause
				clause.insert(literal);
			}
			// add clause to CNF
			cnf.push_back(clause);
		}

		// check if the real number of literals and clauses match values specified in parameter line
		if (seen.size() != nbvar || cnf.size() != nbclauses) {
			throw runtime_error(
				"Parameter and CNF mismatch.");
		}
		return true;
	}
	catch (const exception &e) {
		cerr << "An exception occured while reading body:\n" << e.what() << endl;
		return false;
	}
}

// cnf_read_body overload without input validation
bool cnf_read_body(ifstream &input, vector<set<int>> &cnf) {
	int literal = 0;
	string line = "";
	istringstream iss;

	try {
		if (!input) {
			throw runtime_error(
				"Provided stream is NULL.");
		}

		while (getline(input, line)) {
			set<int> clause;
			iss.clear();
			iss.str(line);

			while (iss >> literal) {
				if (literal == 0) {
					break;
				}
				clause.insert(literal);
			}
			cnf.push_back(clause);
		}
		return true;
	}
	catch (const exception &e) {
		cerr << "An exception occured while reading header:\n" << e.what() << endl;
		return false;
	}
}

bool cnf_read_all(ifstream &input, vector<set<int>> &cnf, int &nbvar, int &nbclauses) {
	// check that input stream is not NULL
	if (!input) {
		throw runtime_error(
			"Provided stream is NULL.");
	}

	// skip leading comments
	skip_comments(input);

	// read parameters and CNF, check if successful
	if (cnf_read_params(input, nbvar, nbclauses) && cnf_read_body(input, cnf)) {
		return true;
	}
	// read failed
	return false;
}
