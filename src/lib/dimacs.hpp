#ifndef DIMACS_HPP
#define DIMACS_HPP

void skip_comments(ifstream &input);
bool read_params(ifstream &input, int &nbvar, int &nbclauses);

#endif
