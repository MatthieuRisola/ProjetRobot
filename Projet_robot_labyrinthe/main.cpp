#include <iostream>
#include "Labyrinthe.h"
#include <conio.h>
#include "Observateur.h"

using namespace std;

Labyrinthe selectionLabyrinthe(const vector<string> &nomFichiersLabyrinthes, const Affichage &aff)
{
    int i=0;
    for(const auto &fichier : nomFichiersLabyrinthes)
    {
        Labyrinthe laby{};
        laby.lisDepuisFichier(fichier);
        cout<<"Labyrinthe "<<i<<" :"<<endl;
        laby.afficheSansRobot(aff);
        cout<<endl<<endl;
        ++i;
    }
}

void selectionAlgorithme()
{

}

void mainDroite(Robot &rob, const Labyrinthe &laby)
{

}

void pledge(Robot &rob, const Labyrinthe &laby)
{

}

int main()
{
    Robot r(5,6,Direction::HAUT);
    AffichageTexteAmeliore1 aff{};
    Labyrinthe laby{};
    laby.lisDepuisFichier("testaffichage.txt");
    aff.afficheDepart(laby, r);
    ObservateurAffichage obs(aff,laby,r.x(),r.y(),r.direction());
    r.ajouteObservateur(std::make_unique<ObservateurAffichage>(obs));
    getch();
    r.avance();
    r.notifieObservateurs();
    getch();
    r.tourneDroite();
    r.notifieObservateurs();
    getch();
    r.avance();
    r.notifieObservateurs();
    getch();
    r.avance();
    r.notifieObservateurs();
    getch();
    r.avance();
    r.notifieObservateurs();
    getch();
    r.avance();
    r.notifieObservateurs();
    getch();
    r.avance();
    r.notifieObservateurs();
    getch();
    r.avance();
    r.notifieObservateurs();
    getch();
}
