#include <iostream>
#include <cstdlib>
#include <string>

struct Stats {
    int note;     // Note de l'étudiant (0 à 20)
    int energie;  // Énergie restante (0 à 100)
    int reputation; // Réputation (0 à 100)
    int revision;

    int niveau;
    std::string difficulte;

    Stats() : note(-1), energie(100), reputation(50), revision(0) {
        niveau = energie + revision - 20;
        if(niveau >= 150) difficulte = "facile";
        else if(niveau < 150 && niveau > 75) difficulte = "moyen";
        else difficulte = "difficile";
    } // Initialisation par défaut

    void afficher() const {
        std::cout << "--- Voici vos statistiques ---" << std::endl;
        std::cout << "--- Note : " << (note == -1 ? "Indéfini" : std::to_string(note) + "/20") << std::endl;
        std::cout << "--- Énergie : " << energie << "/100" << std::endl;
        std::cout << "--- Réputation : " << reputation << "/100" << std::endl;
        std::cout << "------------------------------" << std::endl;
    }

    void maj_dif(){
        niveau = energie + revision - 20;
        if(niveau >= 150) difficulte = "facile";
        else if(niveau < 150 && niveau > 75) difficulte = "moyen";
        else difficulte = "difficile";
    }

};