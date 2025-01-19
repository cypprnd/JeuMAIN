// Librairies
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <vector>
#include <ctime>

// Jeux
#include "../JeuMAIN/mini_jeu/calcul_mental.hpp"
#include "../JeuMAIN/mini_jeu/jeu_memoire.hpp"
#include "../JeuMAIN/mini_jeu/pierre_feuille_ciseau.hpp"
#include "../JeuMAIN/mini_jeu/qcm.hpp"
#include "../JeuMAIN/mini_jeu/ski/ski.cc"

// Fonction
#include "afficher_txt.hpp"
#include "../JeuMAIN/mini_jeu/saisie_int.hpp"

#include "personnage.hpp"

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

    ~Controle() override = default;

    void executer(Stats& stats) override {
        std::cout << "Vous passez un contrôle.." << std::endl;
        
        int resultat; // Note aléatoire entre 0 et 20

        if(num == 1) resultat = calculMental(stats.difficulte);
        if(num == 2) resultat = jeu_memoire(stats.difficulte);
        if(num == 3) resultat = PFC();

        if(stats.note == -1){
            stats.nb_note += 1; 
            stats.somme_note += resultat;
        }
        else{
            stats.nb_note += 1; 
            stats.somme_note += resultat;
        }
        stats.energie -= 10;

        stats.maj_note();
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
            stats.nb_note += 3; 
            stats.somme_note += 3*resultat;
        }
        else{
            stats.nb_note += 3; 
            stats.somme_note += 3*resultat;
        }
        stats.energie -= 20;

        stats.maj_note();
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

class Projet : public Evenement {
public:
    Projet() : Evenement("Projet","Un projet important pour évaluer vos compétences et votre investissement."){}

    void executer(Stats& stats) override {
        
        int resultat; // Note aléatoire entre 0 et 20
        resultat = (stats.reputation + stats.revision - 10)*2/10;
        if(resultat > 20) resultat = 20;

        if(stats.reputation + stats.revision -10 <= 60){
            std::cout << "Vous n'avez pas assez travailler et vous devez plus vous sociabiliser pour avoir une meilleure note au projet" << std::endl << std::endl;
        }
        else{
            std::cout << "Vous avez bien travailler et vous vous êtes sociabilisé(e) donc vous obtenez une bonne note au projet." << std::endl << std::endl;
        }

        if(stats.note == -1){
            stats.nb_note += 2; 
            stats.somme_note += 2*resultat;
        }
        else{
            stats.nb_note += 2; 
            stats.somme_note += 2*resultat;
        }
        stats.energie -= 20;
        if(stats.energie < 0) stats.energie = 0;

        stats.maj_note();
        std::cout << "Vous avez obtenu " << resultat << "/20." << std::endl << "Nouvelle note moyenne : " << stats.note << "/20." << std::endl;
        if (stats.energie <= 0) {
            stats.energie = 0;
            std::cout << "Attention, votre énergie est à 0." << std::endl;
        }
    }
};

class Rentree : public Evenement {
public:
    Rentree(const std::string& nom, const std::string& description, Personnage& perso1, Personnage& perso2): Evenement(nom, description), personne1(perso1), personne2(perso2) {}

    void executer(Stats& stats) override {}

    virtual ~Rentree() {}
protected:
    Personnage& personne1;
    Personnage& personne2;
};

class RentreePremiereAnnee : public Rentree {
public:
    RentreePremiereAnnee(const std::string& nom, const std::string& description, Personnage& perso1, Personnage& perso2): Rentree(nom, description, perso1, perso2) {}

    void executer(Stats& stats) override {
        (void)system("clear");

        afficherFichier("../JeuMAIN/affichage/jussieu_ascii.txt");
        sleep(3);
        (void)system("clear");

        afficherFichier("../JeuMAIN/affichage/bienvenue.txt");
        sleep(4);
        (void)system("clear");

        afficherFichier("../JeuMAIN/affichage/logo_polytech.txt");
        sleep(3);
        (void)system("clear");

        afficherFichier("../JeuMAIN/affichage/aujourd'hui.txt");
        sleep(4);
        (void)system("clear");

        afficherFichier("../JeuMAIN/affichage/meilleur_spe.txt");
        sleep(4);
        (void)system("clear");

        afficherFichier("../JeuMAIN/affichage/main.txt");
        sleep(3);
        (void)system("clear");

        // Première Interaction

        std::cout << "Vous voyez un professeur et un élève. Que voulez-vous faire ?" << std::endl;
        std::cout << "1. Parler au professeur" << std::endl;
        std::cout << "2. Parler à un élève" << std::endl;
        std::cout << "3. Faire la personne mystérieuse" << std::endl;

        int choix;
        std::cout << "Quelle est votre choix (1, 2 ou 3): ";
        std::cin >> choix;
        
        if (choix == 1) {
            std::cout << personne1;
            stats.reputation += 10;
        }

        if (choix == 2) {
            std::cout << personne2;
            stats.reputation += 5;
        }

        if (choix == 3) {
            std::cout << "Vous n'avez parler à personne durant la rentrée. " << std::endl << std::endl;
            sleep(2);
        }

        if(stats.reputation > 100) stats.reputation = 100;
        std::cout << "Vos nouvelles statistiques :" << std::endl << std::endl;
        stats.afficher();
        std::cout << std::endl << std::endl;

        std::cout << "Allez, c'est parti !!!" << std::endl << std::endl;
        sleep(2);
        std::cout << "Demain les cours commencent, attention il peut y avoir des controles surprises." << std::endl << std::endl;
        sleep(2);
        std::cout << "Bonne chance" << std::endl << std::endl << std::endl << std::endl;
        sleep(2);
    }
};

class AutreRentree : public Rentree {
private:
    int anneeEtudes;

public:
    AutreRentree(const std::string& nom, const std::string& description, int annee, Personnage& perso1, Personnage& perso2): Rentree(nom, description, perso1, perso2), anneeEtudes(annee) {}

    void executer(Stats& stats) override {
        stats.reset();
        (void)system("clear");
        afficherFichier("../JeuMAIN/affichage/jussieu_ascii.txt");
        sleep(2);
        (void)system("clear");

        afficherFichier("../JeuMAIN/affichage/n_annee.txt");
        sleep(2);
        (void)system("clear");

        std::cout << "Vous voyez un professeur et un élève. Que voulez-vous faire ?" << std::endl;
        std::cout << "1. Parler au professeur" << std::endl;
        std::cout << "2. Parler à un élève" << std::endl;
        std::cout << "3. Faire la personne mystérieuse" << std::endl;

        int choix;
        std::cout << "Quelle est votre choix (1, 2 ou 3): ";
        std::cin >> choix;
        
        if (choix == 1) {
            personne1.parler(stats);
            stats.reputation += 10;
        }

        if (choix == 2) {
            personne2.parler(stats);
            stats.reputation += 5;

        }

        if (choix == 3) {
            std::cout << "Vous avez parler à personne durant la rentrée. " << std::endl << std::endl;
            sleep(2);
        }

        if(stats.reputation > 100) stats.reputation = 100;
        std::cout << "Vos nouvelles statistiques :" << std::endl << std::endl;
        stats.afficher();
        std::cout << std::endl << std::endl;

        std::cout << "Aller, c'est parti !!!" << std::endl << std::endl;
        sleep(2);
        std::cout << "Demain les cours commencent, attention il peut y avoir des controles surprises." << std::endl << std::endl;
        sleep(2);
        std::cout << "Bonne chance" << std::endl << std::endl << std::endl << std::endl;
        sleep(2);
    }
};


//On gagne de la revision mais perd un peu d'énergie
class Reviser : public Evenement {
    public:
        Reviser() : Evenement("Reviser","Vous avez decider de réviser." ) {}
    
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
        jeu_ski();
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
    Rencontre(Personnage& perso)
        : Evenement("Rencontre " + perso.getNom(), "Tu tombes sur quelqu'un que tu connais"), personne(perso) {}

    void executer(Stats& stats) override {
        std::cout << endl << personne << endl << endl << endl;
        int nb_rencontre = personne.get_rencontre();
        stats += 7 + nb_rencontre;
        std::cout << "Vos nouvelles statistiques :" << std::endl << std::endl;
        stats.afficher();
        std::cout << std::endl << std::endl;
    }

private:
    Personnage& personne; 
};

