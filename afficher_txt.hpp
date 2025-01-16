#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void afficherFichier(const string& Fichier) {
    ifstream fichier(Fichier); // Ouvrir le fichier en mode lecture

    string ligne;
    while (getline(fichier, ligne)) { // Lire le fichier ligne par ligne
        cout << ligne << endl;   // Affiche chaque ligne
    }

    fichier.close(); // Fermer le fichier après lecture
}
