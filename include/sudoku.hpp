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
    void preparerGrilleUnique(); //Génère une grille unique
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
        grille_sol.push_back(g);

        // Pour avoir toutes les solutions :
        //return false;

        //Pour avoir 2 solutions :

        if (grille_sol.size()==2) {
            uniqueSol = false ;
            return true;
        }
        else {
            uniqueSol = true ;
            return false;
        }


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

}

inline void Sudoku::preparerGrilleUnique() {
    suint N = ordre * ordre;

    // Initialisation de la grille initiale à vide
    grille_ini.n = ordre;
    grille_ini.grille.assign(N, vector<int>(N, 0));

    // Génération aléatoire d'une grille partiellement remplie
    // nbcase est le nombre de cases que l'on veut remplir initialement
    grille_ini.genererGrillePartielle(nbcase);

    // Vérifier si la grille a déjà une solution unique
    this->allSol = true;       // on veut récupérer toutes les solutions
    this->grille_sol.clear();  // on vide la liste des solutions
    this->Solve();             // résoudre la grille

    if (grille_sol.size() == 1) {
        // La grille est déjà unique
        uniqueSol = true;
        return; // plus besoin de fixer d'autres cases
    }

    // Boucle jusqu'à ce qu'il n'y ait plus qu'une seule solution
    while (grille_sol.size() > 1) {
        // On compare les deux solutions extrêmes pour trouver une divergence
        const Grille& s1 = grille_sol.front();
        const Grille& s2 = grille_sol.back();

        bool caseFixee = false;

        // Chercher une case vide où les solutions divergent
        for (suint i = 0; i < N && !caseFixee; ++i) {
            for (suint j = 0; j < N && !caseFixee; ++j) {
                if (grille_ini.grille[i][j] == 0 && s1.grille[i][j] != s2.grille[i][j]) {
                    // On fixe la valeur de la première solution dans la grille initiale
                    grille_ini.grille[i][j] = s1.grille[i][j];
                    caseFixee = true;
                }
            }
        }

        // Recalculer toutes les solutions avec la nouvelle grille
        grille_sol.clear();
        this->Solve();
    }

    // À ce stade, la grille est à solution unique
    uniqueSol = true;
    grille_sol.clear();
}
