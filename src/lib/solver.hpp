#ifndef SOLVER_HPP
#define SOLVER_HPP

set<int> get_bounded_vars(vector<set<int>> &cnf, unordered_map<int, set<int>> &map);
unordered_map<int, set<int>> map_clauses(vector<set<int>> &cnf);
set<int> resolve(set<int> &clause1, set<int> &clause2, int resolveBy);
void bve(vector<set<int>> &cnf);
bool solve(vector<set<int>> &cnf, vector<int> &truths);

#endif
