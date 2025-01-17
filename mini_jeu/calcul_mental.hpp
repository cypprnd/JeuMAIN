#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono> // Pour le timer
#include <string>
#include <unistd.h>

#include "saisie_int.hpp"

using namespace std;
using namespace std::chrono;

/* Jeu de calcul mental
 * On donne une séquence de chiffres à mémoriser et on demande à l'utilisateur de la saisir
 * paramètre niveau qui prend les valeurs "faclie", "moyen" ou "difficile"
 * 
 */

int calculMental(string niveau) {
    srand(time(0));

    int nombreQuestions = 10; // Nombre de questions
    int score = 0; // Score de l'utilisateur
    const int delaiMax = 6; // Temps maximum pour répondre en secondes

    srand(static_cast<unsigned int>(time(0))); // Initialisation de la graine pour les nombres aléatoires

    cout << endl << "Bienvenue au controle de mathématiques !" << endl;    
    cout << "Vous allez répondre à " << nombreQuestions << " questions de calcul mental." << endl << endl;
    sleep(5);

    cout << "Vous avez " << delaiMax << " secondes pour répondre à chaque question." << endl << endl;
    sleep(3);
    cout << 3 << endl;
    sleep(1);
    cout << 2 << endl;
    sleep(1);
    cout << 1 << endl;
    sleep(1);
    cout << "C'est parti !!!!" << endl << endl;
    sleep(1);

    for (int i = 0; i < nombreQuestions; ++i) {
        int a, b, reponseUtilisateur, resultat;
        char operateur;

        // En fonction du niveau, choisir les bornes des nombres et l'opération
        if (niveau[0] == 'f') {
            a = rand() % 20 + 1; // Nombres entre 1 et 20
            b = rand() % 20 + 1;
            operateur = '+'; // Seulement des additions faciles
            resultat = a + b;
        } else if (niveau[0] == 'm') {
            a = rand() % 100 + 1; // Nombres entre 1 et 100
            b = rand() % 100 + 1;
            operateur = (rand() % 2 == 0) ? '+' : '-'; // Additions et soustractions
            resultat = (operateur == '+') ? a + b : a - b;
        } else if (niveau[0] == 'd') {
            a = rand() % 200 + 1; // Nombres entre 1 et 200
            b = rand() % 200 + 1;
            int choixOperateur = rand() % 3;
            if (choixOperateur == 0) {
                operateur = '+';
                resultat = a + b;
            } else if (choixOperateur == 1) {
                operateur = '-';
                resultat = a - b;
            } else {
                operateur = '*';
                b = rand() % 20 + 1; // Limiter le second opérande pour les multiplications
                resultat = a * b;
            }
        }

        // Poser la question
        cout << "Question " << i + 1 << ": " << a << " " << operateur << " " << b << " = ?" << endl;

        // Mesurer le temps de réponse
        auto debut = steady_clock::now();
        bool tempsEcoule = false;

        bool saisie = false;

        while (saisie == false) {
            saisie = saisirEntier(reponseUtilisateur);
            auto maintenant = steady_clock::now();
            auto duree = duration_cast<seconds>(maintenant - debut).count();
            if (duree > delaiMax) {
                tempsEcoule = true;
                break;
            }
        }
        // Vérifier la réponse
        if (tempsEcoule) {
            cout << "Temps écoulé ! La bonne réponse était " << resultat << "." << endl;
        } else if (reponseUtilisateur == resultat) {
            cout << "Bonne réponse !\n";
            ++score;
        } else {
            cout << "Faux. La bonne réponse était " << resultat << "." << endl;
        }
    }

    // Afficher le score final
    cout << endl << "Votre note est : " << score*2 << " / " << 20 << endl;

    // Évaluation du score
    if (score == nombreQuestions) {
        cout << "Félicitations ! Vous êtes un as du calcul mental !" << endl;
    } else if (score > nombreQuestions / 2) {
        cout << "Bon travail ! Continuez à vous entraîner.\n";
    } else {
        cout << "Vous pouvez faire mieux. Réessayez pour progresser !" << endl;
    }

    return 2*score;
}
