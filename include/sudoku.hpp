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
    bool solveRec(Grille& g, vector<pair<suint,suint>>& cases, size_t idx);
private:   
    std::pair<int,int> blocCoords(int ligne, int col) const; // Coordonnées des blocs
};

//Constructeurs

inline Sudoku::Sudoku(int ordre, int nbcase, bool allSol, bool uniqueSol): ordre(ordre), nbcase(nbcase), allSol(allSol), uniqueSol(uniqueSol),grille_ini(ordre){}

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

inline bool Sudoku::solveRec(Grille& g, vector<pair<suint,suint>>& cases, size_t idx)
{
    if (idx == cases.size()) {
        return true;
    }

    suint i = cases[idx].first;
    suint j = cases[idx].second;

    if (g.grille[i][j] != 0) {
        return solveRec(g, cases, idx+1);
    }

    vector<suint> valad = g.valeursAdmissibles(i, j);

    for (suint v : valad) {

        if (isValid(g, i, j, v)) {

            g.grille[i][j] = v;

            bool ok = solveRec(g, cases, idx+1);
            if (ok) return true;
        }
        g.grille[i][j] = 0;
    }

    return false;
}



inline void Sudoku::Solve() { 
    Grille g = grille_ini;

    g.n = ordre;                 
    suint N = g.n * g.n;         

    g.casesVides.clear();        
    for (suint i = 0; i < N; ++i)
        for (suint j = 0; j < N; ++j)
            if (g.grille[i][j] == 0)
                g.casesVides.push_back({i, j});

    bool ok = solveRec(g, g.casesVides, 0);  

    if (!ok) {
        cout << "pas de solution";
    } else {
        grille_sol.push_back(g);             
    }
}


