#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

using namespace std;

#include "solver.hpp"

set<int> get_literals(vector<vector<int>> &cnf) {
    set<int> literals;

    // Parse the CNF to fill the sets
    for (const auto& clause : cnf) {
        for (int literal : clause) {
        	literals.insert(literal);
        }
    }

    return literals;
}

bool solve(vector<vector<int>> &cnf, vector<int> &assigment) {
	if (cnf.empty()) {
		return true;
	}

	set<int> pures = get_literals(cnf);

	while (!pures.empty()) {
		for (int pure : pures) {
			if (pures.find(-pure) != pures.end()) {
				return false;
			} else {
				unit_propagate()
			}
		}
		pures = get_literals(cnf);
	}
	return true;
}


/*
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
