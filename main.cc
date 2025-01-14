
// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "personnage.hpp"


void randomevent(std::vector<Evenement*> evenements_aleatoires, Stats stats){
    for (size_t i = 0; i < 3 ; ++i) {
        int event1 = -1;
        int event2 = -1;
        int choix;
        while (event1 == event2){
            event1 = rand() % 6; 
            event2 = rand() % 6;
        }
        std::cout << "Preferez vous " << evenements_aleatoires[event1]->getNom() << " (tapez 1) ou " << evenements_aleatoires[event2]->getNom() << " (tapez 2)"<< std::endl;
        std::cin >> choix;
        if(choix==1) evenements_aleatoires[event1]->executer(stats);
        else evenements_aleatoires[event2]->executer(stats);
    

        if (stats.energie <= 0) {
        std::cout << "Vous êtes trop fatigué pour continuer. Game over !\n";
            break;
        }
    }
}
int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Initialisation de la graine aléatoire

    // Initialisation des statistiques
    Stats stats;

    // Liste d'événements aléatoires ----------------------------------------------
    std::vector<Evenement*> evenements_aleatoires = {
        new Controle(1),
        new Controle(2),
        new Controle(3),
        new Sortir(),
        new Reviser(),
        new Repos,
    };

    std::vector<Evenement*> evenements_recurrents = {
        new Rentree(), //Evenement 0
        new Partiel(), // QCM pour le vrai controle
        new Vacances(),
        new WEC(),
        new Ski(),
        new TIS(),
    };

    // Bienvenue
    std::cout << "Bienvenue dans le jeu MAIN !\n\n";

    

    // On veut ensuite simuler trois années (donc deux boucles for)

    // int duree_annee = 30; // c'est le nombre de semaine et pour chaque

    // en génral, une année c'est environ 30 semaines

    /* 
    std::cout << "Sur combien d'itération voulez vous jouer : ";

    std::cin >> duree_annee;

    std::cout << std::endl;
    */

    for(int i = 0; i < 3; i++){

        // Au début de chaque, l'énergie est au maximum 

        // Il faut afficher les statistiques du joueur au début de l'année (au moins énergie) 

        // initialiser les personnages pour l'année qui va avoir lieu
        attendreEntree();
        stats.afficher();
        attendreEntree();


        if(i == 0){ 
            // comment ce passse l'année 1 

            //On commence par la rentrée
            evenements_recurrents[0]->executer(stats);

            //Certains nombres d'évenement aléatoire
            //tire deux événements aux hasards (ex : controle, tis, sortie, réviser ...)
            randomevent(evenements_aleatoires, stats);

            //On a un partiel mi-semestre + vacances en ensuite
            evenements_recurrents[1]->executer(stats); //Controle
            evenements_recurrents[2]->executer(stats); //Vacances
            evenements_recurrents[4]->executer(stats); //Ski
            
            //De nouveau des événements aléatoires
            randomevent(evenements_aleatoires, stats);
            //Partiel fin de l'année

            // Validation de l'année
            if (stats.note >= 10) {
                std::cout << "\nFélicitations ! Vous avez validé votre année avec une note de " << stats.note << "/20 !\n";
            } else {
                std::cout << "\nDommage... Vous n'avez pas validé votre année. Votre note finale est " << stats.note << "/20.\n";
            }
        }

        // comment ce déroule l'année 2
        else if(i == 1){
            attendreEntree();
            stats.afficher();
            attendreEntree();


    
            
            //On commence par la rentrée
            evenements_recurrents[0]->executer(stats);

            //TIS
            evenements_recurrents[5]->executer(stats);

            //Certains nombres d'évenement aléatoire
            //tire deux événements aux hasards (ex : controle, tis, sortie, réviser ...)
            randomevent(evenements_aleatoires, stats);

            //On a un partiel mi-semestre + vacances en ensuite
            evenements_recurrents[1]->executer(stats); //Controle
            evenements_recurrents[2]->executer(stats); //Vacances
            evenements_recurrents[4]->executer(stats); //Ski
            
            //De nouveau des événements aléatoires
            randomevent(evenements_aleatoires, stats);
            //Partiel fin de l'année

            // Validation de l'année
            if (stats.note >= 10) {
                std::cout << "\nFélicitations ! Vous avez validé votre année avec une note de " << stats.note << "/20 !\n";
            } else {
                std::cout << "\nDommage... Vous n'avez pas validé votre année. Votre note finale est " << stats.note << "/20.\n";
            }
        
        }
        //Comment se déroule l'année 3
        else{
            
            // c'est le semestre à l'étrnger puis le stage donc une mécanique de jeu différente
            
        }
    }


    // Nettoyage
    for (Evenement* ev : evenements_aleatoires) {
        delete ev;
    }

    for (Evenement* ev : evenements_recurrents) {
        delete ev;
    }

    return 0;
}
