#include <iostream>
#include <cstdlib>
#include <string>

struct Stats {
    int note;     // Note de l'étudiant (0 à 20)
    int energie;  // Énergie restante (0 à 100)
    int reputation; // Réputation (0 à 100)
    int revision;
    int somme_note;
    int nb_note;

    int niveau;
    std::string difficulte;

    Stats() : note(-1), energie(80), reputation(35), revision(0),somme_note(0), nb_note(0) {
        niveau = energie + revision - 10;
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

    void maj_note(){
        if(nb_note != 0) note = somme_note/nb_note;
        else note = -1;
    }

    void maj_dif(){
        niveau = energie + revision - 20;
        if(niveau >= 150) difficulte = "facile";
        else if(niveau < 150 && niveau > 75) difficulte = "moyen";
        else difficulte = "difficile";
    }

    void reset(){
        note = -1;
        nb_note = 0;
        somme_note = 0;
        if(energie < 80) energie = 80;
        revision -= 15;
        if(revision < 0) revision = 0;
        reputation -= 30;
        if(reputation < 0) revision = 0;
    }
};

Stats& operator+=(Stats& stats, int val) {
    stats.energie += val;
    stats.revision += val;
    stats.reputation += val;
    if(stats.energie > 100) stats.energie = 100;
    if(stats.revision > 100) stats.revision = 100;
    if(stats.reputation > 100) stats.reputation = 100;
    return stats;
}
