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

    Robot(int x, int y, int direction); //test ecrit
    int x() const;
    int y() const;
    int direction() const;
    bool obstacleDevant(const Labyrinthe& laby) const;
    bool obstacleGauche(const Labyrinthe& laby) const;
    bool obstacleDroite(const Labyrinthe& laby) const;

    void avance(); //test ecrit, TODO : factoriser
    void tourneGauche(); //test ecrit
    void tourneDroite(); //test ecrit

    void affiche(const Affichage &aff);

    void ajouteObservateur(std::unique_ptr<Observateur> obs);
    //void enleveObservateur(Observateur* obs); //TODO si nécessaire
    void notifieObservateurs();
private:
    int d_x, d_y, d_direction;
    std::vector<std::unique_ptr<Observateur>> d_observateurs;
};

#endif // ROBOT_H
