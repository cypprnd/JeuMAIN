#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include <unistd.h>

using namespace std;

bool check_answer(string answer, string correct_answer) {
  return answer == correct_answer;
}

vector<pair<string, string>> create_questions(string niveau_difficulte) {
  if (niveau_difficulte == "facile") {
    return {
      {"Le nombre 7 est un nombre premier ?", "vrai"},
      {"Un algorithme est une séquence d'instructions pour résoudre un problème ?", "vrai"},
      {"Le jeu Pac-Man est un jeu de plateforme ?", "faux"},
      {"La somme des angles d'un triangle est toujours égale à 180 degrés ?", "vrai"},
      {"Le système binaire utilise uniquement les chiffres 0 et 1 ?", "vrai"},
      {"Le jeu Tetris est un jeu de puzzle ?", "vrai"},
      {"Un byte est composé de 8 bits ?", "vrai"},
      {"Le jeu Pong est un jeu de sport ?", "faux"},
      {"Le jeu Pong est un jeu de sport ?", "faux"},
      {"Le jeu Pong est un jeu de sport ?", "faux"},
      {"Le jeu Pong est un jeu de sport ?", "faux"},
      {"Le jeu Pong est un jeu de sport ?", "faux"},
      {"Le jeu Pong est un jeu de sport ?", "faux"},
      {"Le jeu Pong est un jeu de sport ?", "faux"}
    };
  } else if (niveau_difficulte == "moyen") {
    return {
      {"La fonction exponentielle est croissante sur l'ensemble des réels ?", "vrai"},
      {"Un langage de programmation compilé est traduit directement en code machine ?", "vrai"},
      {"Le jeu Super Mario Bros est un jeu d'aventure ?", "vrai"},
      {"Le théorème de Pythagore permet de calculer l'hypoténuse d'un triangle rectangle ?", "vrai"},
      {"Un programme informatique est un ensemble d'instructions écrites dans un langage de programmation ?", "vrai"},
      {"Le jeu Zelda est un jeu de rôle ?", "vrai"},
      {"Une variable est un emplacement mémoire qui peut stocker une valeur ?", "vrai"},
      {"Une variable est un emplacement mémoire qui peut stocker une valeur ?", "vrai"},
      {"Une variable est un emplacement mémoire qui peut stocker une valeur ?", "vrai"},
      {"Une variable est un emplacement mémoire qui peut stocker une valeur ?", "vrai"},
      {"Une variable est un emplacement mémoire qui peut stocker une valeur ?", "vrai"},
      {"Une variable est un emplacement mémoire qui peut stocker une valeur ?", "vrai"},
      {"Une variable est un emplacement mémoire qui peut stocker une valeur ?", "vrai"},
      {"Une variable est un emplacement mémoire qui peut stocker une valeur ?", "vrai"},
      {"Le jeu Street Fighter est un jeu de combat ?", "vrai"}
    };
  } else if (niveau_difficulte == "difficile") {
    return {
      {"L'intégrale d'une fonction continue est toujours définie ?", "faux"},
      {"Un algorithme récursif est un algorithme qui s'appelle lui-même ?", "vrai"},
      {"Le jeu Grand Theft Auto est un jeu de simulation ?", "vrai"},
      {"Le théorème de Fermat-Wiles stipule qu'il n'existe pas de solutions entières à l'équation a^n + b^n = c^n pour n supérieur à 2 ?", "vrai"},
      {"Un langage de programmation interprété est traduit ligne par ligne lors de l'exécution ?", "vrai"},
      {"Le jeu Minecraft est un jeu en monde ouvert ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Une fonction est un bloc de code qui peut être appelé par son nom ?", "vrai"},
      {"Le jeu Fortnite est un jeu de tir à la première personne ?", "vrai"}
    };
  } else {
    return {};
  }
}

/* un qcm c'est 10 question
   niveau facile: 6 faciles, 3 moyennes et 1 difficile  
   niveau moyen: 6 moyennes, 2 faciles et 2 difficiles
   niveau difficile: 6 difficiles, 3 moyennes, 1 facile
*/

int qcm(string niveau_difficulte, vector<pair<string, string>> &questions_faciles, 
        vector<pair<string, string>> &questions_moyennes, vector<pair<string, string>> &questions_difficiles) {

    srand(time(0));
    shuffle(questions_faciles.begin(), questions_faciles.end(), default_random_engine(std::rand()));
    shuffle(questions_moyennes.begin(), questions_moyennes.end(), default_random_engine(std::rand()));
    shuffle(questions_difficiles.begin(), questions_difficiles.end(), default_random_engine(std::rand()));

    vector<pair<string, string>> questions(10);

    if(niveau_difficulte == "facile"){
        for(int i = 0; i < 6; i++){
            questions[i] = questions_faciles.back();
            if (!questions_faciles.empty()) {
                questions_faciles.pop_back(); // Supprimer le premier élément
            }
        }
        for(int i = 6; i < 9; i++){
            questions[i] = questions_moyennes.back();
            if (!questions_moyennes.empty()) {
                questions_moyennes.pop_back(); // Supprimer le premier élément
            }
        }
        questions[9] = questions_difficiles.back();
        if (!questions_difficiles.empty()) {
            questions_difficiles.pop_back(); // Supprimer le premier élément
        }
    } // Remplire questions en supprimant les éléments dans les tableaux
    else if(niveau_difficulte == "moyen"){
        for(int i = 0; i < 6; i++){
            questions[i] = questions_moyennes.back();
            if (!questions_moyennes.empty()) {
                questions_moyennes.pop_back(); // Supprimer le premier élément
            }
        }
        for(int i = 6; i < 8; i++){
            questions[i] = questions_faciles.back();
            if (!questions_faciles.empty()) {
                questions_faciles.pop_back(); // Supprimer le premier élément
            }
        }
        for(int i = 8; i < 10; i++){
            questions[i] = questions_difficiles.back();
            if (!questions_difficiles.empty()) {
                questions_difficiles.pop_back(); // Supprimer le premier élément
            }
        }
    }
    else{
        for(int i = 0; i < 6; i++){
            questions[i] = questions_difficiles.back();
            if (!questions_difficiles.empty()) {
                questions_difficiles.pop_back(); // Supprimer le premier élément
            }
        }
        for(int i = 6; i < 9; i++){
            questions[i] = questions_moyennes.back();
            if (!questions_moyennes.empty()) {
                questions_moyennes.pop_back(); // Supprimer le premier élément
            }
        }
        questions[9] = questions_faciles.back();
        if (!questions_faciles.empty()) {
            questions_faciles.pop_back(); // Supprimer le premier élément
        }
    }

    int score = 0;

    cout << endl << "C'est parti pour le partiel, l'examen le plus important du semestre !" << endl;
    cout << "Vous allez avoir une série de questions auquels vous allez devoir répondre par vrai ou faux" << endl;
    sleep(2);

    cout << endl << "C'est parti !!!!!" << endl << endl;

    for (auto question : questions) {
        cout << question.first << endl;
        string reponse;
        cin >> reponse;
        if (check_answer(reponse, question.second)) {
        cout << "Correct !" << endl << endl;
        score++;
        } else {
        cout << "Incorrect !" << endl << endl;
        }
    }
    cout << "Votre note est : " << score*2 << "/20" << endl;
    return score;
}

