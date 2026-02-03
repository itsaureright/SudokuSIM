#include "grille.hpp"

#include <cmath>
#include <algorithm> // Pour std::find
using suint = unsigned int ;

vector<suint> Grille::valeursAdmissibles(suint i, suint j) {
    // 1. On vide nos vecteurs de travail
    vl.clear(); vc.clear(); vb.clear(); vs.clear();

    // 2. Récupérer les valeurs présentes sur la ligne i et la colonne j
    for (suint k = 0; k < n; ++k) {
        if ((grille)[i][k] != 0) vl.push_back((grille)[i][k]);
        if ((grille)[k][j] != 0) vc.push_back((grille)[k][j]);
    }

    // 3. Récupérer les valeurs du bloc
    suint tailleBloc = sqrt(n);
    suint debutI = (i / tailleBloc) * tailleBloc;
    suint debutJ = (j / tailleBloc) * tailleBloc;

    for (suint r = debutI; r < debutI + tailleBloc; ++r) {
        for (suint c = debutJ; c < debutJ + tailleBloc; ++c) {
            if ((grille)[r][c] != 0) vb.push_back((grille)[r][c]);
        }
    }

    // 4. Déterminer les valeurs admissibles (ce qui n'est ni dans vl, ni vc, ni vb)
    for (suint v = 1; v <= n; ++v) {
        bool interdit = false;
        
        // On vérifie si v est dans un des vecteurs de travail
        for(auto val : vl) if(val == v) interdit = true;
        if(!interdit) {
            for(auto val : vc) if(val == v) interdit = true;
        }
        if(!interdit) {
            for(auto val : vb) if(val == v) interdit = true;
        }

        if (!interdit) {
            vs.push_back(v);
        }
    }

    return vs; 
}


void Grille::genererGrillePartielle(suint p)
{   // remise à zéro
    for (suint i = 0; i < n; ++i)
        for (suint j = 0; j < n; ++j)
            (grille)[i][j] = 0;
    casesVides.clear();
    for (suint i = 0; i < n; ++i)
        for (suint j = 0; j < n; ++j)
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

