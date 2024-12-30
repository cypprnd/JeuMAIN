#include <iostream>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#ifndef STATS_HPP
#define STATS_HPP

// Fonction pour attendre une entrée de l'utilisateur
void attendreEntree() {
    //std::cout << "\nAppuyez sur Entrée pour continuer...";
    std::cin.ignore();
}

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

// Fonction pour afficher une image ASCII
void afficherImage(const std::vector<std::string>& image) {
    for (const std::string& ligne : image) {
        std::cout << ligne << "\n";
    }
}


#endif // STATS_HPP



#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP


class Personnage {
protected:
    std::string nom;
    std::string role;

public:
    Personnage(const std::string& nom, const std::string& role) : nom(nom), role(role) {}

    virtual void parler() const {
        std::cout << nom << " (" << role << ") : Bonjour !\n";
    }

    std::string getNom() const { return nom; }
    std::string getRole() const { return role; }
};

class Professeur : public Personnage {
public:
    Professeur(const std::string& nom) : Personnage(nom, "Professeur") {}

    void parler() const override {
        std::cout << nom << " (" << role << ") : Bienvenue à Polytech ! Travaillez dur pour réussir !\n";
    }
};

class Eleve : public Personnage {
public:
    Eleve(const std::string& nom) : Personnage(nom, "Élève") {}

    void parler() const override {
        std::cout << nom << " (" << role << ") : Salut ! Si tu as besoin d'aide, n'hésite pas !\n";
    }
};

#endif // PERSONNAGE_HPP

#ifndef EVENEMENT_HPP
#define EVENEMENT_HPP

//Focntion du Tis
struct Obstacle {
        int x;
        int y;
    };

void jumpGame(Stats& stats) {
        initscr();            // Démarre ncurses
        noecho();             // Ne pas afficher les entrées utilisateur
        curs_set(0);          // Masque le curseur
        nodelay(stdscr, TRUE);// Rendre getch non bloquant

        int maxHeight, maxWidth;
        getmaxyx(stdscr, maxHeight, maxWidth);

        int playerX = maxWidth / 4;
        int playerY = maxHeight - 2;
        int jumpHeight = 0;
        bool isJumping = false;

        std::vector<Obstacle> obstacles;
        srand(time(0));

        while (true) {
            clear();

            // Ajoute un nouvel obstacle périodiquement
            if (rand() % 20 == 0) {
                int obstacleY = rand() % (maxHeight - 3) + 1;
                obstacles.push_back({maxWidth, obstacleY});
            }

            // Affichage des statistiques
            mvprintw(0, 0, "  Énergie: %d", stats.energie);

            // Affichage du joueur
            mvprintw(playerY - jumpHeight, playerX, "@");

            // Déplace et affiche les obstacles
            for (auto it = obstacles.begin(); it != obstacles.end();) {
                mvprintw(it->y, it->x, "#");
                it->x -= 1;

                // Vérifie les collisions
                if (it->x == playerX && playerY - jumpHeight == it->y) {
                    stats.energie -= 10;
                    mvprintw(maxHeight / 2, maxWidth / 2 - 10, "Collision! Énergie -10");
                    if (stats.energie <= 0) {
                        mvprintw(maxHeight / 2 + 1, maxWidth / 2 - 10, "GAME OVER!");
                        refresh();
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        endwin();
                        return;
                    }
                }

                // Supprime les obstacles hors de l'écran
                if (it->x < 0) {
                    it = obstacles.erase(it);
                   
                } else {
                    ++it;
                }
            }

            // Gère le saut
            if (isJumping) {
                jumpHeight += 1;
                if (jumpHeight > 3) {
                    isJumping = false;
                }
            } else if (jumpHeight > 0) {
                jumpHeight -= 1;
            }

            // Gère l'entrée utilisateur
            int ch = getch();
            if (ch == ' ') {
                isJumping = true;
            } else if (ch == 'q') {
                break;
            }

            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        endwin();
    }



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



#endif // EVENEMENT_HPP



