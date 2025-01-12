#pragma once
#include <iostream>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP


class Personnage {
protected:
    std::string nom;
    std::string role;

public:
    Personnage(const std::string& nom, const std::string& role) : nom(nom), role(role) {}

    virtual void parler() const {
        std::cout << nom << " (" << role << ") : Bonjour !\n";
    }

    std::string getNom() const { return nom; }
    std::string getRole() const { return role; }
};

class Professeur : public Personnage {
public:
    Professeur(const std::string& nom) : Personnage(nom, "Professeur") {}

    void parler() const override {
        std::cout << nom << " (" << role << ") : Bienvenue à Polytech ! Travaillez dur pour réussir !\n";
    }
};

class Eleve : public Personnage {
public:
    Eleve(const std::string& nom) : Personnage(nom, "Élève") {}

    void parler() const override {
        std::cout << nom << " (" << role << ") : Salut ! Si tu as besoin d'aide, n'hésite pas !\n";
    }
};

#endif // PERSONNAGE_HPP


