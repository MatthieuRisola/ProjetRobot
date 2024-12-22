#define DOCTEST_CONFIG_NO_MULTITHREADING
#include "doctest.h"
#include "Robot.h"

// tester x(), y(), direction() ?
// ATTENTION : au debut le robot ne peut pas changer sa direction

TEST_CASE("Robot fonctionne")
{
    SUBCASE("Robot est cree correctement avec les bonnes donnees")
    {
        int x{3}, y{5}, direction{GAUCHE};
        Robot r{x,y,direction};
        REQUIRE_EQ(r.x(),x);
        REQUIRE_EQ(r.y(),y);
        REQUIRE_EQ(r.direction(),direction);
    }
    SUBCASE("Robot verifie s'il y a un obstacle correctement")
    {
        SUBCASE("Robot verifie correctement si obstacle devant lui")
        {

        }
        SUBCASE("Robot verifie correctement si obstacle à sa gauche")
        {

        }
        SUBCASE("Robot verifie correctement si obstacle à sa droite")
        {

        }
    }
    SUBCASE("Robot avance correctement selon sa direction") //TODO : factoriser par Robot r{x,y,direction} si possible
    {
        int x{3}, y{5}, direction, xFinal{x}, yFinal{y};

        SUBCASE("Robot avance vers le haut correctement")
        {
            direction=HAUT;
            --yFinal;
        }
        SUBCASE("Robot avance vers sa droite correctement")
        {
            direction=DROITE;
            ++xFinal;
        }
        SUBCASE("Robot avance vers le bas correctement")
        {
            direction=BAS;
            ++yFinal;
        }
        SUBCASE("Robot avance vers sa gauche correctement")
        {
            direction=GAUCHE;
            --xFinal;
        }
        Robot r{x,y,direction};
        r.avance();
        REQUIRE_EQ(r.x(), xFinal);
        REQUIRE_EQ(r.y(), yFinal);
    }
    SUBCASE("Robot change de direction correctement")
    {
        int x{3}, y{5}, ancienneDirection, nouvelleDirection;
        SUBCASE("Robot tourne a gauche correctement")
        {
            SUBCASE("Robot tourne a gauche quand il avait pour direction HAUT correctement")
            {
                ancienneDirection=HAUT;
                nouvelleDirection=GAUCHE;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction DROITE correctement")
            {
                ancienneDirection=DROITE;
                nouvelleDirection=HAUT;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction BAS correctement")
            {
                ancienneDirection=BAS;
                nouvelleDirection=DROITE;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction GAUCHE correctement")
            {
                ancienneDirection=GAUCHE;
                nouvelleDirection=BAS;
            }
            Robot r(x,y,ancienneDirection);
            r.tourneGauche();
            REQUIRE_EQ(r.direction(), nouvelleDirection);
        }
        SUBCASE("Robot tourne a droite correctement")
        {
            int x{3}, y{5}, ancienneDirection, nouvelleDirection;
            SUBCASE("Robot tourne a gauche quand il avait pour direction HAUT correctement")
            {
                ancienneDirection=HAUT;
                nouvelleDirection=DROITE;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction DROITE correctement")
            {
                ancienneDirection=DROITE;
                nouvelleDirection=BAS;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction BAS correctement")
            {
                ancienneDirection=BAS;
                nouvelleDirection=GAUCHE;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction GAUCHE correctement")
            {
                ancienneDirection=GAUCHE;
                nouvelleDirection=HAUT;
            }
            Robot r(x,y,ancienneDirection);
            r.tourneDroite();
            REQUIRE_EQ(r.direction(), nouvelleDirection);
        }
    }
}
