#define DOCTEST_CONFIG_NO_MULTITHREADING
#include "doctest.h"
#include "Robot.h"
#include "Labyrinthe.h"

#include <fstream>

// ATTENTION : au debut le robot ne peut pas changer sa direction

TEST_CASE("Robot fonctionne")
{
    SUBCASE("Robot est cree correctement avec les bonnes donnees")
    {
        int x{3}, y{5}, direction{GAUCHE};
        Robot r{x,y,direction};
        REQUIRE_EQ(r.x(),x);
        REQUIRE_EQ(r.y(),y);
        REQUIRE_EQ(r.direction(),direction);
    }
    SUBCASE("Robot verifie s'il y a un obstacle correctement")
    {
        int x{1}, y{1}, direction;
        std::string nomFichier{"testrobot.txt"};
        std::ofstream fichier{nomFichier};
        SUBCASE("Robot verifie correctement si obstacle devant lui")
        {
            SUBCASE("Robot détecte bien qu'il y a un obstacle devant lui")
            {
                SUBCASE("Robot détecte bien obstacle devant lui quand sa direction est HAUT")
                {
                    fichier<<".X."<<std::endl;
                    fichier<<"..."<<std::endl;
                    fichier<<"..."<<std::endl;
                    direction=HAUT;
                }
                SUBCASE("Robot détecte bien obstacle devant lui quand sa direction est DROITE")
                {
                    fichier<<"..."<<std::endl;
                    fichier<<"..X"<<std::endl;
                    fichier<<"..."<<std::endl;
                    direction=DROITE;
                }
                SUBCASE("Robot détecte bien obstacle devant lui quand sa direction est BAS")
                {
                    fichier<<"..."<<std::endl;
                    fichier<<"..."<<std::endl;
                    fichier<<".X."<<std::endl;
                    direction=BAS;
                }
                SUBCASE("Robot détecte bien obstacle devant lui quand sa direction est GAUCHE")
                {
                    fichier<<"..."<<std::endl;
                    fichier<<"X.."<<std::endl;
                    fichier<<"..."<<std::endl;
                    direction=GAUCHE;
                }
                Labyrinthe laby{};
                Robot r(x,y,direction);
                laby.lisDepuisFichier(nomFichier);
                REQUIRE_EQ(true, r.obstacleDevant(laby));
            }
            SUBCASE("Robot détecte bien qu'il n'y a pas un obstacle devant lui")
            {
                SUBCASE("Robot détecte bien pas d'obstacle devant lui quand sa direction est HAUT")
                {
                    fichier<<"X.X"<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    direction=HAUT;
                }
                SUBCASE("Robot détecte bien pas d'obstacle devant lui quand sa direction est DROITE")
                {
                    fichier<<"XXX"<<std::endl;
                    fichier<<"XX."<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    direction=DROITE;
                }
                SUBCASE("Robot détecte bien pas d'obstacle devant lui quand sa direction est BAS")
                {
                    fichier<<"XXX"<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    fichier<<"X.X"<<std::endl;
                    direction=BAS;
                }
                SUBCASE("Robot détecte bien d'obstacle devant lui quand sa direction est GAUCHE")
                {
                    fichier<<"XXX"<<std::endl;
                    fichier<<".XX"<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    direction=GAUCHE;
                }
                Labyrinthe laby{};
                Robot r(x,y,direction);
                laby.lisDepuisFichier(nomFichier);
                REQUIRE_EQ(false, r.obstacleDevant(laby));
            }
        }
        SUBCASE("Robot verifie correctement si obstacle à sa gauche")
        {
            SUBCASE("Robot detecte qu'il y a bien un obstacle à sa gauche")
            {
                SUBCASE("Robot detecte qu'il y a bien un obstacle à sa gauche quand sa direction est HAUT")
                {
                    fichier<<"..."<<std::endl;
                    fichier<<"X.."<<std::endl;
                    fichier<<"..."<<std::endl;
                    direction=HAUT;
                }
                SUBCASE("Robot detecte qu'il y a bien un obstacle à sa gauche quand sa direction est DROITE")
                {
                    fichier<<".X."<<std::endl;
                    fichier<<"..."<<std::endl;
                    fichier<<"..."<<std::endl;
                    direction=DROITE;
                }
                SUBCASE("Robot detecte qu'il y a bien un obstacle à sa gauche quand sa direction est BAS")
                {
                    fichier<<"..."<<std::endl;
                    fichier<<"..X"<<std::endl;
                    fichier<<"..."<<std::endl;
                    direction=BAS;
                }
                SUBCASE("Robot detecte qu'il y a bien un obstacle à sa gauche quand sa direction est GAUCHE")
                {
                    fichier<<"..."<<std::endl;
                    fichier<<"..."<<std::endl;
                    fichier<<".X."<<std::endl;
                    direction=GAUCHE;
                }
                Labyrinthe laby{};
                Robot r(x,y,direction);
                laby.lisDepuisFichier(nomFichier);
                REQUIRE_EQ(true, r.obstacleGauche(laby));
            }
            SUBCASE("Robot detecte bien qu'il n'y a pas obstacle à sa gauche")
            {
                SUBCASE("Robot detecte bien qu'il y a pas un obstacle à sa gauche quand sa direction est HAUT")
                {
                    fichier<<"XXX"<<std::endl;
                    fichier<<".XX"<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    direction=HAUT;
                }
                SUBCASE("Robot detecte bien qu'il y a pas un obstacle à sa gauche quand sa direction est DROITE")
                {
                    fichier<<"X.X"<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    direction=DROITE;
                }
                SUBCASE("Robot detecte bien qu'il y a pas un obstacle à sa gauche quand sa direction est BAS")
                {
                    fichier<<"XXX"<<std::endl;
                    fichier<<"XX."<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    direction=BAS;
                }
                SUBCASE("Robot detecte bien qu'il y a pas un obstacle à sa gauche quand sa direction est GAUCHE")
                {
                    fichier<<"XXX"<<std::endl;
                    fichier<<"XXX"<<std::endl;
                    fichier<<"X.X"<<std::endl;
                    direction=GAUCHE;
                }
                Labyrinthe laby{};
                Robot r(x,y,direction);
                laby.lisDepuisFichier(nomFichier);
                REQUIRE_EQ(false, r.obstacleGauche(laby));
            }
        }
        SUBCASE("Robot verifie correctement si obstacle à sa droite")
        {

        }
    }
    SUBCASE("Robot avance correctement selon sa direction") //TODO : factoriser par Robot r{x,y,direction} si possible
    {
        int x{3}, y{5}, direction, xFinal{x}, yFinal{y};

        SUBCASE("Robot avance vers le haut correctement")
        {
            direction=HAUT;
            --yFinal;
        }
        SUBCASE("Robot avance vers sa droite correctement")
        {
            direction=DROITE;
            ++xFinal;
        }
        SUBCASE("Robot avance vers le bas correctement")
        {
            direction=BAS;
            ++yFinal;
        }
        SUBCASE("Robot avance vers sa gauche correctement")
        {
            direction=GAUCHE;
            --xFinal;
        }
        Robot r{x,y,direction};
        r.avance();
        REQUIRE_EQ(r.x(), xFinal);
        REQUIRE_EQ(r.y(), yFinal);
    }
    SUBCASE("Robot change de direction correctement")
    {
        int x{3}, y{5}, ancienneDirection, nouvelleDirection;
        SUBCASE("Robot tourne a gauche correctement")
        {
            SUBCASE("Robot tourne a gauche quand il avait pour direction HAUT correctement")
            {
                ancienneDirection=HAUT;
                nouvelleDirection=GAUCHE;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction DROITE correctement")
            {
                ancienneDirection=DROITE;
                nouvelleDirection=HAUT;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction BAS correctement")
            {
                ancienneDirection=BAS;
                nouvelleDirection=DROITE;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction GAUCHE correctement")
            {
                ancienneDirection=GAUCHE;
                nouvelleDirection=BAS;
            }
            Robot r(x,y,ancienneDirection);
            r.tourneGauche();
            REQUIRE_EQ(r.direction(), nouvelleDirection);
        }
        SUBCASE("Robot tourne a droite correctement")
        {
            int x{3}, y{5}, ancienneDirection, nouvelleDirection;
            SUBCASE("Robot tourne a gauche quand il avait pour direction HAUT correctement")
            {
                ancienneDirection=HAUT;
                nouvelleDirection=DROITE;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction DROITE correctement")
            {
                ancienneDirection=DROITE;
                nouvelleDirection=BAS;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction BAS correctement")
            {
                ancienneDirection=BAS;
                nouvelleDirection=GAUCHE;
            }
            SUBCASE("Robot tourne a gauche quand il avait pour direction GAUCHE correctement")
            {
                ancienneDirection=GAUCHE;
                nouvelleDirection=HAUT;
            }
            Robot r(x,y,ancienneDirection);
            r.tourneDroite();
            REQUIRE_EQ(r.direction(), nouvelleDirection);
        }
    }
}

TEST_CASE("Robot renvoie les donnees correctes")
{
    int x{5}, y{6}, direction{HAUT};
    Robot r(x,y,direction);
    SUBCASE("Robot donne sa coordonnée x correcte")
    {
        REQUIRE_EQ(x, r.x());
    }
    SUBCASE("Robot donne sa coordonnée y correcte")
    {
        REQUIRE_EQ(y, r.y());
    }
    SUBCASE("Robot donne sa direction correctement")
    {
        REQUIRE_EQ(direction, r.direction());
    }
}
