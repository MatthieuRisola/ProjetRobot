#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

#include "Labyrinthe.h"
#include "Observateur.h"
#include "Affichage.h"
#include "DeplacementRobot.h"
#include "Robot.h"

using std::cout;
using std::cin;

const int NUMERO_MAIN_DROITE=1;
const int NUMERO_PLEDGE=2;

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

void initialisationRobot(Robot &rob, const Labyrinthe &laby, const Affichage &aff)
{
    auto obsAffichage = std::make_unique<ObservateurAffichage>(aff, laby, rob.x(), rob.y(), rob.direction());
    auto obsDeplacements = std::make_unique<ObservateurComptageDeplacements>(rob.x(), rob.y());
    auto obsDirections = std::make_unique<ObservateurComptageDirections>(rob.direction());
    rob.ajouteObservateur(std::move(obsAffichage));
    rob.ajouteObservateur(std::move(obsDeplacements));
    rob.ajouteObservateur(std::move(obsDirections));
}


void mainDroite(Robot &rob, const Labyrinthe &laby, const Affichage& aff)
{
    auto obsAffichage = std::make_unique<ObservateurAffichage>(aff, laby, rob.x(), rob.y(), rob.direction());
    auto obsDeplacements = std::make_unique<ObservateurComptageDeplacements>(rob.x(), rob.y());
    auto obsDirections = std::make_unique<ObservateurComptageDirections>(rob.direction());
    rob.ajouteObservateur(std::move(obsAffichage));
    rob.ajouteObservateur(std::move(obsDeplacements));
    rob.ajouteObservateur(std::move(obsDirections));

    RobotAvance avance{};
    RobotDroit droit{};
    RobotGauche gauche{};

    aff.afficheDepart(laby, rob);
    std::cout << "Appuyez sur espace pour commencer" << std::endl;
    getch();
    system("cls");
    aff.afficheDepart(laby, rob);

    int max_iteration = 1000;
    int it = 0;

    // Avancer tout droit jusqu'à rencontrer un mur à droite (si il n'y avait pas de mur au depart)
    while (it < max_iteration && !rob.obstacleDroite(laby)) //si pas d'obstacle à droite
    {
        //on avance tout droit si pas d'obstacle
        if (!rob.obstacleDevant(laby))
        {
            avance.manipulate(rob);
        }
        else
        {
            gauche.manipulate(rob); // Tourner à gauche si bloqué devant
        }

        it++;
    }

    // Suivre le mur à droite
    bool sortieTrouvee = false;
    while (it < max_iteration && !sortieTrouvee)
    {
        if (laby.typeCase(rob.x(), rob.y()) == Case::Arrivee) //peut être bien de faire une fonction qui teste direct case du robot sans avoir besoin d'acceder a ses coordonnees ?
        {
            sortieTrouvee = true;
            continue; // Arrêt logique
        }

        if (!rob.obstacleDroite(laby))
        {
            droit.manipulate(rob); // On tourne à droite car pas d'obstacle et on avance
            avance.manipulate(rob);
        }
        else
            if (!rob.obstacleDevant(laby))
            {
                avance.manipulate(rob); // il y a un obstacle à droite mais pas devant donc on avance devant
            }
            else
            {
                gauche.manipulate(rob); //il y a un obstacle à droite et devant donc on tourne à gauche
            }

        it++;
    }

    if(it>= max_iteration)
        std::cout << "Maximum d'iteration atteint, ce type d'algorithme n'est pas compatible avec ce labyrinthe" << std::endl;
    else
        std::cout << "Le robot a trouvé l'arrivee ! " << std::endl;
    std::cout << "Nombre total de déplacements : " << rob.nombreDeplacements() << std::endl;
    std::cout << "Nombre total de changements de direction : " << rob.nombreDirections() << std::endl;
    std::cout << "Temps d'éxécution : " << (rob.nombreDeplacements()+rob.nombreDirections())*0.11 << " secondes" << std::endl;
}

void pledge(Robot &rob, const Labyrinthe &laby, const Affichage& aff)
{
    auto obsAffichage = std::make_unique<ObservateurAffichage>(aff, laby, rob.x(), rob.y(), rob.direction());
    auto obsDeplacements = std::make_unique<ObservateurComptageDeplacements>(rob.x(), rob.y());
    auto obsDirections = std::make_unique<ObservateurComptageDirections>(rob.direction());
    rob.ajouteObservateur(std::move(obsAffichage));
    rob.ajouteObservateur(std::move(obsDeplacements));
    rob.ajouteObservateur(std::move(obsDirections));

    RobotAvance avance{};
    RobotDroit droit{};
    RobotGauche gauche{};

    aff.afficheDepart(laby, rob);
    std::cout << "Appuyez sur espace pour commencer" << std::endl;
    getch();
    system("cls");
    aff.afficheDepart(laby, rob);
    int max_iteration = 1000;
    int it = 0;
    int compteur = 0;
    while (it < max_iteration&&laby.typeCase(rob.x(), rob.y()) != Case::Arrivee){
        if (compteur == 0){
            if (!rob.obstacleDevant(laby))
                avance.manipulate(rob);
            else{
                droit.manipulate(rob);
                ++compteur;
            }
        }
        else if (!rob.obstacleGauche(laby)) {
                gauche.manipulate(rob);
                --compteur;
                avance.manipulate(rob);
        }
        else if (!rob.obstacleDevant(laby))
            avance.manipulate(rob);
        else{
            droit.manipulate(rob);
            ++compteur;
        }
        it++;
    }

    if(it>= max_iteration)
        std::cout << "Maximum d'iteration atteint, ce type d'algorithme n'est pas compatible avec ce labyrinthe" << std::endl;
    else
        std::cout << "Le robot a trouvé la sortie !" << std::endl;
    std::cout << "Nombre total de déplacements : " << rob.nombreDeplacements() << std::endl;
    std::cout << "Nombre total de changements de direction : " << rob.nombreDirections() << std::endl;
    std::cout << "Temps d'éxécution : " << (rob.nombreDeplacements()+rob.nombreDirections())*0.11 << " secondes" << std::endl;
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
    rob = Robot{x,y,BAS};
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
    Robot rob{0,0,BAS};
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

void testAlgoMainDroite()
{
    Labyrinthe laby{};
    AffichageTexteAmeliore2 aff{};
    laby.lisDepuisFichier("testmaindroite.txt");
    Robot rob{0,0,HAUT};
    bool coucou=true;
    initialisationLabyrinthe(rob,laby,coucou);
    mainDroite(rob,laby,aff);
}

void testPledge()
{
    Labyrinthe laby{};
    AffichageTexteAmeliore2 aff{};
    laby.lisDepuisFichier("testpledge.txt");
    Robot rob{0,0,HAUT};
    bool coucou=true;
    initialisationLabyrinthe(rob,laby,coucou);
    pledge(rob,laby,aff);
}

int main()
{
    SetConsoleOutputCP(65001);
    //testSelectionAlgorithme();
    //testSelectionLabyrinthe();
    //testSelectionAffichage();

    //testProgrammePrincipal();
    testAlgoMainDroite();
    //testPledge();
}
