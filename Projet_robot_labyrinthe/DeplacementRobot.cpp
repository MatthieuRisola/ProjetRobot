#include "DeplacementRobot.h"
#include "Robot.h"

void RobotAvance::manipulate(Robot &r) const
{
    r.avance();
}


void RobotGauche::manipulate(Robot &r) const
{
    r.tourneGauche();
}


void RobotDroit::manipulate(Robot &r) const
{
    r.tourneDroite();
}
