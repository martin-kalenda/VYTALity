#ifndef SOLVER_HPP
#define SOLVER_HPP

set<int> get_literals(vector<vector<int>> &cnf);
bool solve(vector<vector<int>> &cnf, vector<int> &assigment);

#endif
