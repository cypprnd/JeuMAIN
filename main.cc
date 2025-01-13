#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "personnage.hpp"
//#include "evenement.hpp"

void fin(){
    std::string ligneSeparator = "========================================";
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

    // Initialisation des statistiques
    Stats stats;
    Alice Alice;
    Yves Yves;
    Professeur Tannier("Mr Tannier");

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
        new RentreePremiereAnnee("Rentree", "C'est la rentrée à Polytech Sorbonne ! Vous allez découvrir vos nouveaux camarades et professeurs."), //Evenement 0
        new Partiel(), // QCM pour le gros controle
        new Vacances(),
        new WEC(),
        new Ski(),
        new TIS(),
        new AutreRentree("Rentree", "C'est votre rentrée à Polytech en 2 année ! Vous allez retrouver vos nouveaux camarades et professeurs.", 2),
        new AutreRentree("Rentree", "C'est votre rentrée à Polytech en 3 année ! Vous allez retrouver vos nouveaux camarades et professeurs.", 3),
    };

    // Bienvenue
    (void)system("clear");

    std::cout << "Bienvenue dans le jeu MAIN !" << std::endl << std::endl;
    sleep(3);

    std::cout << "Le but du jeu est d'optenir son diplome au bout des 3 ans en ayant au moins 10 de moyenne." << std::endl << std::endl;
    sleep(6);
    std::cout << "Pour cela vous allez des différents choix qui vous menerons ou non vers cet objectif." << std::endl << std::endl;
    sleep(6);
    std::cout << "BONNE CHANCE !!!!!!" << std::endl << std::endl;
    sleep(3);

    for(int i = 0; i < 3; i++){

        // Au début de chaque, l'énergie est au maximum 

        // Il faut afficher les statistiques du joueur au début de l'année (au moins énergie) 

        // initialiser les personnages pour l'année qui va avoir lieu
        // attendreEntree();
        std::cout << "Voici vos statistiques pour commencer le jeux:" << std::endl << std::endl;
        sleep(3);
        stats.afficher();
        std::cout << std::endl << std::endl << "Appuiez sur Entrée une fois que vous vous voulez commencer le jeu." << std::endl << std::endl;
        attendreEntree();


        if(i == 0){ 
            // comment ce passse l'année 1 

            //On commence par la rentrée
            evenements_recurrents[0]->executer(stats);

            //Certains nombres d'évenement aléatoire
            //tire deux événements aux hasards (ex : controle, tis, sortie, réviser ...)
            randomevent(evenements_aleatoires, stats);

            //On a un partiel mi-semestre + vacances en ensuite
            evenements_recurrents[1]->executer(stats); //Partiel
            evenements_recurrents[2]->executer(stats); //Vacances
            evenements_recurrents[4]->executer(stats); //Ski
            
            //De nouveau des événements aléatoires
            randomevent(evenements_aleatoires, stats);
            //Partiel fin de l'année

            // Validation de l'année
            if (stats.note >= 10) {
                std::cout << std::endl << "Félicitations ! Vous avez validé votre année avec une note de " << stats.note << "/20 !" << std::endl;
            } else {
                std::cout << std::endl << "Dommage... Vous n'avez pas validé votre année. Votre note finale est " << stats.note << "/20." << std::endl;
                fin();
                break;
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
                std::cout << std::endl << "Félicitations ! Vous avez validé votre année avec une note de " << stats.note << "/20 !" << std::endl;
            } else {
                std::cout  << std::endl<< "Dommage... Vous n'avez pas validé votre année. Votre note finale est " << stats.note << "/20." << std::endl;
                fin();
                break;
            }
        
        }
        //Comment se déroule l'année 3
        else{
            
            std::cout << "Vous avez de la chance, en année 3 c'est les vacances donc on vous donne votre diplome.";
            fin();

            // Mettre des truc pour la fin du jeu (faire des evenements vous avez votre diplome, vous avez votre année, vous avez rater votre année et perdu le jeu)
            
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
