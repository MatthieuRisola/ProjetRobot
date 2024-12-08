#ifndef DEPLACEMENTROBOT_H_INCLUDED
#define DEPLACEMENTROBOT_H_INCLUDED

class Robot;

class RobotMover
{
    public:
        virtual ~RobotMover() = default;
        virtual void manipulate(Robot &r) const = 0;
};

class RobotAvance : public RobotMover
{
    public:
        void manipulate(Robot &r) const override;
};

class RobotGauche : public RobotMover
{
    public:
        void manipulate(Robot &r) const override;
};

class RobotDroit : public RobotMover
{
    public:
        void manipulate(Robot &r) const override;
};

/** CHANGEMENT
nom des classes mit en français pour être cohérent avec méthode de robot
*/



#endif // DEPLACEMENTROBOT_H_INCLUDED
