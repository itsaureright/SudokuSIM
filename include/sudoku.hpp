#pragma once 
#include <iostream>
#include <vector>
#include <complex>
#include "grille.hpp"
#include <list>
using namespace std ;
using suint = unsigned int ;

class Sudoku
{ public :
    int ordre=0; // ordre du Sudoku
    int nbcase=0; // nombre de case à initialiser
    bool allSol=false; // recherche de toutes les solutions si true
    bool uniqueSol=false; // pour le test d’unicité
    Grille grille_ini ; // grille initiale
    list<Grille> grille_sol ; // liste des grilles solutions
};