#define DOCTEST_CONFIG_NO_MULTITHREADING
#include "doctest.h"
#include "DeplacementRobot.h"
#include "Robot.h"

TEST_CASE ("Test des déplacements de Robot")
{
    int x=3;
    int y=5;
    int direction = HAUT;
    Robot r{x,y, direction};

    SUBCASE("Le robot avance correctement")
    {
        RobotAvance Avance;
        Avance.manipulate(r);

    }
}
