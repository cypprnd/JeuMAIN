#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>
#include 'Environnement.hh'
#include 'Evenement.hh'
#include 'Polytech.hh'
#include 'Personnage.hh'

int RandRange(int range_min, int range_max){
    int r = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    return r;
}



int main(){

    // initialiser tout ce qu'il faut

    // Pour ça, il faut créer les constructeurs pour chaque classs

    /* Initiliser les différents Personnages : 
     * Nous
     * Yves
     * Des profs
     */

    /* Initiliser les différents Environnement : 
     * Crous
     * 
     * 
     */

    // 

    // On veut ensuite simuler trois années (donc deux boucles for)

    int duree_annee = 30; // c'est le nombre de semaine et pour chaque

    // en génral, une année c'est environ 30 semaines

    std::cout << "Sur combien d'itération voulez vous jouer : ";

    std::cin >> duree_annee;

    std::cout << std::endl;

 
    for(int i = 0; i < 3; i++){

        // Au début de chaque, l'énergie est au maximum 

        // Il faut afficher les statistiques du joueur au début de l'année (au moins énergie) 

        // initialiser les personnages pour l'année qui va avoir lieu

        if(i == 0){ 
            // comment ce passse l'année 1 
        }
        else if(i == 1){
            // comment ce déroule l'année 2
        }
        else{
            // Comment ce passe l'année 3
            // c'est le semestre à l'étrnger puis le stage donc une mécanique de jeu différente
        }

        for(int j = 0; j < duree_annee; j++){
            if(j == 0){
                // évenement rentrée, chaque année commence par une rentrée
                continue; // pour passer à j = 1
            }

            else if(j == duree_annee - 1 || j == duree_annee/2){
                // grosse semaine de partiel avant les vacances
            }

            else if(j == duree_annee){
                // Tu as terminé l'année, c'est les vacances
                // Est-ce que tu passes à l'année suivante?
            }

            else if((duree_annee/2) + 1){
                // Tu as terminé le premier semestre de l'année X, est-ce que tu le valides?
                // Tu as deux semaines de vacances
            }

            else if(j == (duree_annee/4) || j == 3*(duree_annee/4)){
                // Séance de partiel mi-semestre
            }

            else if(j == 3*(duree_annee/4) + 1 || j == 3*(duree_annee/4) + 1){
                // Tu as une semaine de vacances pour te remettre en forme
            }

            
        }
    }


    return 0;
}