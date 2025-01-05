#include <iostream>
#include "Labyrinthe.h"
#include <conio.h>
#include "Observateur.h"
#include <vector>
#include "Affichage.h"

using std::cout;
using std::cin;

const int NUMERO_MAIN_DROITE=1;
const int NUMERO_PLEDGE=1;

Labyrinthe selectionLabyrinthe() // A TESTER
{
    std::string nomFichier;
    cout<<"Entrer le nom du fichier contenant le labyrinthe : ";
    cin>>nomFichier;
    Labyrinthe laby{};
    laby.lisDepuisFichier(nomFichier);
    return laby;
}

std::unique_ptr<Affichage> selectionAffichage(const Labyrinthe &laby)
{
    cout<<"Choix de l'affichage du labyrinthe :"<<std::endl;
    std::vector<std::unique_ptr<Affichage>> tableau{};
    tableau.reserve(3);
    tableau.push_back(std::make_unique<AffichageTexteSimple>());
    tableau.push_back(std::make_unique<AffichageTexteAmeliore1>());
    tableau.push_back(std::make_unique<AffichageTexteAmeliore2>());
    for(int i{0}; i<tableau.size(); i++)
    {
        cout<<"Affichage ("<<i+1<<")"<<std::endl;
        tableau[i]->afficheCaseXY(laby,0,0);
    }
    int numeroAffichage;
    do{
        cout<<"Numero de l'affichage choisi : ";
        cin>>numeroAffichage;
    }while(numeroAffichage<1 || numeroAffichage>3);
    return std::move(tableau[numeroAffichage-1]);
}

int selectionAlgorithme() //A TESTER
{
    cout<<"Selection de l'algorithme de sortie du robot"<<std::endl;
    cout<<"Algorithme (1) : Algorithme de la main droite"<<std::endl;
    cout<<"Le robot se deplace en ayant toujours un mur à sa droite (si au début il n’y a pas de mur à droite, il va tout droit jusqu’à rencontrer un mur)"<<std::endl;
    cout<<"Algorithme (2) : Algorithme de Pledge"<<std::endl;
    cout<<"Il consiste a :"<<std::endl;
    cout<<"1. Aller tout droit jusqu’au mur, ensuite passer à l'étape suivante"<<std::endl;
    cout<<"2. Longer le mur par la droite (ou par la gauche, mais toujours dans le même sens)"<<std::endl;
    cout<<"jusqu’à ce que le décompte des changements de direction atteigne zéro (tourner à gauche = +1, tourner à droite = -1), ensuite revenir à l'etape 1"<<std::endl;
    cout<<"Numero de l'algorithme choisi : ";
    int numeroAlgorithme;
    do{
        cout<<"Numero de l'algorithme choisi : ";
        cin>>numeroAlgorithme;
    }while(numeroAlgorithme!=1 && numeroAlgorithme!=2);
    return numeroAlgorithme;
}

void mainDroite(Robot &rob, const Labyrinthe &laby, const Affichage& aff)
{

}

void pledge(Robot &rob, const Labyrinthe &laby, const Affichage& aff)
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
