#include <iostream>
#include <vector>
#include <complex>
#include "grille.hpp"
#include <list>
#include "sudoku.hpp"
#include <cstdlib>
#include <ctime>

using namespace std ;
using suint = unsigned int ;

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    Grille g;
    g.n = 3;                     // Sudoku 9x9
    g.grille.resize(9, vector<int>(9, 0));

    g.genererGrillePartielle(17);
    g.afficher();
    return 0;
}
