#define DOCTEST_CONFIG_NO_MULTITHREADING
#include "Labyrinthe.h"
#include "doctest.h"

Labyrinthe creerEtVerifierLabyrinthe(const std::string& fichier) {
    Labyrinthe labyrinthe;
    REQUIRE_NOTHROW(labyrinthe.lisDepuisFichier(fichier));
    REQUIRE_UNARY(labyrinthe.estValide());
    return labyrinthe;
}

TEST_CASE("Labyrinthe fonctionne correctement") {
    const std::string fichierTest = "test.txt";
    const std::string fichierTestInvalide = "test_labyrinthe_invalide.txt";
    const std::string fichierSauvegarde = "sauvegarde_labyrinthe.txt";
    Labyrinthe labyrinthe = creerEtVerifierLabyrinthe(fichierTest);

    SUBCASE("Lecture et création d'un labyrinthe est correcte") {
        REQUIRE_EQ(labyrinthe.hauteur(), 7);
        REQUIRE_EQ(labyrinthe.largeur(), 16);
    }

    SUBCASE("Sauvegarde et relecture est correcte") {
        REQUIRE_NOTHROW(labyrinthe.sauvegardeSur(fichierSauvegarde));
        Labyrinthe labyrintheSauvegarde = creerEtVerifierLabyrinthe(fichierSauvegarde);
        REQUIRE_EQ(labyrinthe.hauteur(), labyrintheSauvegarde.hauteur());
        REQUIRE_EQ(labyrinthe.largeur(), labyrintheSauvegarde.largeur());
        REQUIRE_EQ(labyrinthe.typeCase(0, 0), labyrintheSauvegarde.typeCase(0, 0));
    }

    SUBCASE("Validation des labyrinthes") {
        SUBCASE("Le labyrinthe est valide"){
            REQUIRE_UNARY(labyrinthe.estValide());
        }
        SUBCASE("Le labyrinthe est invalide"){
            Labyrinthe labyrintheInvalide;
            REQUIRE_NOTHROW(labyrintheInvalide.lisDepuisFichier(fichierTestInvalide));
            REQUIRE_UNARY_FALSE(labyrintheInvalide.estValide());
        }
    }

    SUBCASE("Accès aux informations sur une case est correcte") {
        REQUIRE_NOTHROW(labyrinthe.informationCase(0,0));
        REQUIRE_EQ(labyrinthe.typeCase(1, 1), Case::Vide);
        REQUIRE_EQ(labyrinthe.typeCase(0, 1), Case::Mur);
        REQUIRE_EQ(labyrinthe.typeCase(5, 2), Case::Arrivee);
        REQUIRE_EQ(labyrinthe.typeCase(5, 12), Case::Depart);
        REQUIRE_THROWS_AS(labyrinthe.informationCase(-1, 0), std::out_of_range); // Case hors limites
    }

}
