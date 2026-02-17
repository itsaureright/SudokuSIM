#pragma once 
#include <iostream>
#include <vector>
#include <complex>
#include "grille.hpp"
#include <list>
using namespace std ;
using suint = unsigned int ;
#include <SFML/Graphics.hpp>

class Sudoku
{ public :
    int ordre=0; // ordre du Sudoku
    int nbcase=0; // nombre de case à initialiser
    bool allSol=false; // recherche de toutes les solutions si true
    bool uniqueSol=false; // pour le test d’unicité
    void preparerGrilleUnique(); //Génère une grille unique
    Grille grille_ini ; // grille initiale
    list<Grille> grille_sol ; // liste des grilles solutions
    void jouer();
    void jouerGraphique();
    Sudoku(int ordre, int nbcase, bool allSol, bool uniqueSol) ; 
    void Solve() ;  // Pour résoudre la grille
    bool isValid(const Grille& g, int ligne, int col, int val);  // Vérifie que le placement d'un chiffre est ok
    bool solveRec(Grille& g, vector<pair<suint,suint>>& cases, size_t idx);
    bool isValidDiag(const Grille& g, int ligne, int col, int val);
private:   
    std::pair<int,int> blocCoords(int ligne, int col) const; // Coordonnées des blocs
};

//Constructeurs

inline Sudoku::Sudoku(int ordre, int nbcase, bool allSol, bool uniqueSol): ordre(ordre), nbcase(nbcase), allSol(allSol), uniqueSol(uniqueSol),grille_ini(ordre){}

//Fonctions


//coordonnées des Blocs 

inline pair<int,int> Sudoku::blocCoords(int ligne, int col) const { 
    int n = ordre;
    int blocL = (ligne / n) * n; 
    int blocC = (col / n) * n; 
    return {blocL, blocC}; }


//Cases valides pour le Sudoku Classique

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


//Cases valides pour le Sudoku Diagonal

inline bool Sudoku::isValidDiag(const Grille& g, int ligne, int col, int val){
    suint N = g.n * g.n ;
    bool ok = isValid(g, ligne, col, val);
    if(!ok) {
        return false;
    }
    else{
        //diag directe
        if(ligne == col){
            for(int i = 0; i<N;++i){
                if (g.grille[i][i]==val){
                    return false;
                }
            }
        }
        //diag indirecte
        if( ligne+col+1 == N){
            for(int i = 0; i<N;++i){
                if (g.grille[i][N-i-1]==val){
                    return false; }
                }
        }
    }
}

// Pour résoudre

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



inline void Sudoku::jouer()
{
    setenv("DISPLAY", ":0", 1);
    Grille g = grille_ini;
    suint N = ordre * ordre;
    
    while (true)
    {
        g.afficher();

        cout << "\nEntre ligne colonne valeur (ex: 1 3 5)\n";
        cout << "Tape 0 0 0 pour quitter.\n";

        int ligne, col, val;
        if (!(cin >> ligne >> col >> val))
{
    cout << "Entree invalide ! Tape trois nombres.\n";
    cin.clear();                // enlève l'état d'erreur
    cin.ignore(10000, '\n');    // vide le buffer
    continue;
}


        if (ligne == 0 && col == 0 && val == 0)
        {
            cout << "Fin du jeu.\n";
            break;
        }

        // Ajustement car utilisateur pense en base 1
        ligne--;
        col--;

        if (ligne < 0 || ligne >= N || col < 0 || col >= N)
        {
            cout << "Coordonnees invalides !\n";
            continue;
        }

        if (grille_ini.grille[ligne][col] != 0)
        {
            cout << "Case deja remplie !\n";
            continue;
        }

        if (val < 0 || val > N)
        {
            cout << "Valeur invalide !\n";
            continue;
        }

        if (isValid(g, ligne, col, val))
        {
            g.grille[ligne][col] = val;
        }
        else
        {
            cout << "Coup invalide !\n";
        }

        // Vérifier si grille complète
        bool complete = true;
        for (suint i = 0; i < N; ++i)
            for (suint j = 0; j < N; ++j)
                if (g.grille[i][j] == 0)
                    complete = false;

        if (complete)
        {
            cout << "\nBravo ! Sudoku termine !\n";
            g.afficher();
            break;
        }
    }
}



///Interface graphique :

inline void Sudoku::jouerGraphique()
{
    Grille g = grille_ini;
    suint N = ordre * ordre;

    const int tailleCase = 60;
    const int tailleFenetre = N * tailleCase;

    sf::RenderWindow window(
        sf::VideoMode(tailleFenetre, tailleFenetre),
        "Sudoku"
    );

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    {
        std::cout << "Erreur chargement police\n";
        return;
    }

    int selectionL = -1;
    int selectionC = -1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // CLIC SOURIS
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int x = event.mouseButton.x / tailleCase;
                int y = event.mouseButton.y / tailleCase;

                if (x < N && y < N)
                {
                    selectionL = y;
                    selectionC = x;
                }
            }

            // CLAVIER
            if (event.type == sf::Event::KeyPressed && selectionL != -1 && selectionC != -1)
{
    int val = 0;

    switch(event.key.code)
    {
        // Clavier principal
        case sf::Keyboard::Num1: val = 1; break;
        case sf::Keyboard::Num2: val = 2; break;
        case sf::Keyboard::Num3: val = 3; break;
        case sf::Keyboard::Num4: val = 4; cout<<"OK" ; break;
        case sf::Keyboard::Num5: val = 5; break;
        case sf::Keyboard::Num6: val = 6; break;
        case sf::Keyboard::Num7: val = 7; break;
        case sf::Keyboard::Num8: val = 8; break;
        case sf::Keyboard::Num9: val = 9; break;

        // Pavé numérique
        case sf::Keyboard::Numpad1: val = 1; break;
        case sf::Keyboard::Numpad2: val = 2; break;
        case sf::Keyboard::Numpad3: val = 3; break;
        case sf::Keyboard::Numpad4: val = 4; break;
        case sf::Keyboard::Numpad5: val = 5; break;
        case sf::Keyboard::Numpad6: val = 6; break;
        case sf::Keyboard::Numpad7: val = 7; break;
        case sf::Keyboard::Numpad8: val = 8; break;
        case sf::Keyboard::Numpad9: val = 9; break;

        case 51: val = 4; break;
        
        default: cout << event.key.code ;
    }

    // Mettre la valeur si la case était vide
    if (val != 0 && grille_ini.grille[selectionL][selectionC] == 0)
        g.grille[selectionL][selectionC] = val;

    // Effacer avec Backspace
    if (event.key.code == sf::Keyboard::BackSpace)
    {
        if (grille_ini.grille[selectionL][selectionC] == 0)
            g.grille[selectionL][selectionC] = 0;
    }
}
        }
        

        window.clear(sf::Color::White);

        // Dessiner la grille
        for (suint i = 0; i < N; ++i)
        {
            for (suint j = 0; j < N; ++j)
            {
                sf::RectangleShape caseRect(
                    sf::Vector2f(tailleCase, tailleCase)
                );

                caseRect.setPosition(j * tailleCase, i * tailleCase);
                caseRect.setFillColor(sf::Color::White);
                caseRect.setOutlineColor(sf::Color::Black);
                caseRect.setOutlineThickness(1);

                // surbrillance sélection
                if (i == selectionL && j == selectionC)
                    caseRect.setFillColor(sf::Color(220, 220, 250));

                window.draw(caseRect);

                if (g.grille[i][j] != 0)
                {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(std::to_string(g.grille[i][j]));
                    text.setCharacterSize(24);
                    text.setFillColor(
                        grille_ini.grille[i][j] != 0 ?
                        sf::Color::Black :
                        sf::Color::Blue
                    );

                    text.setPosition(
                        j * tailleCase + tailleCase / 3,
                        i * tailleCase + tailleCase / 5
                    );

                    window.draw(text);
                }
            }
        }

        // Lignes épaisses pour blocs
        for (suint i = 0; i <= N; i += ordre)
        {
            sf::RectangleShape ligne(
                sf::Vector2f(tailleFenetre, 3)
            );
            ligne.setPosition(0, i * tailleCase);
            ligne.setFillColor(sf::Color::Black);
            window.draw(ligne);

            sf::RectangleShape col(
                sf::Vector2f(3, tailleFenetre)
            );
            col.setPosition(i * tailleCase, 0);
            col.setFillColor(sf::Color::Black);
            window.draw(col);
        }

        window.display();
    }
}