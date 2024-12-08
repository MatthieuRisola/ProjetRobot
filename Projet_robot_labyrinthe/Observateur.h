#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

class Observateur {
public:
    virtual ~Observateur() = default;
    virtual void update(int x, int y, int direction) = 0;
};

/*
class ObservateurAffichage : public Observateur {
public:
    void update(int x, int y, int direction) override;
};
*/

//observateur pour lalgorithme principal
class ObservateurComptageDeplacements : public Observateur {
public:
    ObservateurComptageDeplacements();
    void update(int x, int y, int direction) override;
    int nombreDeplacements() const;
private:
    int d_nombreDeplacements;
};

//observateur pour lalgorithme principal
class ObservateurComptageDirections : public Observateur {
public:
	ObservateurComptageDirections();
    void update(int x, int y, int direction) override;
    int nombreDirections() const;
private:
    int d_nombreDirections;
};

//observateur necessaire pour mettre a jour laffichage
class ObservateurDernierePosition : public Observateur {
public:
    ObservateurDernierePosition();
    void update(int x, int y);
    int dernierX();
    int dernierY();
private:
    int d_x, d_y;
};

#endif // OBSERVATEUR_H
