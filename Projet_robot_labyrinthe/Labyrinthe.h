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
    @param fichier Chemin vers le fichier contenant la représentation du labyrinthe
    @throw std::runtime_error si le fichier ne peut pas être ouvert
    @throw std::invalid_argument si le fichier contient des caractères non valides
    */
    void lisDepuisFichier(const std::string& fichier);

    /**
    Sauvegarde le labyrinthe dans un fichier texte.
    @param fichier Chemin vers le fichier où sauvegarder la représentation du labyrinthe
    @throw std::runtime_error si le fichier ne peut pas être ouvert
    */
    void sauvegardeSur(const std::string& fichier) const;

    /**
    Affiche le labyrinthe sans le robot
    @param affichage Instance de la classe Affichage utilisée pour effectuer l'affichage
    */
    void afficheSansRobot(const Affichage& affichage) const;

    /**
    Affiche le labyrinthe avec le robot
    @param affichage Instance de la classe Affichage utilisée pour effectuer l'affichage
    @param robot Référence vers l'objet Robot à afficher dans le labyrinthe
    */
    void afficheAvecRobot(const Affichage& affichage, const Robot& robot) const;

    /**
    Vérifie si le labyrinthe est valide, c'est-à-dire qu'il contient à la fois une case de départ et une case d'arrivée
    @return true si le labyrinthe est valide, false sinon
    */
    bool estValide() const;

    /**
    Retourne les informations sur la case située aux coordonnées (x, y)
    @param x Coordonnée x (colonne) de la case
    @param y Coordonnée y (ligne) de la case
    @return Référence constante vers la case demandée
    @throw std::out_of_range si les coordonnées sont hors des limites du labyrinthe
    */
    const Case& informationCase(int x, int y) const;
    /**
    @param x Coordonnée x (colonne) de la case
    @param y Coordonnée y (ligne) de la case
    @return type d'une case située aux coordonnées (x, y)
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
    Tableau de tableau représentant les cases du labyrinthe
    */
    std::vector<std::vector<Case>> d_cases;
};

#endif // LABYRINTHE_H
