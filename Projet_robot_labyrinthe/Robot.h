#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <memory>
#include "Observateur.h"

class Labyrinthe;
class Affichage;

enum Direction {HAUT = 1, DROITE = 2, BAS = 3, GAUCHE = 4};

class Robot {
public:

    Robot(int x, int y, int direction);
    int x() const;
    int y() const;
    int direction() const;
    bool obstacleDevant(const Labyrinthe& laby) const;
    bool obstacleGauche(const Labyrinthe& laby) const;
    bool obstacleDroite(const Labyrinthe& laby) const;

    void avance(); //TODO : factoriser
    void tourneGauche();
    void tourneDroite();

    void affiche(const Affichage &aff) const; //pas de test

    void ajouteObservateur(std::unique_ptr<Observateur> obs); //pas de test
    //void enleveObservateur(Observateur* obs); //TODO si nécessaire
    void notifieObservateurs(); //pas de test
private:
    int d_x, d_y, d_direction;
    std::vector<std::unique_ptr<Observateur>> d_observateurs;
};

#endif // ROBOT_H
