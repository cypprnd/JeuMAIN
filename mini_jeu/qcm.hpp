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
      {"Si deux signaux f(t) et g(t) sont périodiques, leur convolution dans le domaine temporel sera aussi périodique", "vrai"},
      {"Le théorème de dualité forte stipule que, sous certaines conditions, la solution optimale du problème primal est égale à la solution optimale du problème dual.", "vrai"},
      {"Dans une étude statistique, une hypothèse nulle est souvent formulée pour exprimer l'absence d'effet ou de différence.", "vrai"},
      {"L'erreur de type I est commise lorsque l'on rejette l'hypothèse nulle alors qu'elle est vraie.", "vrai"},
      {"Un byte est composé de 8 bits ?", "vrai"},
      {"Tous les problèmes NP-complets peuvent être résolus en temps polynomial", "faux"},
      {"Une classe en C++ est un modèle qui définit les attributs et les méthodes d'un objet.", "vrai"},
      {"Les membres privés d'une classe peuvent être accédés directement depuis l'extérieur de la classe.", "faux"},
      {"OpenMP est un modèle de programmation parallèle conçu pour les systèmes à mémoire distribuée, permettant la communication entre différents processus.", "faux"},
      {"Dans OpenMP, les sections de code parallèles sont définies à l’aide de la directive #pragma parallel", "faux"},
      {"Dans MPI, la fonction MPI_Bcast permet de diffuser un message à tous les processus d'un communicateur.", "vrai"},
      {"La MAIN est la meilleure spécialité ?", "vrai"}
    };
  } else if (niveau_difficulte == "moyen") {
    return {
      {"La convolution dans le domaine temporel est une opération linéaire ?", "vrai"},
      {"Un langage de programmation compilé est traduit directement en code machine ?", "vrai"},
      {"La convolution de deux signaux de même durée ne change pas la durée du signal résultant.", "faux"},
      {"Un problème est dit NP-complet s'il est à la fois dans NP et qu'il est aussi dur que tous les autres problèmes dans NP", "vrai"},
      {"Un problème est dans la classe NP si et seulement si une machine de Turing non déterministe peut résoudre ce problème en temps polynomial.", "vrai"},
      {"Le simplexe est une méthode d'optimisation qui cherche à se déplacer à travers les sommets d'un polytope pour atteindre la solution optimale.", "vrai"},
      {"La méthode du simplexe peut être utilisée pour résoudre des problèmes de programmation linéaire avec des variables non continues.", "faux"},
      {"L'estimation par maximum de vraisemblance (EMV) consiste à trouver les paramètres du modèle qui minimisent la vraisemblance des données observées.", "faux"},
      {"Une estimation ponctuelle est toujours plus précise qu'un intervalle de confiance, car elle ne donne qu'une seule valeur.", "faux"},
      {"L'encapsulation en C++ permet de protéger les données d'une classe en les rendant accessibles uniquement via des méthodes publiques.", "vrai"},
      {"En C++, il est obligatoire d'utiliser des pointeurs ou des références pour passer des objets à une fonction.", "faux"},
      {"La vectorisation consiste à exécuter plusieurs instructions simultanément sur différentes données à l'aide de processeurs vectoriels ou de jeux d'instructions SIMD.", "vrai"},
      {"Un sous-ensemble fermé d'un espace de Hilbert est toujours un espace de Hilbert.", "vrai"},
      {"Tout sous-ensemble fermé et convexe d'un espace de Hilbert est un espace de Hilbert.", "faux"},
      {"Une suite de Cauchy dans un espace métrique complet converge toujours.", "vrai"}
    };
  } else if (niveau_difficulte == "difficile") {
    return {
      {"L'intégrale d'une fonction continue est toujours définie ?", "faux"},
      {"Il existe une machine de Turing qui peut déterminer si une autre machine de Turing s'arrêtera sur une entrée donnée, pour tous les programmes et entrées.", "faux"},
      {"Le dual d'un problème de programmation linéaire offre souvent une méthode plus rapide pour trouver une solution optimale que le problème primal.", "faux"},
      {"Le simplexe fonctionne en évaluant les points intérieurs du polytope de contraintes.", "faux"},
      {"Un intervalle de confiance à 95% signifie qu'il y a 95% de chance que l'intervalle contienne la vraie valeur du paramètre.", "faux"},
      {"L'intervalle de confiance pour un paramètre est basé sur la distribution de l'estimateur sous l'hypothèse que les données suivent une distribution normale.", "vrai"},
      {"Il est impossible de créer une instance d'une classe abstraite en C++.", "vrai"},
      {"Le mot-clé virtual dans une fonction membre d'une classe signifie que cette fonction peut être redéfinie uniquement dans une classe dérivée directe.", "faux"},
      {"Le polymorphisme en C++ permet d'utiliser des objets de classes dérivées comme s'ils étaient des objets de la classe de base.", "vrai"},
      {"MPI (Message Passing Interface) est une bibliothèque utilisée pour la programmation parallèle sur des systèmes à mémoire partagée", "faux"},
      {"Dans OpenMP, les variables locales sont partagées entre les threads d'un même bloc parallèle.", "faux"},
      {"La vectorisation dans les processeurs modernes utilise des instructions SIMD (Single Instruction, Multiple Data) pour traiter plusieurs données en parallèle avec une seule instruction.", "vrai"},
      {"Dans un espace topologique, l'ensemble vide et l'ensemble total sont toujours ouverts.", "vrai"},
      {"Tout espace métrique complet est un espace de Banach, mais pas nécessairement un espace de Hilbert.", "vrai"},
      {"L'adhérence d'un sous-ensemble fermé d'un espace topologique est un sous-ensemble ouvert.", "faux"},
      {"Le pruning peut être effectué avant la construction de l'arbre de décision", "faux"},
      {"Le pruning peut également être utilisé dans les réseaux de neurones pour supprimer des connexions entre les couches.", "vrai"},
      {"Nous avons la meilleure professeure de C++", "vrai"}
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
                questions_faciles.pop_back(); // Supprimer le dernier élément
            }
        }
        for(int i = 6; i < 9; i++){
            questions[i] = questions_moyennes.back();
            if (!questions_moyennes.empty()) {
                questions_moyennes.pop_back(); // Supprimer le dernier élément
            }
        }
        questions[9] = questions_difficiles.back();
        if (!questions_difficiles.empty()) {
            questions_difficiles.pop_back(); // Supprimer le dernier élément
        }
    } // Remplire questions en supprimant les éléments dans les tableaux
    else if(niveau_difficulte == "moyen"){
        for(int i = 0; i < 6; i++){
            questions[i] = questions_moyennes.back();
            if (!questions_moyennes.empty()) {
                questions_moyennes.pop_back(); // Supprimer le dernier élément
            }
        }
        for(int i = 6; i < 8; i++){
            questions[i] = questions_faciles.back();
            if (!questions_faciles.empty()) {
                questions_faciles.pop_back(); // Supprimer le dernier élément
            }
        }
        for(int i = 8; i < 10; i++){
            questions[i] = questions_difficiles.back();
            if (!questions_difficiles.empty()) {
                questions_difficiles.pop_back(); // Supprimer le dernier élément
            }
        }
    }
    else{
        for(int i = 0; i < 6; i++){
            questions[i] = questions_difficiles.back();
            if (!questions_difficiles.empty()) {
                questions_difficiles.pop_back(); // Supprimer le dernier élément
            }
        }
        for(int i = 6; i < 9; i++){
            questions[i] = questions_moyennes.back();
            if (!questions_moyennes.empty()) {
                questions_moyennes.pop_back(); // Supprimer le dernier élément
            }
        }
        questions[9] = questions_faciles.back();
        if (!questions_faciles.empty()) {
            questions_faciles.pop_back(); // Supprimer le dernier élément
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
    return 2*score;
}

