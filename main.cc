#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>
#include 'Evenement.hh'
#include 'Polytech.hpp'
#include 'Personnage.hh'

// sort un nb random
int RandRange(int range_min, int range_max){
    int r = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    return r;
}



int main(){

    // initialiser tout ce qu'il faut

    // Pour ça, il faut créer les constructeurs pour chaque classs

    /* Initiliser les différents Personnages : 
     * Nous
     * Yves (avec qui il y aura des quetes secondaires)
     * Des profs 
     */

    /* Le temps passe de samaine en semaine, il y a 1 evenement par semaine
     * des semaines le choix est aléatoire mais à d'autres moment ils sont déja prévus (controle, vacance, rentre, semaine de ski, WEC)
    */

    /* Initiliser les différents Evenement : 
     * rentrée (on explique le dérouler de l'année, quand sont les partiels, les vacances etc...)
     * réviser (gagne des point d'apprentissage mmais tu perds en popularité)
     * se reposeer (gagne en energie)
     * sortir (tu perds en energie et en révision mais tu gagnes en popularité)
     * faire du sport (améliore la récupération d'energie et les révision)
     * controle
     */

    /* Les controles : 
     * créer différents types de controles
     * on peut par exemple, pour un controle de maths, faire du calcul mental et la difficulté des calcul dépend 
     * du temps passé à réviser, du niveau de fatigue et de la sévérité du prof
     * jeu de mémorisation
     * une courte enigme 
     * on peut ajouter un projet de groupe ou la popullarite et le temps de revision vont donner une note
     * jeu de mémoire (réecrire une phrase affiché dans le terminal)
     * QCM
     * des vrais faux
     * 
     */

    // Ajouter une commande pour pouvoir voir ses statistiques

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