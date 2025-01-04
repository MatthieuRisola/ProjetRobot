#include <iostream>
#include "Labyrinthe.h"
#include <conio.h>
#include "Observateur.h"
#include <vector>

using std::cout;
using std::cin;

Labyrinthe selectionLabyrinthe(const std::vector<std::string> &nomFichiersLabyrinthes, const Affichage &aff)
{
    int i=0;
    for(const auto &fichier : nomFichiersLabyrinthes)
    {
        Labyrinthe laby{};
        laby.lisDepuisFichier(fichier);
        cout<<"Labyrinthe "<<i+1<<" :"<<std::endl;
        laby.afficheSansRobot(aff);
        cout<<std::endl<<std::endl;
        ++i;
    }
    cout<<"Choix du labyrinthe"<<std::endl;
    cout<<"Labyrinthe n� : "<<std::endl;
    int numeroLabyrinthe;
    do{
        cin>>numeroLabyrinthe;
    }while(numeroLabyrinthe<1 || numeroLabyrinthe>nomFichiersLabyrinthes.size());
    Labyrinthe laby{};
    laby.lisDepuisFichier(nomFichiersLabyrinthes[numeroLabyrinthe-1]);
    return laby;
}

void selectionAlgorithme() //TODO
{
    cout<<"Selection de l'algorithme de sortie du robot"<<std::endl;
    cout<<"Algorithme (1) : Algorithme de la main droite"<<std::endl;
    cout<<"Le robot se deplace en ayant toujours un mur � sa droite (si au d�but il n�y a pas de mur � droite, il va tout droit jusqu�� rencontrer un mur)"<<std::endl;
    cout<<"Algorithme (2) : Algorithme de Pledge"<<std::endl;
    cout<<"Il consiste a :"<<std::endl;
    cout<<"1. Aller tout droit jusqu�au mur, ensuite passer � l'�tape suivante"<<std::endl;
    cout<<"2. Longer le mur par la droite (ou par la gauche, mais toujours dans le m�me sens)"<<std::endl;
    cout<<"jusqu�� ce que le d�compte des changements de direction atteigne z�ro (tourner � gauche = +1, tourner � droite = -1), ensuite revenir � l'etape 1"<<std::endl;
    cout<<"Numero de l'algorithme choisi : ";
    int numeroAlgorithme;
    do{
        cin>>numeroAlgorithme;
    }while(numeroAlgorithme!=1 && numeroAlgorithme!=2);
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
