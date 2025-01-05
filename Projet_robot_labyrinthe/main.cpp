#include <iostream>
#include "Labyrinthe.h"
#include <conio.h>
#include "Observateur.h"
#include <vector>
#include "Affichage.h"
#include "DeplacementRobot.h"

using std::cout;
using std::cin;

const int NUMERO_MAIN_DROITE=1;
const int NUMERO_PLEDGE=1;

Labyrinthe selectionLabyrinthe()
{
    std::string nomFichier;
    cout<<"Entrer le nom du fichier contenant le labyrinthe : ";
    cin>>nomFichier;
    Labyrinthe laby{};
    laby.lisDepuisFichier(nomFichier);
    while(laby.estValide()==false)
    {
        cout<<"Labyrinthe invalide, il manque une case de depart ou une case arrivee"<<std::endl;
        cout<<"Entrer le nom du fichier contenant le labyrinthe : ";
        cin>>nomFichier;
        laby.lisDepuisFichier(nomFichier);
    }
    return laby;
}

std::unique_ptr<Affichage> selectionAffichage(const Labyrinthe &laby) //TO DO : pb d'affichage du texte et des differents affichages
{
    cout<<"Choix de l'affichage du labyrinthe :"<<std::endl;
    std::vector<std::unique_ptr<Affichage>> tableau{};
    tableau.reserve(3);
    tableau.push_back(std::make_unique<AffichageTexteSimple>());
    tableau.push_back(std::make_unique<AffichageTexteAmeliore1>());
    tableau.push_back(std::make_unique<AffichageTexteAmeliore2>());
    Robot r{0,0,HAUT};
    for(int i{0}; i<tableau.size(); i++)
    {
        cout<<"Affichage ("<<i+1<<")"<<std::endl;
        tableau[i]->afficheSansRobot(laby);
        cout<<std::endl;
    }
    int numeroAffichage;
    do{
        cout<<"Numero de l'affichage choisi : ";
        cin>>numeroAffichage;
    }while(numeroAffichage<1 || numeroAffichage>3);
    //cout<<"Numero choisi :"<<numeroAffichage; //pour le test
    return std::move(tableau[numeroAffichage-1]);
}

int selectionAlgorithme()
{
    cout<<"Selection de l'algorithme de sortie du robot"<<std::endl;
    cout<<"Algorithme (1) : Algorithme de la main droite"<<std::endl;
    cout<<"Le robot se deplace en ayant toujours un mur a sa droite (si au debut il n'y a pas de mur a droite, il va tout droit jusqu'a rencontrer un mur)"<<std::endl;
    cout<<"Algorithme (2) : Algorithme de Pledge"<<std::endl;
    cout<<"Il consiste a :"<<std::endl;
    cout<<"1. Aller tout droit jusqu'au mur, ensuite passer a l'etape suivante"<<std::endl;
    cout<<"2. Longer le mur par la droite (ou par la gauche, mais toujours dans le meme sens)"<<std::endl;
    cout<<"jusqu'a ce que le decompte des changements de direction atteigne zero (tourner a gauche = +1, tourner a droite = -1), ensuite revenir a l'etape 1"<<std::endl;
    int numeroAlgorithme;
    do{
        cout<<"Numero de l'algorithme choisi : ";
        cin>>numeroAlgorithme;
    }while(numeroAlgorithme!=1 && numeroAlgorithme!=2);
    return numeroAlgorithme;
}

/** Test sur selectionAlgorithme
        test avec un numero invalide (différent de 1 et 2)
        test avec numero valide (1 ou 2)
        test redemande le nom du fichier quand le fichier n'a pas une case arrivee ou une case depart
**/
void testSelectionAlgorithme()
{
    int numeroAlgo{selectionAlgorithme()};
    cout<<"Algo choisi final : "<<numeroAlgo;
}

/** Test sur selectionLabyrinthe
    nom de fichier qui n'existe pas
    nom de fichier qui existe
**/
void testSelectionLabyrinthe()
{
    Labyrinthe laby{selectionLabyrinthe()};
}

/** Test sur selectionAffichage
        test avec numero invalide (différent de 1, 2 et 3)
        test avec numero valide (1, 2 ou 3)
**/
void testSelectionAffichage()
{
    Labyrinthe laby{selectionLabyrinthe()};
    selectionAffichage(laby);
}

void mainDroite(Robot &rob, const Labyrinthe &laby, const Affichage& aff)
{

}

void pledge(Robot &rob, const Labyrinthe &laby, const Affichage& aff)
{

}

void initialisationLabyrinthe(Robot &rob, const Labyrinthe &laby, bool &robotCorrect)
{
    int x,y, i{0}, j{0};
    bool departTrouve=false;
    while((j<laby.hauteur()) && (departTrouve == false))
    {
        i=0;
        while((i<laby.largeur()) && (departTrouve==false))
        {
            if(laby.typeCase(i,j) == Case::TypeCase::Depart)
            {
                x=i;
                y=j;
                departTrouve=true;
            }
            ++i;
        }
        ++j;
    }
    rob = Robot{x,y,HAUT};
    RobotDroit robotD{};
    int compteurNombreTours{0};
    while(compteurNombreTours<4 && rob.obstacleDevant(laby) == true)
    {
        robotD.manipulate(rob);
        ++compteurNombreTours;
    }
    if(compteurNombreTours<4)
    {
        robotCorrect=true;
    }
    else
    {
        robotCorrect=false;
    }
}

void programmePrincipal()
{
    Labyrinthe laby{selectionLabyrinthe()};
    Robot rob{0,0,HAUT};
    bool robotCorrect{false};
    initialisationLabyrinthe(rob,laby,robotCorrect);

    while(robotCorrect==false)
    {
        cout<<"Labyrinthe selectionne est invalide, le robot ne peut se deplacer"<<std::endl;
        laby=selectionLabyrinthe();
        initialisationLabyrinthe(rob, laby, robotCorrect);
    }

    std::unique_ptr<Affichage> affichage{selectionAffichage(laby)};
    int numeroAlgo{selectionAlgorithme()};

    if(numeroAlgo == NUMERO_MAIN_DROITE)
    {
        mainDroite(rob,laby,*affichage);
    }
    else //numeroAlgo == NUMERO_PLEDGE
    {
        pledge(rob,laby,*affichage);
    }
}

/** Tests sur le programme principal dont initialisationLabyrinthe
    test avec la case depart a differents endroits,la direction initiale de robot est initialise correctement en correlation avec le labyrinthe
    test la position (x,y) de robot est bien initialisee
    test le bon algo est lance apres le choix de l'utilisateur
**/
void testProgrammePrincipal()
{
    programmePrincipal();
}

int main()
{
    //testSelectionAlgorithme();
    //testSelectionLabyrinthe();
    //testSelectionAffichage();

    //testProgrammePrincipal();

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
