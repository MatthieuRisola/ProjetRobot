#include <iostream>
#include "Labyrinthe.h"
#include <conio.h>

using namespace std;

int main()
{
    Robot r(14,5,Direction::HAUT);
    AffichageTexteSimple aff{};
    Labyrinthe laby{};
    laby.lisDepuisFichier("test.txt");
    aff.afficheDepart(laby, r);
}
