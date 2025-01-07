#define DOCTEST_CONFIG_NO_MULTITHREADING
#include "doctest.h"
#include "DeplacementRobot.h"
#include "Robot.h"

TEST_CASE ("Test des déplacements de Robot")
{
    /**TESTS ressemblant à ceux de robottest.cpp, car on doit vérifier que la méthode manipulate de la classe RobotMover
     et de ses classes dérivées appelle bien les méthodes de Robot => pour le vérifier on effectue des tests similaires
     à ceux faits pour les méthodes appelées : avance(), tourneGauche(), tourneDroite() */

    SUBCASE("RobotAvance fait avancer le robot correctement quelque soit sa direction")
    {
        int x=3;
        int y=5;
        int direction;
        int xFinal = x;
        int yFinal = y;

        SUBCASE("RobotAvance fait avancer le robot vers le haut correctement")
        {
            direction = HAUT;
            --yFinal;
        }

        SUBCASE("RobotAvance fait avancer le robot vers sa droite correctement")
        {
            direction = DROITE;
            ++xFinal;
        }

        SUBCASE("RobotAvance fait avancer le robot vers le bas correctement")
        {
            direction = BAS;
            ++yFinal;
        }

        SUBCASE("RobotAvance fait avancer le robot vers sa gauche correctement")
        {
            direction = GAUCHE;
            --xFinal;
        }

        Robot r{x,y,direction};
        RobotAvance Avance{};
        Avance.manipulate(r);
        REQUIRE_EQ(r.x(), xFinal);
        REQUIRE_EQ(r.y(), yFinal);
    }
}
