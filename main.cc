#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "evenement.hpp"

void fin(){
    std::string ligneSeparator = "=======================================================================";
    std::string titre = "MERCI D'AVOIR JOUE A NOTRE JEU !";
    std::string auteurs = "Francis Jégou et Cyprien Renaud";

    std::cout << std::endl << std::endl << std::endl << std::endl;
    std::cout << ligneSeparator << std::endl;
    std::cout << "\t\t" << titre << std::endl;
    std::cout << ligneSeparator << std::endl;
    std::cout << std::endl;
    std::cout << "Nous vous remercions chaleureusement d'avoir joué à notre jeu de simulation de la MAIN." << std::endl;
    std::cout << "Nous espérons sincèrement qu'il vous a plu et que vous avez passé un bon moment." << std::endl;
    std::cout << std::endl;
    std::cout << "Créé avec passion par :" << std::endl;
    std::cout << auteurs << std::endl;
    std::cout << std::endl;
    std::cout << ligneSeparator << std::endl;
    std::cout << "A bientôt pour de nouvelles aventures !" << std::endl;
    std::cout << ligneSeparator << std::endl;
}


void randomevent(std::vector<Evenement*> evenements_aleatoires, Stats& stats){
    std::cout << std::endl << std::endl << std::endl << std::endl;
    for (size_t i = 0; i < 5 ; ++i) {
        int event1 = -1;
        int event2 = -1;
        int choix;
        while (event1 == event2){
            event1 = rand() % 12; 
            event2 = rand() % 12;
        }

        std::cout << "Preferez vous " << evenements_aleatoires[event1]->getNom() << " (tapez 1) ou " << evenements_aleatoires[event2]->getNom() << " (tapez 2)"<< std::endl;
        
        saisirEntierMinMax(choix, 1, 2);

        stats.maj_dif();
        
        if(choix==1) evenements_aleatoires[event1]->executer(stats);
        else evenements_aleatoires[event2]->executer(stats);
        
        stats.maj_dif();

        if (stats.energie <= 0) {
        std::cout << "Vous êtes trop fatigué pour continuer. Game over !" << std::endl;
            fin();
            break;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Initialisation de la graine aléatoire

    // Initialisation
    Stats stats;
    Alice Alice;
    Yves Yves;
    Professeur Tannier("Mr Tannier");

    Rencontre rencontreYves(Yves);
    Rencontre rencontreAlice(Alice);
    Rencontre rencontreProf(Tannier);

    // Liste d'événements aléatoires ----------------------------------------------
    std::vector<Evenement*> evenements_aleatoires = {
        new Controle(1),
        new Controle(2),
        new Controle(3),
        new Sortir(),
        new Reviser(),
        new Repos,
        new Controle(1),
        new Controle(2),
        new Controle(3),
        &rencontreYves,
        &rencontreAlice,
        &rencontreProf,
    };

    std::vector<Evenement*> evenements_recurrents = {
        new RentreePremiereAnnee("Rentree", "C'est la rentrée à Polytech Sorbonne ! Vous allez découvrir vos nouveaux camarades et professeurs.", Tannier, Yves), //Evenement 0
        new Partiel(),
        new Vacances(),
        new Ski(),
        new AutreRentree("Rentree", "C'est votre rentrée à Polytech en 2 année ! Vous allez retrouver vos nouveaux camarades et professeurs.", 2, Tannier, Yves),
        new AutreRentree("Rentree", "C'est votre rentrée à Polytech en 3 année ! Vous allez retrouver vos nouveaux camarades et professeurs.", 3, Tannier, Yves),
        new Projet(),
    };

    // Bienvenue
    (void)system("clear");

    std::cout << "Bienvenue dans le jeu MAIN !" << std::endl << std::endl;
    sleep(2);
    std::cout << "Le but du jeu est d'optenir son diplome au bout des 3 ans en ayant au moins 10 de moyenne." << std::endl << std::endl;
    sleep(5);
    std::cout << "Pour cela vous allez des différents choix qui vous menerons ou non vers cet objectif." << std::endl << std::endl;
    sleep(5);
    std::cout << "BONNE CHANCE !!!!!!" << std::endl << std::endl;
    sleep(3);

    for(int i = 0; i < 3; i++){

        std::cout << "Voici vos statistiques" << std::endl << std::endl;
        // sleep(3);
        stats.afficher();

        if(i == 0){ // année 1

            std::cout << std::endl << std::endl << "Appuiez sur Entrée une fois que vous vous voulez commencer le jeu." << std::endl << std::endl;
            attendreEntree();

            //On commence par la rentrée
            evenements_recurrents[0]->executer(stats);

            stats.maj_dif();

            //Certains nombres d'évenement aléatoire
            //tire deux événements aux hasards (ex : controle, sortie, réviser ...)
            randomevent(evenements_aleatoires, stats);

            //On a un partiel mi-semestre + vacances en ensuite
            evenements_recurrents[2]->executer(stats); //Vacances
            sleep(4);
            cout << "On part au ski" << endl << endl;
            sleep(2);
            evenements_recurrents[3]->executer(stats); //Ski

            stats.maj_dif();
            
            //De nouveau des événements aléatoires
            randomevent(evenements_aleatoires, stats);

            stats.maj_dif();

            //Partiel fin de l'année
            evenements_recurrents[1]->executer(stats); //Partiel
            evenements_recurrents[6]->executer(stats); //Projet
            sleep(3);

            stats.maj_dif();

            // Validation de l'année
            if (stats.note >= 10) {
                std::cout << std::endl << "Félicitations ! Vous avez validé votre année avec une note de " << stats.note << "/20 !" << std::endl << std::endl;
                sleep(7);
            } else {
                std::cout << std::endl << "Dommage... Vous n'avez pas validé votre année. Votre note finale est de " << stats.note << "/20." << std::endl;
                sleep(7);
                fin();
                break;
            }
        }

        else if(i == 1){ // année 2
            
            //On commence par la rentrée
            evenements_recurrents[4]->executer(stats);

            stats.maj_dif();

            //Certains nombres d'évenement aléatoire
            //tire deux événements aux hasards (ex : controle, sortie, réviser ...)
            randomevent(evenements_aleatoires, stats);

            stats.maj_dif();

            //On a un partiel mi-semestre + vacances en ensuite
            evenements_recurrents[2]->executer(stats); //Vacances
            sleep(4);
            cout << "On part au ski" << endl << endl;
            sleep(2);
            evenements_recurrents[3]->executer(stats); //Ski
            
            //De nouveau des événements aléatoires
            randomevent(evenements_aleatoires, stats);

            stats.maj_dif();

            //Partiel fin de l'année
            evenements_recurrents[1]->executer(stats); //Partiel
            evenements_recurrents[6]->executer(stats); //Projet
            sleep(3);

            stats.maj_dif();


            // Validation de l'année
            if (stats.note >= 10) {
                std::cout << std::endl << "Félicitations ! Vous avez validé votre année avec une note de " << stats.note << "/20 !" << std::endl;
                sleep(7);
            } else {
                std::cout  << std::endl<< "Dommage... Vous n'avez pas validé votre année. Votre note finale est de " << stats.note << "/20." << std::endl;
                sleep(7);
                fin();
                break;
            }
        
        }
        else{ // année 3

            evenements_recurrents[5]->executer(stats);
            std::cout << "Vous avez de la chance, en année 3 c'est les vacances donc on vous donne votre diplome." << std::endl << std::endl;
            sleep(5);
            fin();            
        }
    }

    // Nettoyage
    // Libérer uniquement les objets alloués dynamiquement
    for (Evenement* ev : evenements_aleatoires) {
        // Vérifiez si l'objet a été alloué dynamiquement
        if (ev != &rencontreYves && ev != &rencontreAlice && ev != &rencontreProf) {
            delete ev; // Libère la mémoire
        }
    }

    evenements_aleatoires.clear();


    for (Evenement* ev : evenements_recurrents) {
        delete ev;
    }
    evenements_recurrents.clear();

    return 0;
}
