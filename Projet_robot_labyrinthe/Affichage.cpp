#include "Affichage.h"
#include "goto_xy_windows.h"

void AffichageTexteSimple::afficheSansRobot(const Labyrinthe& labyrinthe) const
{
    for (int x=0; x<labyrinthe.hauteur(); ++x)
    {
        for (int y=0; y<labyrinthe.largeur(); ++y)
        {
            char symbole;
            switch(labyrinthe.typeCase(x,y))
            {
                case Case::Vide : symbole = '.';
                break;
                case Case::Mur : symbole = 'X';
                break;
                case Case::Depart : symbole = 'D';
                break;
                case Case::Arrivee : symbole = 'A';
                break;
            }
            std::cout << symbole;
        }
        std::cout << '\n';
    }
}

void AffichageTexteSimple::afficheDepart(const Labyrinthe& labyrinthe, const Robot& robot) const
{
    afficheSansRobot(labyrinthe);
    update(labyrinthe,0,0,robot.x(),robot.y(),robot.direction());
}

void AffichageTexteSimple::update(const Labyrinthe& labyrinthe, int ancienX, int ancienY, int nouveauX, int nouveauY, int direction) const
{
    //curseur(X = position largeur, Y = [position hauteur) dans cet ordre
    goto_xy(ancienX, ancienY);
    //laby[Y = position hauteur, X = position largeur] dans cet ordre
    switch (labyrinthe.typeCase(ancienY, ancienX))
    {
        case Case::Vide: std::cout << '.';
        break;
        case Case::Mur: std::cout << 'X';
        break;
        case Case::Depart: std::cout << 'D';
        break;
        case Case::Arrivee: std::cout << 'A';
        break;
    }
    goto_xy(nouveauX, nouveauY);

    switch (direction)
    {
        case Direction::HAUT: std::cout << '^';
        break;
        case Direction::DROITE: std::cout << '>';
        break;
        case Direction::BAS: std::cout << 'v';
        break;
        case Direction::GAUCHE: std::cout << '<';
        break;
    }
    goto_xy(labyrinthe.largeur(), labyrinthe.hauteur());
}

/*
modif inverser largeur et hauteur dans laffichage
ajout update texte simple
*/
