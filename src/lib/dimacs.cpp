#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

#include "dimacs.hpp"

// skip leading comments from the stream
void skip_comments(ifstream &input) {
	string line = "";
	streampos pos = 0;

	// read lines from input until they begin with something else than 'c'
	while (true) {
		pos = input.tellg();

		getline(input, line);

		if (line.empty() || line[0] != 'c') {
			input.seekg(pos);
			break;
		}
	}
}

// read the header of given DIMACS filestream
bool cnf_read_params(ifstream &input, int &nbvar, int &nbclauses) {
	string line = "";
	string format = "";

	// read what should be the parameter line
	try {
		// check that input stream is not NULL
		if (!input) {
			throw runtime_error(
				"Provided stream is NULL.");
		}

		getline(input, line);

		// line doesn't start with 'p' or is empty
		if (line.empty() || line[0] != 'p') {
			throw runtime_error(
				"Unable to read parameters.");
		}

		// skip "p" and read the next word, expect "cnf"
		istringstream iss(line);
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
  	// read was successful
		return true;
	}
	// catch exceptions
	catch (const exception& e) {
		cerr << "An exception occured while reading header:\n" << e.what() << endl;
		return false;
	}
}


// read the body of given DIMACS filestream
// TODO: exception handling
bool cnf_read_body(ifstream &input, vector<vector<int>> &cnf, int nbvar, int nbclauses) {
	int literal = 0;
	string line = "";
	istringstream iss;

	// TODO: test performance of creating a new instance for each line vs iss.clear; iss.str();
	while (getline(input, line)) {
		vector<int> clause;
		iss.clear();
		iss.str(line);

		while (iss >> literal) {
			if (literal == 0) {
				break;
			}
			clause.push_back(literal);
		}
		cnf.push_back(clause);
	}
	return true;
}

bool cnf_read_all(ifstream &input, vector<vector<int>> &cnf, int &nbvar, int &nbclauses) {
	skip_comments(input);
	cnf_read_params(input, nbvar, nbclauses);
	cnf_read_body(input, cnf, nbvar, nbclauses);

	return true;
}
