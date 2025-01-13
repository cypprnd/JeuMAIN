#include <iostream>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "stats.hpp"

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



