#include "Affichage.h"
#include "goto_xy_windows.h"


void Affichage::afficheDepart(const Labyrinthe& labyrinthe, const Robot& robot) const
{
    afficheSansRobot(labyrinthe);
    update(labyrinthe,0,0,robot.x(),robot.y(),robot.direction());
}

void Affichage::update(const Labyrinthe& labyrinthe, int ancienX, int ancienY, int nouveauX, int nouveauY, int direction) const
{
    //curseur(X = position largeur, Y = [position hauteur) dans cet ordre
    goto_xy(ancienX, ancienY);
    //laby[Y = position hauteur, X = position largeur] dans cet ordre
    afficheCaseXY(labyrinthe,ancienX,ancienY);
    goto_xy(nouveauX, nouveauY);
    afficheRobot(direction);
    goto_xy(0, labyrinthe.hauteur());
}

void AffichageTexteSimple::afficheCaseXY(const Labyrinthe& labyrinthe, int x, int y) const
{
    Case::TypeCase c=labyrinthe.typeCase(x,y);
    char symbole;
    switch(c)
    {
        case Case::Vide : symbole = '.';
        break;
        case Case::Mur : symbole = 'X';
        break;
        case Case::Depart : symbole = 'D';
        break;
        case Case::Arrivee : symbole = 'A';
        break;
    }
    std::cout << symbole;
}

void AffichageTexteSimple::afficheRobot(int direction) const
{
    switch (direction)
    {
        case Direction::HAUT: std::cout << '^';
        break;
        case Direction::DROITE: std::cout << '>';
        break;
        case Direction::BAS: std::cout << 'v';
        break;
        case Direction::GAUCHE: std::cout << '<';
        break;
    }
}

void Affichage::afficheSansRobot(const Labyrinthe& labyrinthe) const
{
    for (int y=0; y<labyrinthe.hauteur(); ++y)
    {
        for (int x=0; x<labyrinthe.largeur(); ++x )
            afficheCaseXY(labyrinthe,x,y);
        std::cout << '\n';
    }
}

//renvoie vrai si la case est en dehors du labyrinthe ou est un mur
bool estMur(const Labyrinthe& labyrinthe, int x, int y)
{
    return x < 0 || x >= labyrinthe.largeur() || y < 0 || y >= labyrinthe.hauteur() || labyrinthe.typeCase(x, y) == Case::Mur;
}

void AffichageTexteAmeliore1::afficheCaseXY(const Labyrinthe& labyrinthe, int x, int y) const
{
    Case::TypeCase c=labyrinthe.typeCase(x,y);
    char symbole;
    switch(c)
    {
        case Case::Vide : symbole = '.';
        break;
        case Case::Mur : {
            //information des cases autour
            bool gauche = estMur(labyrinthe, x-1, y);
            bool droite = estMur(labyrinthe, x+1, y);
            bool haut = estMur(labyrinthe, x, y-1);
            bool bas = estMur(labyrinthe, x, y+1);
            bool hautGauche = estMur(labyrinthe, x-1, y-1);
            bool hautDroite = estMur(labyrinthe, x+1, y-1);
            bool basGauche = estMur(labyrinthe, x-1, y+1);
            bool basDroite = estMur(labyrinthe, x+1, y+1);

            //choix par defaut
            symbole = '+';
            if(haut) {
                if(bas) {
                    if(gauche) {
                        if(droite) {
                            if(hautGauche)
                                if(hautDroite)
                                    if(basGauche)
                                        if(basDroite)
                                            //toutes les cases autour sont des murs
                                            symbole = '#';
                        }
                        else if(hautGauche&&basGauche)
                            symbole = '|';
                    }
                    else if(droite){
                        if(hautDroite&&basDroite)
                            symbole = '|';
                    }
                    else
                        symbole = '|';
                }
                else if(gauche){
                    if(droite)
                        if(hautGauche&&hautDroite)
                            symbole = '-';
                }
                else if(!droite)
                    symbole ='|';
            }
            else if(bas){
                if(gauche){
                    if(droite)
                        if(basGauche&&basDroite)
                            symbole = '-';
                }
                else if(!droite)
                    symbole ='|';
            }
            else if(gauche||droite)
                symbole='-';
        }
        break;
        case Case::Depart : symbole = 'D';
        break;
        case Case::Arrivee : symbole = 'A';
        break;
    }
    std::cout << symbole;
}

void AffichageTexteAmeliore1::afficheRobot(int direction) const
{
    switch (direction)
    {
        case Direction::HAUT: std::cout << '^';
        break;
        case Direction::DROITE: std::cout << '>';
        break;
        case Direction::BAS: std::cout << 'v';
        break;
        case Direction::GAUCHE: std::cout << '<';
        break;
    }
}

void AffichageTexteAmeliore2::afficheCaseXY(const Labyrinthe& labyrinthe, int x, int y) const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Case::TypeCase c=labyrinthe.typeCase(x,y);
    wchar_t symbole;
    switch(c)
    {
        case Case::Vide : symbole = '.';
        break;
        case Case::Mur : {
            //information des cases autour
            bool gauche = estMur(labyrinthe, x-1, y);
            bool droite = estMur(labyrinthe, x+1, y);
            bool haut = estMur(labyrinthe, x, y-1);
            bool bas = estMur(labyrinthe, x, y+1);
            bool hautGauche = estMur(labyrinthe, x-1, y-1);
            bool hautDroite = estMur(labyrinthe, x+1, y-1);
            bool basGauche = estMur(labyrinthe, x-1, y+1);
            bool basDroite = estMur(labyrinthe, x+1, y+1);

            //choix par defaut
            symbole = L'┼';
            if(haut) {
                if(bas) {
                    if(gauche) {
                        if(droite) {
                            if(hautGauche){
                                if(hautDroite){
                                    if(basGauche){
                                        if(basDroite)
                                            //toutes les cases autour sont des murs
                                            symbole = L'█';
                                        else
                                            symbole=L'┌';
                                    }
                                    else if(basDroite)
                                        symbole=L'┐';
                                    else
                                        symbole = L'┬';
                                }
                                else if(basGauche){
                                    if(basDroite)
                                        symbole=L'└';
                                    else
                                        symbole=L'├';
                                }
                            }
                            else if(hautDroite){
                                if(basGauche){
                                    if(basDroite)
                                        symbole = L'┘';
                                }
                                else if(basDroite)
                                    symbole = L'┤';
                            }
                            else if(basGauche&&basDroite)
                                symbole = L'┴';
                        }
                        else if(hautGauche&&basGauche)
                            symbole = L'│';
                        else
                            symbole = L'┤';
                    }
                    else if(droite){
                        if(hautDroite&&basDroite)
                            symbole = L'│';
                        else
                            symbole = L'├';
                    }
                    else
                        symbole = L'│';
                }
                else if(gauche){
                    if(droite){
                        if(hautGauche&&hautDroite)
                            symbole = L'─';
                        else
                            symbole=L'┴';
                    }
                    else
                        symbole = L'┘';
                }
                else if(droite)
                    symbole=L'└';
                else
                    symbole =L'│';
            }
            else if(bas){
                if(gauche){
                    if(droite)
                        if(basGauche&&basDroite)
                            symbole = L'─';
                        else
                            symbole = L'┬';
                    else
                        symbole = L'┐';
                }
                else if(droite)
                    symbole = L'┌';
                else
                    symbole =L'│';
            }
            else if(gauche||droite)
                symbole=L'─';
            else
                symbole=L'○';
        }
        break;
        case Case::Depart : symbole = 'D';
        break;
        case Case::Arrivee : symbole = 'A';
        break;
    }
    DWORD written;
    WriteConsoleW(hConsole, &symbole, 1, &written, NULL);
}

void AffichageTexteAmeliore2::afficheRobot(int direction) const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    wchar_t symbole;
    switch (direction)
    {
        case Direction::HAUT: symbole = L'▲';
        break;
        case Direction::DROITE: symbole = L'►';
        break;
        case Direction::BAS: symbole = L'▼';
        break;
        case Direction::GAUCHE: symbole = L'◄';
        break;
    }
    DWORD written;
    WriteConsoleW(hConsole, &symbole, 1, &written, NULL);
}
