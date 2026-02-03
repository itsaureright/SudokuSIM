#pragma once
#include <iostream>
#include <vector>
#include <complex>
using namespace std ;
using suint = unsigned int ;


class Grille  
{public :
    Grille() = default; // constructeur vide 
    Grille(suint ordre);

    vector<vector<int>> grille;
    suint n=0;                                         // ordre de la grille
    mutable vector<pair<suint , suint>> casesVides ; // vecteur des cases vides
    std::vector<suint> valeursAdmissibles(suint i, suint j);
    mutable vector<suint> vs , vl ,vc ,vb;          // vecteurs de travail vs : valeurs possibles, vl valeur ligne, vc : valeur colonne, vb :valeurs bloc
    void genererGrillePartielle(suint p);
    void afficher() const;
};

