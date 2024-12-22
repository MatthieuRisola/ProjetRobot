#include "Observateur.h"
#include "Labyrinthe.h"
#include "Affichage.h"
#include <iostream>

ObservateurAffichage::ObservateurAffichage(const Affichage &affichage, const Labyrinthe &labyrinthe, int x, int y, int direction) : d_affichage{affichage}, d_labyrinthe{labyrinthe}, d_ancienX{x}, d_ancienY{y}, d_ancienneDirection{direction}
{}

void ObservateurAffichage::update(int x, int y, int direction)
{
    d_affichage.update(d_labyrinthe, d_ancienX, d_ancienY, x, y, direction);
    d_ancienX=x;
    d_ancienY=y;
    d_ancienneDirection=direction;
}

ObservateurComptageDeplacements::ObservateurComptageDeplacements(int x, int y) : d_nombreDeplacements{0}, d_ancienX{x}, d_ancienY{y}
{}

void ObservateurComptageDeplacements::update(int x, int y, int direction)
{
    if(d_ancienX!=x||d_ancienY!=y){
        ++d_nombreDeplacements;
        d_ancienX=x;
        d_ancienY=y;
    }
}

int ObservateurComptageDeplacements::nombreDeplacements() const
{
    return d_nombreDeplacements;
}

ObservateurComptageDirections::ObservateurComptageDirections(int direction) : d_nombreDirections{0}, d_ancienneDirection{direction}
{}

void ObservateurComptageDirections::update(int x, int y, int direction)
{
        if(d_ancienneDirection!=direction){
            ++d_nombreDirections;
            d_ancienneDirection=direction;
    }
}

int ObservateurComptageDirections::nombreDirections() const
{
    return d_nombreDirections;
}
