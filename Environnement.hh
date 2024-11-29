#include "Polytech.hpp"

class Environnement : public Polytech {
public:
    virtual void afficher() override {
        std::cout << "Vous êtes dans un environnement..." << std::endl;
    }
};

class Crous : public Environnement {
public:
    void afficher() override {
        std::cout << "Vous êtes au CROUS, lieu de détente!" << std::endl;
    }
};

class BU : public Environnement {
public:
    void afficher() override {
        std::cout << "Vous êtes à la Bibliothèque Universitaire (BU)." << std::endl;
    }
};

class Classe : public Environnement {
public:
    void afficher() override {
        std::cout << "Vous êtes en cours." << std::endl;
    }
};
