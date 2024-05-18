# VYTALity
A DPLL SAT solver with unit propadation. Created as the final assignment for the VYTAL subject I took @ UPOL.

## Introduction
Based on the [Wikipedia DPLL algorithm page](https://en.wikipedia.org/wiki/DPLL_algorithm) and this [DPLL algorithm breakdown](https://www.cs.ox.ac.uk/people/james.worrell/lecture06.pdf) by Oxford Department of Computer Science. At this time the only goal of this program is to fulfill all the requirements for completing the subject, I might improve upon these later.

### Requirements

The requirements are as follows:
    1. the program should be based on the DPLL algorithm with unit propagation (further improvements are optional, but reasonable effectiveness is expected)
    2. the program is run by executing "solver input.cnf"
    3. the program will print lines to standard output containing this information:
        i. problem is SAT/UNSAT
       ii. a list of literals that evaluated to "true"
      iii. procesor time needed for reading and initialization
       iv. procesor time needed for evaluation
        v. number of unit propagations
       vi. number of nodes in the searched binary tree

## Usage
TBD