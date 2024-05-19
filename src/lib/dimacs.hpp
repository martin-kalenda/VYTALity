#ifndef DIMACS_HPP
#define DIMACS_HPP

void skip_comments(ifstream &input);
bool cnf_read_params(ifstream &input, int &nbvar, int &nbclauses);
bool cnf_read_body(ifstream &input, vector<vector<int>> &cnf, int nbvar = -1, int nbclauses = -1);
bool cnf_read_all(ifstream &input, vector<vector<int>> &cnf, int &nbvar, int &nbclauses);

#endif
