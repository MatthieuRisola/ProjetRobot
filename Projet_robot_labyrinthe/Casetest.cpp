#define DOCTEST_CONFIG_NO_MULTITHREADING
#include "doctest.h"
#include "case.h"
#include <string>

TEST_CASE("Le constructeur par défaut fonctionne")
{
    Case c{};
    REQUIRE_EQ(c.typeEnChaine(), "Vide");
}

TEST_CASE("Le constructeur avec paramètres fonctionne")
{
    Case::TypeCase type = Case::Mur;
    Case c{type};
    REQUIRE_EQ(c.type(), type);
}

TEST_CASE("Le changement de type fonctionne")
{
    Case c{};
    Case::TypeCase type = Case::Arrivee;
    Case::TypeCase type2 = Case::Depart;

    c.changeType(type);
    REQUIRE_EQ(c.type(), type);

    c.changeType(type2);
    REQUIRE_EQ(c.type(), type2);
}

TEST_CASE("La copie fonctionne")
{
    Case::TypeCase typeNouv = Case::Mur;
    Case c{};
    Case cNouv{typeNouv};
    c=cNouv;
    REQUIRE_EQ(c.type(), typeNouv);
}
