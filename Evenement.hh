#include "Polytech.hpp"
class Personnage;  // Déclaration anticipée
class Environnement;

class Evenement : public Polytech {
protected:
    std::vector<Personnage*> _personnages;  // Liste des personnages dans l'événement
    std::vector<Environnement*> _lieux;  // Liste des environnements associés à l'événement
public:
    virtual void afficher() override = 0;  // Afficher les informations relatives à l'événement
    virtual void action() = 0;  // Actions spécifiques à chaque événement

    Evenement(std::vector<Personnage*> personnages) : _personnages(personnages){}
};

class Rentree : public Evenement{
public:
    void afficher() override {
        std::cout << "C'est la rentrée universitaire!" << std::endl;
    }
};

class Rencontre : public Evenement {
public:
    void afficher() override {
        std::cout << "Une rencontre inattendue avec un personnage!" << std::endl;
    }
    void action() override {
        // Logique de l'action lors de la rencontre (ajouter des conséquences sur le personnage)
    }
};

class Controle : public Evenement {
public:
    void afficher() override {
        std::cout << "Un contrôle approche!" << std::endl;
    }
    void action() override {
        // Gérer les conséquences du contrôle sur l'étudiant
    }
};

class Sortir : public Evenement {
public:
    void afficher() override {
        std::cout << "C'est le moment de sortir entre amis!" << std::endl;
    }
    void action() override {
        // Les actions qui affectent l'énergie et la motivation
    }
};

class Vacances : public Evenement {
public:
    void afficher() override {
        std::cout << "Les vacances arrivent! Un peu de repos!" << std::endl;
    }
    void action() override {
        // Effets sur la motivation, l'énergie, etc.
    }
};


//opérateur de sucharge pour ajouter des personnages à un événement
std::vector<Personnage*> operator+(Personnage perso){
    
}