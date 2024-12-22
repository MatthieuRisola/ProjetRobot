#include <iostream>
#include "Labyrinthe.h"
#include <conio.h>
#include "Observateur.h"

using namespace std;

int main()
{
    Robot r(14,5,Direction::HAUT);
    AffichageTexteSimple aff{};
    Labyrinthe laby{};
    laby.lisDepuisFichier("test.txt");
    aff.afficheDepart(laby, r);
    ObservateurAffichage obs(aff,laby,r.x(),r.y(),r.direction());
    r.ajouteObservateur(std::make_unique<ObservateurAffichage>(obs));
    getch();
    r.avance();
    r.notifieObservateurs();
    getch();
}
