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
    // Si l'utilisateur n'a rien passé en argument
    if (argc < 2) {
        cout << "Tape :\n"
             << "  - 1 si tu veux generer une grille unique et sa solution\n"
             << "  - 2 si tu veux jouer toi-meme au sudoku\n\n"
             << "Puis relance le programme avec l'option choisie.\n"
             << "Exemple : ./main 1\n";
        return 0;
    }

    // On récupère l'argument
    string choix = argv[1];

    if (choix == "1") {
        cout << "Tu as choisi : generer une grille unique.\n"; 
        int ordre; 
        int nbCases;
        cout << "Donne l'ordre de la grille (ex : 3 pour un 9x9) : "; cin >> ordre;
        cout << "Donne le nombre de cases a remplir initialement (ce nombre peut augmenter pour avoir une grille unique) : "; cin >> nbCases;
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

    else if (choix == "2") {
    cout << "Mode 2 : jouer toi-meme au sudoku.\n";

    int ordre;
    int nbCases;

    cout << "Donne l'ordre (3 pour 9x9) : ";
    cin >> ordre;

    cout << "Donne le nombre de cases a remplir initialement : ";
    cin >> nbCases;

    Sudoku S(ordre, nbCases, false, false);

    // Initialisation grille vide
    suint N = ordre * ordre;
    S.grille_ini.n = ordre;
    S.grille_ini.grille.assign(N, vector<int>(N, 0));

    // Génération simple (pas forcément unique)
    S.grille_ini.genererGrillePartielle(nbCases);
    S.grille_sol.clear();
    S.allSol = false;   // on veut juste savoir si une solution existe
    S.Solve();

    if (S.grille_sol.empty()) {
        cout << "La grille generee n'a aucune solution ! essaye avec moins de chiffres. Regeneration...\n";
        cout << "Donne le nombre de cases a remplir initialement : ";
        S.grille_ini.genererGrillePartielle(nbCases);
        return 0; // ou relancer une generation
}
    S.jouerGraphique();;
}
}