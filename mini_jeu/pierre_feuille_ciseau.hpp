#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "saisie_int.hpp"

using namespace std;

// Fonction pour convertir un choix en texte
string getChoice(int num) {
    if (num == 0) return "Pierre";
    if (num == 1) return "Feuille";
    return "Ciseaux";
}

// Fonction pour déterminer le gagnant d'une manche
int determineWinner(int player, int prof) {
    if (player == prof) return 0; // Égalité
    if ((player == 0 && prof == 2) || // Pierre bat Ciseaux
        (player == 1 && prof == 0) || // Papier bat Pierre
        (player == 2 && prof == 1))   // Ciseaux bat Papier
        return 1; // Joueur gagne
    return -1;    // Prof gagne
}

// Fonction principale pour jouer une partie
int PFC() {
    srand(time(0));
    int score = 0;
    int profScore = 0;

    cout << "1v1 contre le prof à Pierre Feuille Ciseaux" << endl;
    cout << "Premier a atteindre 5 points gagne." << endl;
    cout << "0: Pierre, 1: Feuille, 2: Ciseaux" << endl;
    sleep(5);

    while (score < 5 && profScore < 5) {
        int player, prof;

        cout << endl << "Votre choix (0: Pierre, 1: Feuille, 2: Ciseaux) : ";

        bool saisie = false;

        while (saisie == false) {
            saisie = saisirEntier(player);
        }

        // Validation de l'entrée utilisateur
        if (player < 0 || player > 2) {
            cout << "Choix invalide, reessayez." << endl;
            continue;
        }

        prof = rand() % 3; // Prof choisit au hasard

        cout << "Vous avez choisi : " << getChoice(player) << endl;
        cout << "Prof a choisi : " << getChoice(prof) << endl;

        // Déterminer le gagnant de la manche
        int result = determineWinner(player, prof);

        if (result == 1) {
            cout << "Vous gagnez cette manche !" << endl;
            score++;
        } else if (result == -1) {
            cout << "Prof gagne cette manche !" << endl;
            profScore++;
        } else {
            cout << "Egalite dans cette manche !" << endl;
        }

        // Afficher le score
        cout << "Score - Vous: " << score << " | Prof: " << profScore << endl << endl;
    }

    // Déterminer le vainqueur final
    if (score == 5){
        cout << endl << "Felicitations ! l'élève à dépasser le maitre" << endl << "Vous avez obtenu la note de 20/20 !" << endl;
        score = 20;
    }
    else
        cout << endl << "Vous n'avez pas fait le poids !" << endl << "Vous avez obtenu la note de " << score << "/20";
        
    return score;
}


