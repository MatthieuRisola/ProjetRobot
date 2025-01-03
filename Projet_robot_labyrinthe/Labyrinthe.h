#ifndef LABYRINTHE_H
#define LABYRINTHE_H
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "Case.h"
#include "Affichage.h"
#include "Robot.h"

class Labyrinthe{
public:
    /**
    Constructeur qui initialise un labyrinthe vide
    */
    Labyrinthe();

    /**
    Charge un labyrinthe depuis un fichier texte
    @param fichier Chemin vers le fichier contenant la repr�sentation du labyrinthe
    @throw std::runtime_error si le fichier ne peut pas �tre ouvert
    @throw std::invalid_argument si le fichier contient des caract�res non valides
    */
    void lisDepuisFichier(const std::string& fichier);

    /**
    Sauvegarde le labyrinthe dans un fichier texte.
    @param fichier Chemin vers le fichier o� sauvegarder la repr�sentation du labyrinthe
    @throw std::runtime_error si le fichier ne peut pas �tre ouvert
    */
    void sauvegardeSur(const std::string& fichier) const;

    /**
    Affiche le labyrinthe sans le robot
    @param affichage Instance de la classe Affichage utilis�e pour effectuer l'affichage
    */
    void afficheSansRobot(const Affichage& affichage) const;

    /**
    Affiche le labyrinthe avec le robot
    @param affichage Instance de la classe Affichage utilis�e pour effectuer l'affichage
    @param robot R�f�rence vers l'objet Robot � afficher dans le labyrinthe
    */
    void afficheAvecRobot(const Affichage& affichage, const Robot& robot) const;

    /**
    V�rifie si le labyrinthe est valide, c'est-�-dire qu'il contient � la fois une case de d�part et une case d'arriv�e
    @return true si le labyrinthe est valide, false sinon
    */
    bool estValide() const;

    /**
    Retourne les informations sur la case situ�e aux coordonn�es (x, y)
    @param x Coordonn�e x (colonne) de la case
    @param y Coordonn�e y (ligne) de la case
    @return R�f�rence constante vers la case demand�e
    @throw std::out_of_range si les coordonn�es sont hors des limites du labyrinthe
    */
    const Case& informationCase(int x, int y) const;
    /**
    @param x Coordonn�e x (colonne) de la case
    @param y Coordonn�e y (ligne) de la case
    @return type d'une case situ�e aux coordonn�es (x, y)
    */
    Case::TypeCase typeCase(int x, int y) const;
    /**
    @return Cases du labyrinthe
    */
    const std::vector<std::vector<Case>>& cases() const;
    /**
    @return Largeur du labyrinthe
    */
    int largeur() const;

    /**
    @return Hauteur du labyrinthe
    */
    int hauteur() const;

private:
    /**
    Tableau de tableau repr�sentant les cases du labyrinthe
    */
    std::vector<std::vector<Case>> d_cases;
};

#endif // LABYRINTHE_H
