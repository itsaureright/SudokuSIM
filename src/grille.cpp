#include "grille.hpp"

#include <cmath>
#include <algorithm> // Pour std::find
using suint = unsigned int ;

//Constructeur
Grille::Grille(suint ordre) { n = ordre; grille.resize(n*n, vector<int>(n*n, 0)); }

vector<suint> Grille::valeursAdmissibles(suint i, suint j)
{
    vl.clear(); vc.clear(); vb.clear(); vs.clear();

    suint N = n * n;

    // Ligne + colonne
    for (suint k = 0; k < N; ++k) {
        if (grille[i][k] != 0) vl.push_back(grille[i][k]);
        if (grille[k][j] != 0) vc.push_back(grille[k][j]);
    }

    // Bloc
    suint debutI = (i / n) * n;
    suint debutJ = (j / n) * n;

    for (suint r = debutI; r < debutI + n; ++r) {
        for (suint c = debutJ; c < debutJ + n; ++c) {
            if (grille[r][c] != 0)
                vb.push_back(grille[r][c]);
        }
    }

    // Valeurs admissibles
    for (suint v = 1; v <= N; ++v) {
        bool interdit = false;

        for (auto x : vl) if (x == v) interdit = true;
        for (auto x : vc) if (x == v) interdit = true;
        for (auto x : vb) if (x == v) interdit = true;

        if (!interdit)
            vs.push_back(v);
    }

    return vs;
}



void Grille::genererGrillePartielle(suint p)
{   // remise à zéro
    suint N = n*n ;
    for (suint i = 0; i < N; ++i)
        for (suint j = 0; j < N; ++j)
            (grille)[i][j] = 0;
    casesVides.clear();
    for (suint i = 0; i < N; ++i)
        for (suint j = 0; j < N; ++j)
            casesVides.push_back({i, j});

    suint nbRemplies = 0;
    while (nbRemplies < p && !casesVides.empty())
    {
        // choisir une case vide aléatoire
        suint k = rand() % casesVides.size();
        suint i = casesVides[k].first;
        suint j = casesVides[k].second;

        // valeurs admissibles
        vector<suint> admissibles = valeursAdmissibles(i, j);

        if (!admissibles.empty())
        {
            // choisir une valeur admissible aléatoire
            suint v = admissibles[rand() % admissibles.size()];
            (grille)[i][j] = v;
            nbRemplies++;
            

            // retirer la case de casesVides
            casesVides.erase(casesVides.begin() + k);
        }
        else
        {
            // impossible de remplir cette case → on l'abandonne
            casesVides.erase(casesVides.begin() + k);
        }
    }
}

void Grille::afficher() const
{
    int N = n * n;

    for (int i = 0; i < N; ++i) {

        // Séparation horizontale entre blocs
        if (i % n == 0) {
            for (suint k = 0; k < N * 2 + n + 1; ++k)
                std::cout << "-";
            std::cout << '\n';
        }

        for (int j = 0; j < N; ++j) {

            // Séparation verticale entre blocs
            if (j % n == 0)
                std::cout << "| ";

            if ((grille)[i][j] == 0)
                std::cout << ". ";
            else
                std::cout << (grille)[i][j] << " ";
        }

        std::cout << "|\n";
    }

    // Dernière ligne
    for (suint k = 0; k < N * 2 + n + 1; ++k)
        std::cout << "-";
    std::cout << '\n';
}

