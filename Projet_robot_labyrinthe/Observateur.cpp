#include "Observateur.h"

ObservateurComptageDeplacements::ObservateurComptageDeplacements() : d_nombreDeplacements{0}
{}

void ObservateurComptageDeplacements::update(int x, int y, int direction)
{
    ++d_nombreDeplacements;
}

int ObservateurComptageDeplacements::nombreDeplacements() const
{
    return d_nombreDeplacements;
}

ObservateurComptageDirections::ObservateurComptageDirections() : d_nombreDirections{0}
{}

void ObservateurComptageDirections::update(int x, int y, int direction)
{
    ++d_nombreDirections;
}

int ObservateurComptageDirections::nombreDirections() const
{
    return d_nombreDirections;
}
