#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>

#include "saisie_int.hpp"

using namespace std;

/* Jeu de mémoire
 * On donne une séquence de chiffres à mémoriser et on demande à l'utilisateur de la saisir
 * paramètre niveau qui prend les valeurs "faclie", "moyen" ou "difficile"
 * */

int jeu_memoire(string niveau) {
  srand(time(0));
  
  vector<int> seq;
  vector<int> seq_utilisateur;
  int nb;
  int nb_max;
  int score = 0;
  int i = 0;
  int n = 10;
  if(niveau[0] == 'f') nb_max = 10;
  else if(niveau[0] == 'm') nb_max = 20;
  else nb_max = 100;

  srand(time(0));

  // Génération de la séquence
  for (i = 0; i < n; i++) {
    nb = rand() % nb_max;
    seq.push_back(nb);
  }

  cout << "Bienvenue au controle de mémoire !" << endl;
  cout << "Il va falloir retenir une séquence de nombre" << endl;
  sleep(5);

  // Affichage de la séquence
  cout << "Voici la séquence à mémoriser : " << endl;
  for (i = 0; i < n; i++) {
    cout << seq[i] << " ";
  }
  cout << endl;

  sleep(20);
  (void)system("clear");

  // Saisie de la séquence par l'utilisateur
  cout << "Saisissez un nombre de la séquence : " << endl;
  for (i = 0; i < n; i++) {
    cout << "Saisissez le nombre n°" << i + 1 << ": ";
    bool saisie = false;
    while (saisie == false) {
      saisie = saisirEntier(nb);
    }
    seq_utilisateur.push_back(nb);
  }

  // Comparaison des séquences
  for (i = 0; i < n; i++) {
    if (seq[i] == seq_utilisateur[i]) {
      score++;
    }
  }

  cout << "Votre note est de : " << 2*score << "/" << 20 << endl;

  return 2*score;
}
