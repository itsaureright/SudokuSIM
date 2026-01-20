#ifndef grille.hpp
#define grille.hpp
#include <iostream>
#include <vector>
#include <complex>
using namespace std ;
using suint = unsigned int ;


class Grille : vector<vector<int>>
{public :
    int n=0;                                         // ordre de la grille
    mutable vector<pair<suint , suint>> casesVides ; // vecteur des cases vides
    mutable vector<suint> vs , vl ,vc ,vb;           // vecteurs de travail
};


