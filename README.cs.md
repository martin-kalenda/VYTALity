# VYTALity
[![English](https://img.shields.io/badge/English-green?style=flat)](README.md)

DPLL SAT solver s unit propagací. Vytvořen jako zápočtový úkol do předmětu VYTAL, který jsem studoval na Univerzitě Palackého v Olomouci.

## Úvod
Založen na [Wikipedia stránce DPLL algoritmu](https://en.wikipedia.org/wiki/DPLL_algorithm) a tomto [shrnutí DPLL algoritmu](https://www.cs.ox.ac.uk/people/james.worrell/lecture06.pdf) od Oxford Department of Computer Science. V tento moment je jediným cílem programu splnit veškeré požadavky pro zápočet, časem může být funkcionalita rozšířena.

### Požadavky

Požadavky jsou následující:
1. program musí být založen na DPPL algoritmu s unit propagací (další vylepšení jsou dobrovolná, očekává se ale přiměřená efektivita)
2. program se spustí příkazem: "solver input.cnf"
3. program vypíše na výstup řádky s následujícími informacemi:
    1. problém je SAT/UNSAT
    2. seznam literálů vyhodnocených na "pravda"
    3. procesorový čas potřebný pro čtení a inicializaci
    4. procesorový čas potřebný pro výpočet
    5. počet provedených unit propagací
    6. počet uzlů prohledávaného binárního stromu

## Použití
TBD