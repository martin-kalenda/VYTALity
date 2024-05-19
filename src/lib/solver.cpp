#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

#include "solver.hpp"

#define MAX_SIZE_INC 10

set<int> get_bounded_vars(int clauseCount, unordered_map<int, set<int>> &map) {
	set<int> bounded = {};
	set<int> seenClauses = {};
	int occurenceBalance = 0;

	for (const auto& pair : map) {
		for (int clauseIndex : pair.second) {
			if (clauseIndex < 0) {
				occurenceBalance--;
			} else {
				occurenceBalance++;
			}
		}
		if (seenClauses.size() != clauseCount && abs(occurenceBalance) < pair.second.size()) {
			bounded.insert(pair.first);
		}
		occurenceBalance = 0;
		seenClauses.clear();
  }
  return bounded;
}

unordered_map<int, set<int>> map_clauses(vector<set<int>> &cnf) {
	int i = 1;
	unordered_map<int, set<int>> map;

	for (set<int> clause : cnf) {
		for (int literal : clause) {
			if (literal < 0) {
				i = -i;
			}
			map[abs(literal)].insert(i);
			i = abs(i);
		}
		i++;
	}
	return map;
}

set<int> resolve(set<int> &clause1, set<int> &clause2, int resolveBy) {
	set<int> resolvedClause = {};

	for (int literal : clause1) {
		if (literal != resolveBy) {
			resolvedClause.insert(literal);
		}
  }
	for (int literal : clause2) {
		if (literal != -resolveBy) {
			// eliminate tautology
			if (resolvedClause.find(-literal) != resolvedClause.end()) {
				resolvedClause = {};
				break;
			}
			resolvedClause.insert(literal);
		}
	}
  return resolvedClause;
}

// Function to perform Bounded Variable Elimination
void bve(vector<set<int>> &cnf) {
	set<int> bVars = {};
	unordered_map<int, set<int>> map = {};

	set<set<int>> newClauses = {};
	set<int> newClause = {};

	vector<int> pClauses = {};
	vector<int> nClauses = {};

	while (true) {
		if (cnf.empty()) {
			break;
		}
		map = map_clauses(cnf);
		bVars = get_bounded_vars(cnf.size(), map);
		if (bVars.empty()) {
			break;
		}

		for (int var : bVars) {
			for (int clauseIndex : map[var]) {
				if (clauseIndex < 0) {
					nClauses.push_back(abs(clauseIndex) - 1);
				} else {
					pClauses.push_back(clauseIndex - 1);
				}
			}
			for (int pClauseIndex : pClauses) {
				for (int nClauseIndex : nClauses) {
					if (pClauseIndex != nClauseIndex) {
						newClause = resolve(cnf[pClauseIndex], cnf[nClauseIndex], var);
						if (!newClause.empty()) {
							newClauses.insert(newClause);
						}
					}
				}
			}

			for (set<int> clause : newClauses) {
				if (find(cnf.begin(), cnf.end(), clause) == cnf.end()) {
					cnf.push_back(clause);
				}
			}
			for (auto it = cnf.begin(); it != cnf.end();) {
    		if (it->find(var) != it->end()) {
        	it = cnf.erase(it);
    		} else {
        	++it;
    		}
			}
			newClauses.clear();
			pClauses.clear();
			nClauses.clear();
		}
	}
}


bool solve(vector<set<int>> &cnf, vector<int> &truths) {
	// PREPROCESSING
	bve(cnf);

	return true;
}





/*
set<int> get_literals(set<set<int>> &cnf) {
	set<int> literals;

	for (set<int> clause : cnf) {
		for (int literal : clause) {
			literals.insert(abs(literal));
		}
	}
	return literals;
}

set<int> get_units(vector<vector<int>> &cnf) {
    set<int> literals;

    // Parse the CNF to fill the sets
    for (vector<int> clause : cnf) {
        if (clause.size() == 1) {
        	literals.insert(literal);
        }
    }
    return literals;
}

void eliminate_pure_literals(vector<vector<int>> &cnf, vector<int> &truths) {
    unordered_set<int> seen;
    std::set<int> negativeLiterals;

    // Parse the CNF to fill the sets
    for (int i = 0; i < cnf.size(); i++) {
        for (int j = 0; j < cnf[i].size(); j++) {

        }
    }

    // Identify pure literals
    std::unordered_set<int> pureLiterals;
    for (int literal : positiveLiterals) {
        if (negativeLiterals.find(literal) == negativeLiterals.end()) {
            pureLiterals.insert(literal);
        }
    }
    for (int literal : negativeLiterals) {
        if (positiveLiterals.find(literal) == positiveLiterals.end()) {
            pureLiterals.insert(-literal);
        }
    }

    return pureLiterals;
}



bool dpll(vector<vector<int>> &cnf, vector<int> &truths) {
	if (cnf.empty()) {
		return true;
	}

	set<int> units = get_units(cnf);

	while (!units.empty()) {
		for (int pure : pures) {
			if (pures.find(-pure) != pures.end()) {
				return false;
			} else {
				propagate_unit()
			}
		}
		pures = get_literals(cnf);
	}
	return true;
}


function DPLL(Φ)
    // unit propagation:
    while there is a unit clause {l} in Φ do
        Φ ← unit-propagate(l, Φ);
    // pure literal elimination:
    while there is a literal l that occurs pure in Φ do
        Φ ← pure-literal-assign(l, Φ);
    // stopping conditions:
    if Φ is empty then
        return true;
    if Φ contains an empty clause then
        return false;
    // DPLL procedure:
    l ← choose-literal(Φ);
    return DPLL(Φ ∧ {l}) or DPLL(Φ ∧ {¬l});

function DPLL(S) {

    if (S is empty) {
        return("satisfiable");
    }
    while (there is some unit clause {p}, or some pure literal p) {
       if ({p} and {~p} are both in S) {
           return("unsatisfiable");
       } else {
           S = Simplify(S,p);
       }
    }
    if (S is empty) {
        return("satisfiable");
    }

    pick some literal p from a shortest clause in S;
    if (DPLL(Simplify(S,p))=="satisfiable") { //----Assign it TRUE
       return("satisfiable");
    } else {
       return(DPLL(Simplify(S,~p));           //----Assign it FALSE
    }
}

function Simplify(S,p) {

    delete every clause in S containing p;
    delete every occurrence in S of ~p;
    return(S);
}
*/
