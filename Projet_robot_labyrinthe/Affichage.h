#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "Labyrinthe.h"
#include "Robot.h"


class Affichage {
public:
    virtual ~Affichage() = default;

    //affichage sans le robot pour la selection
    virtual void afficheSansRobot(const Labyrinthe& labyrinthe) const = 0;

    //affichage initial du labyrinthe
    virtual void afficheDepart(const Labyrinthe& labyrinthe, const Robot& robot) const = 0;

    //mise a jour du labyrinthe apres un deplacement du robot
    virtual void update(const Labyrinthe& labyrinthe, int ancienX, int ancienY, int nouveauX, int nouveauY, int direction) const = 0;
};


class AffichageTexteSimple : public Affichage {
public:
    void afficheSansRobot(const Labyrinthe& labyrinthe) const override;

    void afficheDepart(const Labyrinthe& labyrinthe, const Robot& robot) const override;

    void update(const Labyrinthe& labyrinthe, int ancienX, int ancienY, int nouveauX, int nouveauY, int direction) const override;
};



#endif // AFFICHAGE_H

/*
enleve r a la fin des methodes
*/
