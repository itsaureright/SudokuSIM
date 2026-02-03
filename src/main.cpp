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

    Sudoku S(3, 17, false, false); 
    S.grille_ini.genererGrillePartielle(15);
    S.grille_ini.afficher();
    S.Solve();
    for (const Grille& sol : S.grille_sol) {
    sol.afficher();
    }


    return 0;
}
