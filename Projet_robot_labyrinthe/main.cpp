#include <iostream>
#include "Labyrinthe.h"
#include <conio.h>
#include "Observateur.h"
#include <vector>
#include "Affichage.h"

using std::cout;
using std::cin;

Labyrinthe selectionLabyrinthe() // A TESTER
{
    std::string nomFichier;
    std::cout<<"Entrer le nom du fichier contenant le labyrinthe : ";
    std::cin>>nomFichier;
    Labyrinthe laby{};
    laby.lisDepuisFichier(nomFichier);
    return laby;
}

/*Affichage selectionAffichage(const Labyrinthe &laby) //TO DO
{

}*/

void selectionAlgorithme() //A TESTER
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
