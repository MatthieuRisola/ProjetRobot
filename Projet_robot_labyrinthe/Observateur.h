#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

class Affichage;
class Labyrinthe;

class Observateur {
public:
    virtual ~Observateur() = default;
    virtual void update(int x, int y, int direction) = 0;
private:

};

class ObservateurAffichage : public Observateur {
public:
    ObservateurAffichage(const Affichage &affichage, const Labyrinthe &labyrinthe, int x, int y, int direction);
    void update(int x, int y, int direction) override;
private:
    const Affichage &d_affichage;
    const Labyrinthe &d_labyrinthe;
    int d_ancienX, d_ancienY, d_ancienneDirection;
};

class ObservateurComptageDeplacements : public Observateur {
public:
    ObservateurComptageDeplacements(int x, int y);
    void update(int x, int y, int direction) override;
    int nombreDeplacements() const;
private:
    int d_nombreDeplacements;
    int d_ancienX, d_ancienY;
};

class ObservateurComptageDirections : public Observateur {
public:
	ObservateurComptageDirections(int direction);
    void update(int x, int y, int direction) override;
    int nombreDirections() const;
private:
    int d_nombreDirections;
    int d_ancienneDirection;
};

#endif // OBSERVATEUR_H
