#include "Polytech.hpp"

class Personnage : public Polytech {
protected:
    float note;  // La note de l'étudiant
    int energie;  // L'énergie actuelle de l'étudiant
    std::string reputation;  // La réputation du personnage
public:
    Personnage() : note(0), energie(100), reputation("neutre") {}
    virtual void afficher() override {
        std::cout << "Note : " << note << " Energie : " << energie << " Réputation : " << reputation << std::endl;
    }
    
    void modifierNote(float mod) {
        note += mod;
    }
    
    void modifierEnergie(int mod) {
        energie += mod;
    }
    
    void modifierReputation(std::string rep) {
        reputation = rep;
    }
};

class Nous : public Personnage {
public:
    Nous() : Personnage() {
        // Initialiser des caractéristiques spécifiques à l'étudiant joueur
        note = 75.0;  // Exemple de note initiale
        energie = 100;
        reputation = "étudiant sérieux";
    }
    void afficher() override {
        std::cout << "Bienvenue, étudiant!" << std::endl;
        Personnage::afficher();  // Appel de la méthode de la classe de base
    }
};

class Eleve : public Personnage {
public:
    Eleve() : Personnage() {
        note = 80.0;  // Exemple de note
        energie = 100;
        reputation = "étudiant moyen";
    }
};

class NPC : public Personnage {
public:
    NPC() : Personnage() {
        reputation = "inconnue";  // Réputation de base pour les NPCs
    }
};

class Prof : public NPC {
public:
    Prof() : NPC() {
        reputation = "professeur strict";
    }
};

class Yves : public NPC {
public:
    Yves() : NPC() {
        reputation = "personnage clé de l'histoire";
    }
    void action() {
        // Action spécifique d'Yves, par exemple sortir du cadre habituel
        std::cout << "Yves te sort de ta routine!" << std::endl;
    }
};

