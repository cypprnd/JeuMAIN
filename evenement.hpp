// Librairies
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <vector>
#include <ctime>

// Jeux
#include "calcul_mental.hpp"
#include "jeu_memoire.hpp"
#include "pierre_feuille_ciseau.hpp"
#include "qcm.hpp"
#include "jump_game.hpp"

// Fonction
#include "afficher_txt.hpp"

// Structure
// #include "stats.hpp"

class Personnage;  // Déclaration anticipée
class Environnement;

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
        std::cout << "Événement générique : " << nom << " exécuté" << std::endl;
    }
};

class Controle : public Evenement {
public:
    Controle() : Evenement("Contrôle","Un examen pour évaluer vos compétences.") {}
    Controle(int nb) : Evenement("Contrôle","Un examen pour évaluer vos compétences."), num(nb) {}

    void executer(Stats& stats) override {
        std::cout << "Vous passez un contrôle.." << std::endl;
        
        int resultat; // Note aléatoire entre 0 et 20

        if(num == 1) resultat = calculMental(stats.difficulte);
        if(num == 2) resultat = jeu_memoire(stats.difficulte);
        if(num == 3) resultat = PFC();

        if(stats.note == -1){
            stats.note = resultat;
        }
        else{
            stats.note = (stats.note + resultat) / 2; // Moyenne pondérée
        }
        stats.energie -= 10;


        std::cout << "Vous avez obtenu " << resultat << "/20. Nouvelle note moyenne : " << stats.note << "/20." << std::endl;
        if (stats.energie <= 0) {
            stats.energie = 0;
            std::cout << "Attention, votre énergie est à 0." << std::endl;
        }
    }
private:
    int num;
};

class Partiel : public Evenement {
public:
    Partiel() : Evenement("Partiel","Un examen très très important pour évaluer vos compétences."), questions_faciles(create_questions("facile")), questions_moyennes(create_questions("moyen")), questions_difficiles(create_questions("difficile")){}

    void executer(Stats& stats) override {
        std::cout << "Vous passez un partiel..." << std::endl << std::endl;
        
        int resultat; // Note aléatoire entre 0 et 20

        resultat = qcm(stats.difficulte, questions_faciles, questions_moyennes, questions_difficiles);

        if(stats.note == -1){
            stats.note = resultat;
        }
        else{
            stats.note = (3*stats.note + 2*resultat) /5; // le partiel compte beaucoup dans la moyenne
        }
        stats.energie -= 20;

        std::cout << "Vous avez obtenu " << resultat << "/20." << std::endl << "Nouvelle note moyenne : " << stats.note << "/20." << std::endl;
        if (stats.energie <= 0) {
            stats.energie = 0;
            std::cout << "Attention, votre énergie est à 0." << std::endl;
        }
    }
private:
    vector<pair<string, string>> questions_faciles;
    vector<pair<string, string>> questions_moyennes;
    vector<pair<string, string>> questions_difficiles;
};

class WEC : public Evenement { // A faire
public:
    WEC() : Evenement("WEC", "description ") {}

    void executer(Stats& stats) override {
    
    }

};

class TIS : public Evenement {
public:
    TIS() : Evenement("TIS", "Vous participez au tournoi inter-spécialités") {}

    void executer(Stats& stats) override {
        // jumpGame(stats);
    }

};

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Rentree : public Evenement {
public:
    Rentree(const std::string& nom, const std::string& description): Evenement(nom, description){}

    void executer(Stats& stats) override {}

    virtual ~Rentree() {}
};

class RentreePremiereAnnee : public Rentree {
public:
    RentreePremiereAnnee(const std::string& nom, const std::string& description): Rentree(nom, description) {}

    // mettre en paramètre Tannier et Yves

    void executer(Stats& stats) override {
        (void)system("clear");

        afficherFichier("jussieu_ascii.txt");
        sleep(4);
        (void)system("clear");

        afficherFichier("bienvenue.txt");
        sleep(5);
        (void)system("clear");

        afficherFichier("logo_polytech.txt");
        sleep(3);
        (void)system("clear");

        afficherFichier("aujourd'hui.txt");
        sleep(5);
        (void)system("clear");

        afficherFichier("meilleur_spe.txt");
        sleep(5);
        (void)system("clear");

        afficherFichier("main.txt");
        sleep(3);
        (void)system("clear");

        // Aujourd'hui c'est la rentrée, c'est partie

        // Première Interaction

        std::cout << "Vous voyez un professeur et un élève. Que voulez-vous faire ?" << std::endl;
        std::cout << "1. Parler au professeur" << std::endl;
        std::cout << "2. Parler à un élève" << std::endl;
        std::cout << "3. Faire la personne mystérieuse" << std::endl;

        int choix;
        std::cout << "Quelle est votre choix (1, 2 ou 3): ";
        std::cin >> choix;
        
        if (choix == 1) {
            // Tannier.parler();
        }

        if (choix == 2) {
            // Yves.parler();
        }

        if (choix == 3) {
            std::cout << "Vous avez parler à personne durant la rentrée. " << std::endl << std::endl;
            sleep(4);
            std::cout << "Aller, c'est parti !!!" << std::endl << std::endl;
            sleep(4);
            std::cout << "Demain les cours commence, attention il peut y avoir des controles surprises." << std::endl << std::endl;
            sleep(4);
            std::cout << "Bonne chance" << std::endl << std::endl << std::endl << std::endl;
            sleep(4);
        }

        // Aller c'est parti, bonne chance
    }
};

class AutreRentree : public Rentree {
private:
    int anneeEtudes;

public:
    AutreRentree(const std::string& nom, const std::string& description, int annee): Rentree(nom, description), anneeEtudes(annee) {}

    void executer(Stats& stats) override {
        afficherFichier("jussieu_ascii.txt");
        sleep(2);
        (void)system("clear");

        afficherFichier("n_annee.txt");
        sleep(2);
        (void)system("clear");

        // Choix entre Tannier, Yves, faire la personne mistérieuse

        // Aller c'est parti, bonne chance
    }
};


//On gagne de la revision mais perd un peu d'énergie
class Reviser : public Evenement {
    public:
        Reviser () : Evenement("Reviser","Vous avez decider de réviser." ) {}
    
    void executer(Stats& stats) override {
        std::cout << getDescription() << std::endl;
        stats.energie -= 5;
        stats.revision += 10;
        if(stats.energie < 0) stats.energie = 0;
        if(stats.revision > 100) stats.revision = 100;
        std::cout << "Vous gagnez " << 10 << " en révision mais perdez " << 5 << " en enérgie." << std::endl << std::endl;
        std::cout << "Vos nouvelles statistiques :" << std::endl << std::endl;
        stats.afficher();
        std::cout << std::endl << std::endl;
    }
};


//on gagne en réputation mais perd beaucoup en énérgie
class Sortir : public Evenement {
    public:
        Sortir () : Evenement("Sortir", "Vous avez decider de sortir.") {}
    
    void executer(Stats& stats) override {
        std::cout << getDescription() << std::endl;
        stats.energie -= 5;
        stats.reputation += 10;
        if(stats.energie < 0) stats.energie = 0;
        if(stats.reputation > 100) stats.reputation = 100;
        std::cout << "Vous gagnez " << 10 << " en réputation mais perdez " << 5 << " en enérgie." << std::endl << std::endl;
        std::cout << "Vos nouvelles statistiques :" << std::endl << std::endl;
        stats.afficher();
        std::cout << std::endl << std::endl;
    }
};

//On fait un jeu
class Ski : public Evenement {
    public:
        Ski() : Evenement("Ski", "Vous partez au ski avec Polytech.") {}
    
    void executer(Stats& stats) override {

    }
}; 

class Repos : public Evenement {
    public:
        Repos() : Evenement("Repos", "Je fais rien, je me repose") {}
    
    void executer(Stats& stats) override {
        std::cout << getDescription() << std::endl;
        stats.energie += 5;
        if(stats.energie > 100) stats.energie = 100;
        std::cout<< "Vous gagnez " << 5 << " en énergie." << std::endl << std::endl;
        std::cout << "Vos nouvelles statistiques :" << std::endl << std::endl;
        stats.afficher();
        std::cout << std::endl << std::endl;

    }
}; 


//C'est les vacances, on gagne en energie
class Vacances : public Evenement {
    public:
        Vacances() : Evenement("Vacances", "C'est les vacances !") {}
    
        void executer(Stats& stats) override {
            std::cout << getDescription() << std::endl;
            stats.energie += 20;
            if(stats.energie > 100) stats.energie = 100;
            std::cout << "Vous avez gagné plein d'enérgie." << std::endl;
            std::cout << "Vous gagnez "<< 20 << " en enérgie." << std::endl << std::endl;
            std::cout << "Vos nouvelles statistiques :" << std::endl << std::endl;
            stats.afficher();
            std::cout << std::endl << std::endl;
        }
}; 

class Rencontre : public Evenement {
    public:
        Rencontre(Personnage perso) : Evenement("Rencontre", "Tu tombes sur quelqu'un que tu connais"), personne(perso) {}

        void executer(Stats& stats) override {
            personne.parler();
            std::cout << "Vos nouvelles statistiques :" << std::endl << std::endl;
            stats.afficher();
            std::cout << std::endl << std::endl;
        }

    private:
        Personnage personne;
};
