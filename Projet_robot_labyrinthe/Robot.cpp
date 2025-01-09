#include "Robot.h"
#include "Labyrinthe.h"
#include "Observateur.h"

Robot::Robot(int x, int y, int direction):d_x{x}, d_y{y}, d_direction{direction}
{}

int Robot::x() const
{
    return d_x;
}

int Robot::y() const
{
    return d_y;
}

int Robot::direction() const
{
    return d_direction;
}

bool Robot::obstacleDevant(const Labyrinthe& laby) const
{
    int x=d_x, y=d_y;
    switch(d_direction)
    {
      case HAUT : --y ; break;
      case DROITE : ++x ; break;
      case BAS : ++y ; break;
      case GAUCHE : --x ; break;
    }
    return laby.typeCase(x,y)==Case::TypeCase::Mur;
}


bool Robot::obstacleGauche(const Labyrinthe& laby) const
{
    int x=d_x, y=d_y;
    switch(d_direction)
    {
      case HAUT : --x ; break;
      case DROITE : --y ; break;
      case BAS : ++x ; break;
      case GAUCHE : ++y ; break;
    }
    return laby.typeCase(x,y)==Case::TypeCase::Mur;
}

bool Robot::obstacleDroite(const Labyrinthe& laby) const
{
    int x=d_x, y=d_y;
    switch(d_direction)
    {
      case HAUT : ++x ; break;
      case DROITE : ++y ; break;
      case BAS : --x ; break;
      case GAUCHE : --y ; break;
    }
    return laby.typeCase(x,y)==Case::TypeCase::Mur;
}

void Robot::avance()
{
    switch(d_direction)
    {
      case HAUT : --d_y ; break;
      case DROITE : ++d_x ; break;
      case BAS : ++d_y ; break;
      case GAUCHE : --d_x ; break;
    }
    notifieObservateurs();
}

void Robot::tourneGauche()
{
    switch(d_direction)
    {
      case HAUT : d_direction=GAUCHE ; break;
      case DROITE : d_direction=HAUT ; break;
      case BAS : d_direction=DROITE ; break;
      case GAUCHE : d_direction=BAS ; break;
    }
    notifieObservateurs();
}

void Robot::tourneDroite()
{
    switch(d_direction)
    {
      case HAUT : d_direction=DROITE ; break;
      case DROITE : d_direction=BAS ; break;
      case BAS : d_direction=GAUCHE ; break;
      case GAUCHE : d_direction=HAUT ; break;
    }
    notifieObservateurs();
}

void Robot::affiche(const Affichage &affichage) const
{
    affichage.afficheRobot(d_direction);
}

void Robot::ajouteObservateur(std::unique_ptr<Observateur> obs)
{
    d_observateurs.push_back(std::move(obs));
}


void Robot::notifieObservateurs()
{
    for(const auto& obs : d_observateurs)
    {
        obs->update(d_x,d_y,d_direction);
    }
}

int Robot::nombreDeplacements() const
{
    for (const auto& obs : d_observateurs) {
        auto obsDeplacements = dynamic_cast<ObservateurComptageDeplacements*>(obs.get());
        if (obsDeplacements) {
            return obsDeplacements->nombreDeplacements();
        }
    }
    return -1;
}

int Robot::nombreDirections() const
{
    for (const auto& obs : d_observateurs) {
        auto obsDeplacements = dynamic_cast<ObservateurComptageDirections*>(obs.get());
        if (obsDeplacements) {
            return obsDeplacements->nombreDirections();
        }
    }
    return -1;
}
