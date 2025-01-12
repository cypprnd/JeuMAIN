#pragma once
#include <iostream>
struct Stats {
    int note;     // Note de l'étudiant (0 à 20)
    int energie;  // Énergie restante (0 à 100)
    int reputation; // Réputation (0 à 100)
    int revision;

    Stats() : note(-1), energie(100), reputation(50), revision(0) {} // Initialisation par défaut

    void afficher() const {
        std::cout << "\n--- Voici vos statistiques ---\n";
        std::cout << "Note : " << (note == -1 ? "Indéfini" : std::to_string(note) + "/20") << "\n";
        std::cout << "Énergie : " << energie << "/100\n";
        std::cout << "Réputation : " << reputation << "/100\n";
        std::cout << "---------------------\n";
    }

};