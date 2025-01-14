#include <iostream>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// #include "evenement.hpp"
#include "stats.hpp"

// Fonction pour attendre une entrée de l'utilisateur
void attendreEntree() {
    //std::cout << "\nAppuyez sur Entrée pour continuer...";
    std::cin.ignore();
}

// Fonction pour afficher une image ASCII
void afficherImage(const std::vector<std::string>& image) {
    for (const std::string& ligne : image) {
        std::cout << ligne << "\n";
    }
}


class Personnage {
protected:
    std::string nom;
    std::string role;
    mutable int nb_rencontre;

public:
    Personnage(const std::string& nom, const std::string& role) : nom(nom), role(role), nb_rencontre(0) {}

    virtual void parler(Stats& stats) const {
        std::cout << "Bonjour je m'appelle " << nom << " (" << role << ")" << std::endl << std::endl;
    }

    std::string getNom() const { return nom; }
    std::string getRole() const { return role; }
};

class Professeur : public Personnage {
public:
    Professeur(const std::string& nom) : Personnage(nom, "Professeur") {}

    void parler(Stats& stats) const override {
        if (nb_rencontre == 0) {
            std::cout << "Bonjour, je suis " << nom << ", et je suis passionné(e) par l'enseignement ! N'hésite pas à venir discuter avec moi pour en savoir plus sur ta spécialité." << std::endl;
        } else if (nb_rencontre < 3) {
            std::cout << "Ravie de te revoir ! As-tu réfléchi à ta stratégie pour les révisions ? Je peux te donner quelques conseils." << std::endl;
        } else {
            std::cout << "Encore toi ? Haha, je vois que tu es motivé ! Continuons à travailler ensemble pour que tu sois au top." << std::endl;
        }
        nb_rencontre++;
        stats.reputation += 10;
        stats.revision += 10 + nb_rencontre;
        if(stats.reputation > 100) stats.reputation = 100;
        if(stats.revision > 100) stats.energie = 100;
    }
};

class Eleve : public Personnage {
public:
    Eleve(const std::string& nom) : Personnage(nom, "Élève") {}

    void parler(Stats& stats) const override {
        if(nb_rencontre == 0) std::cout << "Salut, comment ça va? Je m'appelle " << nom << std::endl << std::endl;
        else std::cout << "Commmen on se retrouve, c'est un plaisir de te voir" << std::endl << std::endl;

        nb_rencontre++;
        stats.reputation += 10;
        stats.energie += 10 + nb_rencontre;
        if(stats.reputation > 100) stats.reputation = 100;
        if(stats.energie > 100) stats.energie = 100;
        
    }
};

class Yves : public Eleve {
public:
    Yves() : Eleve("Yves") {}

    void parler(Stats& stats) const override {
        if (nb_rencontre == 0) {
            std::cout << "Salut, comment ça va ? Je m'appelle Yves, je suis brésilien (il ment) !" << std::endl;
        } else if(nb_rencontre == 1) {
            std::cout << "Oh salut, commnet ça va ? Hier je suis allé prank un streamer. " << std::endl;
        }else if (nb_rencontre == 2) {
            std::cout << "Ah, c'est quand ton 1v1 contre Thierry, tu vas le laver c'est sur." << std::endl;
        }else if (nb_rencontre == 3) {
            std::cout << "Tu tombes bien, je cherche Meeting (surnom), tu l'as pas vue? " << std::endl;
        }else if (nb_rencontre == 4) {
            std::cout << "Wesh encore toi, ça te dit d'aller en vacances chez moi au Canada? " << std::endl;
        }else {
            std::cout << "Encore encore toi, mais on se voit tout le temps, on est connecté" << std::endl;
        }
        nb_rencontre++;
        stats.reputation += 10;
        stats.energie += 10 + nb_rencontre;
        if(stats.reputation > 100) stats.reputation = 100;
        if(stats.energie > 100) stats.energie = 100;
    }
};

class Alice : public Eleve {
public:
    Alice() : Eleve("Alice") {}

    void parler(Stats& stats) const override {
        if (nb_rencontre == 0) {
            std::cout << "Salut, je m'appelle Alice. J'adore les énigmes et les jeux de réflexion ! Si tu as besoin d'aide pour réviser, viens me voir." << std::endl;
        } else if (nb_rencontre < 3) {
            std::cout << "Ah, te revoilà ! J'ai trouvé une nouvelle énigme hier soir, ça te tente qu'on la résolve ensemble ?" << std::endl;
        } else {
            std::cout << "Toujours toi ! Haha, je crois qu'on va finir par devenir une équipe imbattable pour les jeux et les révisions." << std::endl;
        }
        nb_rencontre++;
        stats.reputation += 10;
        stats.revision += 10 + nb_rencontre;
        if(stats.reputation > 100) stats.reputation = 100;
        if(stats.revision > 100) stats.energie = 100;
    }
};

