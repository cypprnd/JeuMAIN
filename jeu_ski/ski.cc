#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PLAYER_SIZE = 40;
const int GATE_WIDTH = 150;  
const int GATE_SPACING = 300;  
const float PLAYER_SPEED = 0.2;
const float GATE_SPEED = 0.1; 
const float SNOWDUNE_SPEED = 0.1;

const sf::Color snowColor = sf:: Color(230, 230, 240);


extern sf::Font defaultFont;
struct Gate {
    sf::Sprite leftPost;
    sf::Sprite rightPost;
    float yPosition;
};

struct Snow {
    sf::Sprite neige;
    float speed;
};

// Fonction pour afficher le menu avec du texte ajusté
void showMenu(sf::RenderWindow &window, sf::Font &font, bool &gameStarted) {
    sf::Text titleText("Ski Game", font, 48);
    titleText.setFillColor(sf::Color::Blue);
    titleText.setPosition(WINDOW_WIDTH / 2 - titleText.getLocalBounds().width / 2, 100);

    // Ajuster le texte des instructions pour ne pas dépasser la fenêtre
    sf::Text instructionsText("Appuyez sur 'Entree' pour commencer", font, 24);
    instructionsText.setFillColor(sf::Color::Black);
    instructionsText.setPosition(WINDOW_WIDTH / 2 - instructionsText.getLocalBounds().width / 2, 200);

    // Afficher les règles en plusieurs lignes si nécessaire
    std::string rules = "Règles: \n\n- Utilisez les flèches gauche et droite pour déplacer le joueur.\n- Passez entre les portes pour marquer des points.\n- Evitez de heurter les portes!";
    sf::Text rulesText(rules, font, 24);
    rulesText.setFillColor(sf::Color::Black);

    // Diviser le texte en lignes pour s'adapter à la largeur de la fenêtre
    std::string line1 = "- Utilisez les fleches gauche \n et droite pour deplacer le joueur.\n";
    std::string line2 = "- Passez entre les portes \n pour marquer des points.\n";
    std::string line3 = "- Evitez de heurter les portes !\n";
    
    sf::Text line1Text(line1, font, 24);
    sf::Text line2Text(line2, font, 24);
    sf::Text line3Text(line3, font, 24);

    line1Text.setFillColor(sf::Color::Black);
    line2Text.setFillColor(sf::Color::Black);
    line3Text.setFillColor(sf::Color::Black);

    // Ajuster la position des lignes pour qu'elles ne se chevauchent pas
    line1Text.setPosition(WINDOW_WIDTH / 2 - line1Text.getLocalBounds().width / 2, 300);
    line2Text.setPosition(WINDOW_WIDTH / 2 - line2Text.getLocalBounds().width / 2, 400);
    line3Text.setPosition(WINDOW_WIDTH / 2 - line3Text.getLocalBounds().width / 2, 500);

    // Affichage du menu
    while (!gameStarted && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                gameStarted = true;  // Le jeu commence quand l'utilisateur appuie sur "Entrée"
            }
        }

        window.clear(snowColor);
        window.draw(titleText);
        window.draw(instructionsText);
        window.draw(line1Text);
        window.draw(line2Text);
        window.draw(line3Text);
        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ski Game");

    // Chargement de la texture du joueur
    sf::Texture playerTexture_right, playerTexture_left, playerTexture_front;
    if (!playerTexture_front.loadFromFile("sprite_1.png") || !playerTexture_right.loadFromFile("sprite_3.png") || !playerTexture_left.loadFromFile("sprite_1.png")) {
        std::cerr << "Erreur de chargement de l'image du joueur." << std::endl;
        return -1;
    }

    // Initialisation du sprite du joueur
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture_front);
    playerSprite.setScale(PLAYER_SIZE / static_cast<float>(playerTexture_front.getSize().x),
                          PLAYER_SIZE / static_cast<float>(playerTexture_front.getSize().y));
    playerSprite.setPosition(WINDOW_WIDTH / 2 - PLAYER_SIZE / 2, WINDOW_HEIGHT - 100);

    // Chargement des textures des portes
    sf::Texture gateTexture;
    if (!gateTexture.loadFromFile("tree1.png")) {  
        std::cerr << "Erreur de chargement de l'image des portes." << std::endl;
        return -1;
    }

    // Liste des portes
    std::vector<Gate> gates;

    // Chargement des textures de la neige
    sf::Texture neige1Texture, neige2Texture;
    if (!neige1Texture.loadFromFile("dune1.png") || !neige2Texture.loadFromFile("dune2.png")) {  
        std::cerr << "Erreur de chargement de l'image des portes." << std::endl;
        return -1;
    }

    // Liste des flocons de neige
    std::vector<Snow> buffer_snow;

    // Initialisation aléatoire
    std::srand(std::time(nullptr));

    int score = 0;
    bool gameOver = false;
    bool gameStarted = false;
    float difficulty = 1.0f;  // Facteur de difficulté initial
    float addspeed = 1.0f;
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/croscore/Cousine-Regular.ttf")) {
        std::cerr << "Erreur de chargement de la police." << std::endl;
        return -1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // Affichage du menu avant de commencer le jeu
    showMenu(window, font, gameStarted);

    // Boucle principale
    while (window.isOpen()) {
        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (score % 5 == 0 && score > 0) {
            difficulty += 0.00005f;  // Augmente la difficulté toutes les 5 points de score
            addspeed += 0.000025f;
        }

        if (!gameOver) {
            // Déplacement du joueur
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerSprite.getPosition().x > 0) {
                playerSprite.move(-addspeed*0.15f, 0);
                playerSprite.setTexture(playerTexture_left);  // Le skieur regarde à gauche
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerSprite.getPosition().x < WINDOW_WIDTH - PLAYER_SIZE) {
                playerSprite.move(addspeed*0.15f, 0);
                playerSprite.setTexture(playerTexture_right);  // Le skieur regarde à gauche
            }

            // Ajout de nouvelles portes
            if (gates.empty() || gates.back().yPosition > GATE_SPACING) {
                float gateCenter = std::rand() % (WINDOW_WIDTH - GATE_WIDTH) + GATE_WIDTH / 2;
                Gate gate;
                gate.leftPost.setTexture(gateTexture);
                gate.leftPost.setScale(1.0f, 2.0f); // Redimensionner si nécessaire
                gate.leftPost.setPosition(gateCenter - GATE_WIDTH / 2, -30);

                gate.rightPost.setTexture(gateTexture);
                gate.rightPost.setScale(1.0f, 2.0f); // Redimensionner si nécessaire
                gate.rightPost.setPosition(gateCenter + GATE_WIDTH / 2 - 10, -30);

                gate.yPosition = -30;
                gates.push_back(gate);
            }

            // Déplacement des portes et détection des passages
            for (auto it = gates.begin(); it != gates.end();) {
                it->yPosition += difficulty*0.07;
                it->leftPost.move(0, difficulty*0.07f);
                it->rightPost.move(0, difficulty*0.07f);

                if (it->yPosition > 5*WINDOW_HEIGHT/6 && it->yPosition < WINDOW_HEIGHT) {
                // Vérification du passage correct entre les portes
                float playerCenterX = playerSprite.getPosition().x + PLAYER_SIZE / 2;
                if (it->yPosition > playerSprite.getPosition().y && it->yPosition < playerSprite.getPosition().y + PLAYER_SIZE) {
                    if (playerCenterX < it->leftPost.getPosition().x + 10 || playerCenterX > it->rightPost.getPosition().x) {
                        gameOver = true;
                        break;
                    } else {
                        score++;
                        it = gates.erase(it);
                        continue;
                    }
                }
                }
                // Suppression des portes hors écran
                if (it->yPosition > WINDOW_HEIGHT) {
                    it = gates.erase(it);
                } else {
                    ++it;
                }
            }

            // Création des dunes de neige
            if (std::rand() % 100 < 2) {  // Ajouter des dunes de neige avec une probabilité de 2%
                Snow snow;
                if (std::rand() % 2 == 0) {
                    snow.neige.setTexture(neige1Texture);  // Utilisation de la texture 1
                } else {
                    snow.neige.setTexture(neige2Texture);  // Utilisation de la texture 2
                }
                snow.neige.setScale(1.0f, 0.5f);  // Ajuster la taille des dunes si nécessaire
                snow.neige.setPosition(std::rand() % WINDOW_WIDTH, -100);  // Position aléatoire en haut
                snow.speed = SNOWDUNE_SPEED;
                buffer_snow.push_back(snow);
            }

            // Déplacement des dunes de neige
            for (auto& snowDune : buffer_snow) {
                snowDune.neige.move(0, difficulty*0.07f);  // Déplacer les dunes de neige vers le bas
            }

            // Suppression des dunes de neige hors de l'écran
            buffer_snow.erase(std::remove_if(buffer_snow.begin(), buffer_snow.end(),
                [](const Snow& snowDune) {
                    return snowDune.neige.getPosition().y > WINDOW_HEIGHT;
                }), buffer_snow.end());
        
        
            // Mise à jour du score
            scoreText.setString("Score: " + std::to_string(score));
        }
        

        // Effacer l'écran
        window.clear(snowColor);

        // Dessiner les objets
        window.draw(playerSprite);
        for (const auto& gate : gates) {
            window.draw(gate.leftPost);
            window.draw(gate.rightPost);
        }
        for (const auto& snow : buffer_snow) {
            window.draw(snow.neige);
        }
        window.draw(scoreText);

        // Afficher Game Over
        if (gameOver) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(48);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setString("GAME OVER!");
            gameOverText.setPosition(WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 2 - 24);
            // Affichage du nombre d'étoiles en fonction du score
            std::string starRating;
            if (score >= 0 && score <= 10) {
                starRating = "Score: " + std::to_string(score) + " Vous avez obtenu l'etoile de bronze ";
            } else if (score > 10 && score <= 20) {
                starRating = "Score: " + std::to_string(score) + " Vous avez obtenu l'etoile d'argent ";
            } else {
                starRating = "Score: " + std::to_string(score) + " Vous avez obtenu l'etoile d'or ";
            }

            sf::Text scoreText(starRating, font, 24);
            scoreText.setFillColor(sf::Color::Black);
            scoreText.setPosition(WINDOW_WIDTH / 2 - scoreText.getLocalBounds().width / 2,
                      WINDOW_HEIGHT / 2 + 20);

            sf::Text restartText("Appuyez sur Entree pour quitter", font, 24);
            restartText.setFillColor(sf::Color::Black);
            restartText.setPosition(WINDOW_WIDTH / 2 - restartText.getLocalBounds().width / 2,
                        WINDOW_HEIGHT / 2 + 80);

            window.draw(gameOverText);
            window.draw(scoreText);
            window.draw(restartText);
            window.display();

            // Attente pour quitter le jeu
            while (window.isOpen()) {
                 sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                        window.close();  // Quitter le jeu si "Entrée" est pressée
                    }
                }
            }   
        }

        // Afficher à l'écran
        window.display();
    }
    

    return 0;
}


