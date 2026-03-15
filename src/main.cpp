#include <iostream>
#include <vector>
#include <complex>
#include "grille.hpp"
#include <list>
#include "sudoku.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>


using namespace std ;
using suint = unsigned int ;

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    // Si l'utilisateur n'a rien passé en argument
    if (argc < 2) {
        cout << "Tape :\n"
             << "  - 1 si tu veux generer une grille unique et sa solution\n"
             << "  - 2 si tu veux jouer toi-meme au sudoku\n\n"
             << "Puis relance le programme avec l'option choisie.\n"
             << "Exemple : ./output/main 1\n";
        return 0;
    }

    // On récupère l'argument
    string choix = argv[1];

    if (choix == "1") {
        cout << "Tu as choisi : generer une grille unique.\n"; 
        int ordre; 
        int nbCases;
        int Diag;
        cout << "Donne l'ordre de la grille (ex : 3 pour un 9x9) : "; cin >> ordre;
        cout << "Donne le nombre de cases a remplir initialement (ce nombre peut augmenter pour avoir une grille unique) : "; cin >> nbCases;
        cout << "Souhaites tu un sudoku classique (0) ou un sudoku diagonal (1)"; cin >> Diag;
        //Diag 
        if (Diag == 1 ) {
        Sudoku S(ordre, nbCases, false, false); 
        cout << "Grille initiale :\n";
        S.grille_ini.genererGrillePartielleDiag(nbCases);
        S.grille_ini.afficher();
        cout << "Grille unique :\n";
        S.preparerGrilleUniqueDiag();
        S.grille_ini.afficher();
        cout << "Solution unique :\n";
        S.SolveDiag();
        for (const Grille& sol : S.grille_sol) {
        sol.afficher();
        }
        if (S.grille_sol.empty()){
            cout << "Il n'y a pas de solutions." ;
        }
        }
        else if(Diag == 0){
        cout << "\nGeneration d'une grille de taille " << ordre*ordre << "x" << ordre*ordre << " avec " << nbCases << " cases vides.\n";
        Sudoku S(ordre, nbCases, false, false); 
        cout << "Grille initiale :\n";
        S.grille_ini.genererGrillePartielle(nbCases);
        S.grille_ini.afficher();
        cout << "Grille unique :\n";
        S.preparerGrilleUnique();
        S.grille_ini.afficher();
        cout << "Solution unique :\n";
        S.Solve();
        for (const Grille& sol : S.grille_sol) {
        sol.afficher();
        }
    }
    }

    else if (choix == "2") {
    cout << "Mode 2 : jouer toi-meme au sudoku.\n";

    int ordre;
    int nbCases;
    int difficulte;
    suint A;

    cout << "Donne l'ordre (3 pour 9x9) : ";
    cin >> ordre;

    cout << "Choisis ta difficultée : 1 - facile , 2 - moyen, 3 - difficile";
    cin >> difficulte;

    A = ordre*ordre*ordre*ordre; 

    if (difficulte == 1){
        nbCases = floor(0.36*A);
    }

    else if (difficulte == 2){
        nbCases = floor(0.26*A);
    }

    else if (difficulte == 3){
        nbCases = floor(0.18*A);
    }

    Sudoku S(ordre, nbCases, false, false);

    // Initialisation grille vide
    suint N = ordre*ordre;
    S.grille_ini.n = ordre;
    S.grille_ini.grille.assign(N, vector<int>(N, 0));

    // Génération simple unique
    int nbiter = 0;
    int maxiter=50;
    while(S.grille_sol.empty() && nbiter < maxiter){
    S.grille_sol.clear();
    S.grille_ini.genererGrillePartielle(nbCases);
    S.allSol = false;   // on veut juste savoir si une solution existe
    S.Solve(); 
    nbiter += 1 ;
    cout << "reload\n";}

    S.grille_sol.clear();
    S.preparerGrilleUnique();
    S.jouerGraphique();
}
}