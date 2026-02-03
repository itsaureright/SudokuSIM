#include "sudoku.hpp"

//Sudoku.cpp
void Sudoku::afficherSolutions() const {
    for (const auto& g : grilles_sol) {
        g.afficher();
        std::cout << '\n';
    }
}