# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cstring>
# include <fstream>
# include <cmath>
# include <ctime>

using namespace std;

# include "dimacs.hpp"


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
bool read_params(ifstream &input, int &nbvar, int &nbclauses) {
	string line = "";
	string format = "";

	// read what should be the parameter line
	try {
		getline(input, line);

		cout << line << endl;

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

	catch (const exception& e) {
		cerr << "An exception occured while reading header:\n" << e.what() << endl;
		return false;
	}
}


// read the body of given DIMACS filestream
bool read_body(const ifstream &input, int &nbvar, int &nbclauses, bool consume = true);

bool read(const ifstream &input, int &nbvar, int &nbclauses );
