// Let DocTest provide main():
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <iostream>
#include <fstream>
#include <list>

#include "../evenement.hpp"

using namespace std;

TEST_SUITE("Jeu MAin"){

TEST_CASE("1: Stats"){
  Stats stats;
  CHECK(stats.energie == 80);
  CHECK(stats.reputation == 35);
  CHECK(stats.revision == 0);
  CHECK(stats.note == -1);

  stats += 30;
  CHECK(stats.energie == 100);
  CHECK(stats.reputation == 65);
  CHECK(stats.revision == 30);
  CHECK(stats.note == -1);

  stats.afficher();
}

TEST_CASE("2: Personnage"){
  Stats stats;
  Yves yves;
  Professeur prof("Michel");

  cout << yves << std::endl;
  CHECK(yves.getNom() == "Yves");
  CHECK(yves.getRole() == "Élève");
  yves.parler(stats);
  CHECK(yves.get_rencontre() == 2);

  cout << prof << std::endl;
  CHECK(prof.getNom() == "Michel");
  CHECK(prof.getRole() == "Professeur");
  prof.parler(stats);
  CHECK(yves.get_rencontre() == 2);

}

TEST_CASE("3: Evenement" ) // Changer par les bonnes valeurs
{
  Stats stats;
  Yves yves;

  Reviser revision;
  Sortir sortir;
  Repos reposer;
  Rencontre rencontreYves(yves);
  Vacances vac;

  revision.executer(stats);
  CHECK(stats.energie == 75);
  CHECK(stats.revision == 10);

  sortir.executer(stats);
  CHECK(stats.energie == 70);
  CHECK(stats.reputation == 45);

  reposer.executer(stats);
  CHECK(stats.energie == 75);

  rencontreYves.executer(stats);
  CHECK(stats.energie == 83);
  CHECK(stats.revision == 18);
  CHECK(stats.reputation == 53);

  vac.executer(stats);
  CHECK(stats.energie == 100);
}
}

