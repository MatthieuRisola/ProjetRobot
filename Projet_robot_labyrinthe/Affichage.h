#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "Labyrinthe.h"
#include "Robot.h"


class Affichage {
public:
    virtual ~Affichage() = default;

    //affichage du symbole une case
    virtual void afficheCaseXY(const Labyrinthe& labyrinthe, int x, int y) const = 0;

    //affichage du symbole du robot
    virtual void afficheRobot(int direction) const = 0;

    //affichage sans le robot pour la selection
    void afficheSansRobot(const Labyrinthe& labyrinthe) const;

    //affichage initial du labyrinthe
    void afficheDepart(const Labyrinthe& labyrinthe, const Robot& robot) const;

    //mise a jour du labyrinthe apres un deplacement du robot
    void update(const Labyrinthe& labyrinthe, int ancienX, int ancienY, int nouveauX, int nouveauY, int direction) const;
};


class AffichageTexteSimple : public Affichage {
public:
    void afficheCaseXY(const Labyrinthe& labyrinthe, int x, int y) const override;

    void afficheRobot(int direction) const override;
};

class AffichageTexteAmeliore1 : public Affichage {
public:
    void afficheCaseXY(const Labyrinthe& labyrinthe, int x, int y) const override;

    void afficheRobot(int direction) const override;
};

class AffichageTexteAmeliore2 : public Affichage {
public:
    void afficheCaseXY(const Labyrinthe& labyrinthe, int x, int y) const override;

    void afficheRobot(int direction) const override;
};

#endif // AFFICHAGE_H

/*
enleve r a la fin des methodes
*/
