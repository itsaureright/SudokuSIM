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

    Sudoku(int ordre, int nbcase, bool allSol, bool uniqueSol) ; 
    void Solve() ;  // Pour résoudre la grille
    bool isValid(const Grille& g, int ligne, int col, int val);  // Vérifie que le placement d'un chiffre est ok

private:   
    std::pair<int,int> blocCoords(int ligne, int col) const; // Coordonnées des blocs
};

//Constructeurs

inline Sudoku::Sudoku(int ordre, int nbcase, bool allSol, bool uniqueSol) : ordre(ordre), nbcase(nbcase), allSol(allSol), uniqueSol(uniqueSol) {}

//Fonctions

inline pair<int,int> Sudoku::blocCoords(int ligne, int col) const { 
    int n = ordre;
    int blocL = (ligne / n) * n; 
    int blocC = (col / n) * n; 
    return {blocL, blocC}; }

inline bool Sudoku::isValid(const Grille& g, int ligne, int col, int val)
{   vector<vector<int>> grille = g.grille;
    int n = ordre;
    // Vérifier la ligne
    for (int j = 0; j < grille[ligne].size(); j++) {
        if (j != col && grille[ligne][j] == val)
            return false;
    }

    // Vérifier la colonne
    for (int i = 0; i < grille.size(); i++) {
        if (i != ligne && grille[i][col] == val)
            return false;
    }

    // vérifie le bloc
    auto [blocL, blocC] = blocCoords(ligne, col); 
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if ((blocL + i != ligne || blocC + j != col) && grille[blocL + i][blocC + j] == val){
                return false; }
            }
        }

    return true; 
}

inline void Sudoku::Solve() { 
    vector<pair<suint, suint>> cases = grille_ini.casesVides;
    
}


