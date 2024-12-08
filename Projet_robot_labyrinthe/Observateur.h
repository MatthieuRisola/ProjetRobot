#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H


class Observateur {
public:
    virtual ~Observateur() = default;
    virtual void update(int x, int y, int direction) = 0;
};

class ObservateurAffichage : public Observateur {
public:
    void update(int x, int y, int direction) override;
};

class ObservateurComptageDeplacements : public Observateur {
public:
    ObservateurComptageDeplacements();
    void update(int x, int y, int direction) override;
    int nombreDeplacements() const;
private:
    int d_nombreDeplacements;
};

class ObservateurComptageDirections : public Observateur {
public:
	ObservateurComptageDirections();
void update(int x, int y, int direction) override;
    int nombreDirections() const;
private:
    int d_nombreDirections;
};


#endif // OBSERVATEUR_H
