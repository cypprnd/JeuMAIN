#include 'Environnement.hh'
#include 'Evenement.hh'
#include 'Polytech.hh'
#include 'Personnage.hh'
#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>

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

    cout << "Sur combien d'itération voulez vous jouer : ";

    cin >> duree_annee;

    cout << endl;

 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < duree_annee; j++){
            if(j == 0){
                // évenement rentrée, chaque année commence par une rentrée
                continue; // pour passer à j = 1
            }

            if(i == 0){ 
                // comment ce passse l'année 1 
            }
            else if(i == 1){
                // comment ce déroule l'année 2
            }
            else{
                // Comment ce passe l'année 3
                // c'est le semestre à l'étrnger puis le stage
            }
        }
    }


    return 0;
}