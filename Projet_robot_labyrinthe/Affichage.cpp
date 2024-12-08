#include "Affichage.h"

void AffichageTexteSimple::afficherSansRobot(const Labyrinthe& labyrinthe) const
{
    for (int x=0; x<labyrinthe.largeur(); ++x)
    {
        for (int y=0; y<labyrinthe.hauteur(); ++y)
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
