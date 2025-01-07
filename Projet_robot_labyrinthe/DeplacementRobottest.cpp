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

    SUBCASE("RobotGauche et RobotDroit fonctionne correctement")
    {
        int x{3}, y{5}, ancienneDirection, nouvelleDirection;

        SUBCASE("RobotGauche fait tourner le robot a gauche correctement quelque soit sa direction initiale")
        {
            SUBCASE("RobotGauche fonctionne correctement quand le robot avait comme direction initiale : HAUT")
            {
                ancienneDirection=HAUT;
                nouvelleDirection=GAUCHE;
            }

            SUBCASE("RobotGauche fonctionne correctement quand le robot avait comme direction initiale : DROITE")
            {
                ancienneDirection=DROITE;
                nouvelleDirection=HAUT;
            }

            SUBCASE("RobotGauche fonctionne correctement quand le robot avait comme direction initiale : BAS")
            {
                ancienneDirection=BAS;
                nouvelleDirection=DROITE;
            }

            SUBCASE("RobotGauche fonctionne correctement quand le robot avait comme direction initiale : GAUCHE")
            {
                ancienneDirection=GAUCHE;
                nouvelleDirection=BAS;
            }

            Robot r(x,y,ancienneDirection);
            RobotGauche Gauche{};
            Gauche.manipulate(r);
            REQUIRE_EQ(r.direction(), nouvelleDirection);
        }


        SUBCASE("RobotDroit fait tourner le robot a droite correctement quelque soit sa direction initiale")
        {
            SUBCASE("RobotDroit fonctionne correctement quand le robot avait comme direction initiale : HAUT")
            {
                ancienneDirection=HAUT;
                nouvelleDirection=DROITE;
            }

            SUBCASE("RobotDroit fonctionne correctement quand le robot avait comme direction initiale : DROITE")
            {
                ancienneDirection=DROITE;
                nouvelleDirection=BAS;
            }

            SUBCASE("RobotDroit fonctionne correctement quand le robot avait comme direction initiale : BAS")
            {
                ancienneDirection=BAS;
                nouvelleDirection=GAUCHE;
            }

            SUBCASE("RobotDroit fonctionne correctement quand le robot avait comme direction initiale : GAUCHE")
            {
                ancienneDirection=GAUCHE;
                nouvelleDirection=HAUT;
            }

            Robot r(x,y,ancienneDirection);
            RobotDroit Droite{};
            Droite.manipulate(r);
            REQUIRE_EQ(r.direction(), nouvelleDirection);
        }
    }
}
