#define DOCTEST_CONFIG_NO_MULTITHREADING
#include "doctest.h"
#include "Observateur.h"
#include "Affichage.h"
#include "Labyrinthe.h"

TEST_CASE("Observateur fonctionne")
{
    SUBCASE("ObservateurAffichage fonctionne"){
        //???
    }
    SUBCASE("ObservateurComptageDeplacements fonctionne"){
        int x=0;
        int y=0;
        ObservateurComptageDeplacements obs{x,y};
        SUBCASE("le constructeur fonctionne"){
            REQUIRE_EQ(obs.nombreDeplacements(),0);
        }
        SUBCASE("le compteur fonctionne"){
            SUBCASE("s'il n'y a pas de deplacement"){
                obs.update(x,y,0);
                REQUIRE_EQ(obs.nombreDeplacements(),0);
            }
            SUBCASE("s'il y a un deplacement en x"){
                obs.update(x+1,y,0);
                REQUIRE_EQ(obs.nombreDeplacements(),1);
            }
            SUBCASE("s'il y a un deplacement en y"){
                obs.update(x,y+1,0);
                REQUIRE_EQ(obs.nombreDeplacements(),1);
            }
        }
    }
    SUBCASE("ObservateurComptageDirections fonctionne"){
        int direction=0;
        ObservateurComptageDirections obs{direction};
        SUBCASE("le constructeur fonctionne"){
            REQUIRE_EQ(obs.nombreDirections(),0);
        }
        SUBCASE("le compteur fonctionne"){
            SUBCASE("s'il n'y a pas de changement"){
                obs.update(0,0,direction);
                REQUIRE_EQ(obs.nombreDirections(),0);
            }
            SUBCASE("s'il y a un changement"){
                obs.update(0,0,direction+1);
                REQUIRE_EQ(obs.nombreDirections(),1);
            }
        }
    }
}
