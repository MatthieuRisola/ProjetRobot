#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <memory>
#include "Observateur.h"

class Labyrinthe;
class Affichage;

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
private:
    int d_x, d_y, d_direction;
    std::vector<std::unique_ptr<Observateur>> d_observateurs;
    void notifieObservateurs();
};

/** REMARQUE 1 :
j'ai ajoute enum Direction HAUT, DROITE, BAS, GAUCHE **/

/** REMARQUE 2 :
pour Robot::afficher, je propose une methode Affichage::afficherRobot(const Robot& r) de sorte que :
    -   dans Robot::afficher : on fait juste aff.afficheRobot(*this);
    -   dans Affichage::afficherRobot(const Robot& r) : on fait ce qu'il faut pour mettre à jour l'ancienne case où était le robot
        et la nouvelle case où il y a le robot **/

/** REMARQUE 3 :
je n'ai pas fait enleverObservateur car je n'ai pas l'impression que ça va servir **/

/** 08/12/2024 ______________________________________________________________________________________________________________________________**/

/** REMARQUE 4 : changeDirection() pour pouvoir mieux factoriser les tests ? **/

/** REMARQUE 5 : debut de chaque classe en Majuscule **/

/** REMARQUE 6 : avancer -> avance, notifier -> notifie, tournerGauche->tourneGauche, etc.. **/

#endif // ROBOT_H
