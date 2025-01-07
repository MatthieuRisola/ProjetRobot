#include "DeplacementRobot.h"
#include "Robot.h"
#include <thread>
#include <chrono>

void RobotAvance::manipulate(Robot &r) const
{
    r.avance();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


void RobotGauche::manipulate(Robot &r) const
{
    r.tourneGauche();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


void RobotDroit::manipulate(Robot &r) const
{
    r.tourneDroite();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
