
#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>
#include "stats.hpp"
#include "personnage.hpp"
#include "jumpgame.cc"

class Evenement {
protected:
    std::string nom;
    std::string description;

public:
    Evenement(const std::string& nom, const std::string& description)
        : nom(nom), description(description) {}

    virtual ~Evenement() {}

    std::string getNom() const { return nom; }
    std::string getDescription() const {return description;}
    

    virtual void executer(Stats& stats) {
        std::cout << "Événement générique : " << nom << " exécuté.\n";
    }
};

class Controle : public Evenement {
public:
    Controle() : Evenement("Contrôle","Un examen important pour évaluer vos compétences.") {}

    void executer(Stats& stats) override {
        std::cout << "Vous passez un contrôle...\n";
        int resultat = rand() % 20 + stats.energie/50 ; // Note aléatoire entre 0 et 20
        if(stats.note == -1){
            stats.note = resultat;
        }
        else{
            stats.note = (stats.note + resultat) / 2; // Moyenne pondérée
        }
        stats.energie -= 20;

        std::cout << "Vous avez obtenu " << resultat << "/20. Nouvelle note moyenne : " << stats.note << "/20.\n";
        if (stats.energie <= 0) {
            std::cout << "Attention, votre énergie est à 0.\n";
        }
    }
};

class WEC : public Evenement {
public:
    WEC() : Evenement("WEC", "description ") {}

    void executer(Stats& stats) override {
    
    }

};

class TIS : public Evenement {
public:
    TIS() : Evenement("TIS", "Vous participez au tournoi inter-spécialités") {}

    void executer(Stats& stats) override {
        jumpGame(stats);
    
    }

};

class Rentree : public Evenement {
public:
    Rentree() : Evenement("Rentree","C'est la rentrée à Polytech Sorbonne ! Vous allez découvrir vos nouveaux camarades et professeurs.") {}

    void executer(Stats& stats) override {
        std::cout<<getDescription()<<std::endl;
        // Première image : personnage voyant la fac
        std::vector<std::string> imageFac = {
            "          __________",
            "         /          \\",
            "        /    FAC     \\",
            "       /______________\\",
            "           ||  ||",
            "           ||  ||",
            "           ||  ||",
            "           ||  ||",
            "          [==  ==]",
        };
        std::cout << "Vous arrivez devant la fac...\n";
        afficherImage(imageFac);
        attendreEntree();

        // Deuxième image : personnage entrant dans la fac
        std::vector<std::string> imageEntree = {
            "         _________________",
            "        |                 |",
            "        |    Bienvenue    |",
            "        |_________________|",
            "             ||    ||",
            "            [==    ==]",
            "             ||    ||",
            "             ||    ||",
        };
        std::cout << "Vous entrez dans la fac...\n";
        afficherImage(imageEntree);
        attendreEntree();

        // Interaction avec un personnage
        std::cout << "Vous voyez un professeur et un élève. Que voulez-vous faire ?\n";
        std::cout << "1. Parler au professeur\n";
        std::cout << "2. Parler à l'élève\n";
        std::cout << "Choix : ";
        int choix;
        std::cin >> choix;

        // Dialogue en fonction du choix
        if (choix == 1) {
            Professeur professeur("Mr Tannier");
            std::vector<std::string> imageProf = {
                "          _______",
                "         /       \\",
                "        / Prof    \\",
                "       /___________\\",
                "           ||  ||",
                "          (==  ==)",
                "           ||  ||",
            };
            afficherImage(imageProf);
            professeur.parler();
        } else if (choix == 2) {
            Eleve eleve("Alice");
            std::vector<std::string> imageEleve = {
                "          _______",
                "         /       \\",
                "        / Eleve   \\",
                "       /___________\\",
                "           ||  ||",
                "          (==  ==)",
                "           ||  ||",
            };
            afficherImage(imageEleve);
            eleve.parler();
        }else {
            std::cout << "Choix invalide. Vous ne parlez à personne.\n";
        }

        attendreEntree();
    }
};



//On gagne de la revision mais perd un peu d'énergie
class Reviser : public Evenement {
    public:
        Reviser () : Evenement("Reviser","Vous avez decider de réviser." ) {}
    
    void executer(Stats& stats) override {
        std::cout<<getDescription()<<std::endl;
        stats.energie-=5;
        stats.revision+=1;
        std::cout<<"Vous gagnez "<<stats.revision<<" en révision mais perdez "<<stats.energie<<" en enérgie.\n\n";
    }
};


//on gagne en réputation mais perd beaucoup en énérgie
class Sortir : public Evenement {
    public:
        Sortir () : Evenement("Sortir", "Vous avez decider de sortir.") {}
    
    void executer(Stats& stats) override {
        std::cout<<getDescription()<<std::endl;
        stats.energie-=5;
        stats.reputation+=10;
        std::cout<<"Vous gagnez "<<stats.reputation<<" en réputation mais perdez "<<stats.energie<<" en enérgie.\n\n";
    }
};

//On fait un jeu
class Ski : public Evenement {
    public:
        Ski () : Evenement("Reviser", "Vous partez au ski avec Polytech.") {}
    
    void executer(Stats& stats) override {

    }
}; 


//C'est les vacances, on gagne en energie
class Vacances : public Evenement {
    public:
        Vacances () : Evenement("Vacances", "C'est les vacances !") {}
    
    void executer(Stats& stats) override {
        std::cout<<getDescription()<<std::endl;
        stats.energie+=20;
        std::cout<<"Vous gagnez "<<stats.energie<<" en enérgie.\n\n";

    }
}; 


