#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "Labyrinthe.h"

Labyrinthe::Labyrinthe() : d_cases{}
{}

// Lecture depuis un fichier
void Labyrinthe::lisDepuisFichier(const std::string& fichier) {
    std::ifstream file(fichier);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir fichier : "+fichier);
    }

    d_cases.clear(); // Vider les ancinnes données
    std::string ligne;

    while (std::getline(file, ligne)) {
        std::vector<std::unique_ptr<Case>> ligneCases;
        for (char c : ligne) {
            switch (c) {
                case 'X': ligneCases.push_back(std::make_unique<Case>(Case::Mur)); break;
                case '.': ligneCases.push_back(std::make_unique<Case>(Case::Vide)); break;
                case 'D': ligneCases.push_back(std::make_unique<Case>(Case::Depart)); break;
                case 'A': ligneCases.push_back(std::make_unique<Case>(Case::Arrivee)); break;
                default:
                    throw std::invalid_argument("Caractère invalide:" + std::string(1, c));
            }
        }
        d_cases.push_back(std::move(ligneCases));
    }
}

// Sauvegarde dans un fichier
/*
void Labyrinthe::sauvegardeSur(const std::string& fichier) const {
    std::ofstream file(fichier);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + fichier);
    }
    for (const auto& ligne : d_cases) {
        for (const auto& casePtr : ligne) {
            switch (casePtr->type()) {
                case Case::Mur: file << "X"; break;
                case Case::Vide: file << "."; break;
                case Case::Depart: file << "D"; break;
                case Case::Arrivee: file << "A"; break;
            }
        }
        file << '\n';
    }
}
*/

// Affichage sans robot
void Labyrinthe::afficheSansRobot(const Affichage& affichage) const {
    affichage.afficheSansRobot(*this);
}

// Affichage avec robot
void Labyrinthe::afficheAvecRobot(const Affichage& affichage, const Robot& robot) const {
    affichage.afficheDepart(*this, robot);
}

// Vérification de validité du labyrinthe
/*
bool Labyrinthe::estValide() const {
    bool departTrouvee = false, arriveeTrouvee = false;
    for (const auto& ligne : d_cases) {
        for (const auto& casePtr : ligne) {
            if (casePtr->type() == Case::Depart) departTrouvee = true;
            if (casePtr->type() == Case::Arrivee) arriveeTrouvee = true;
        }
    }
    return departTrouvee && arriveeTrouvee;
}
*/

// Récupération d'informations sur une case
const Case& Labyrinthe::informationCase(int x, int y) const {
// x doit être compris entre 0 et la largeur du labyrinthe (d_cases[0].size() - 1),
// y doit être compris entre 0 et la hauteur du labyrinthe (d_cases.size() - 1).
    if (x<0||x>=d_cases[0].size()||y < 0||y >=d_cases.size()) {
        throw std::out_of_range("Coordonnée hors des limites du labyrinthe.");
    }
    return *d_cases[y][x];
}

Case::TypeCase Labyrinthe::typeCase(int x, int y) const
{
    return d_cases[x][y]->type();
}

// Affichage du nombre de cases parcourues
/*
void Labyrinthe::afficheNombreCasesParcourues() const {
    int casesParcourues=0;
    for (const auto& ligne : d_cases) {
        for (const auto& casePtr : ligne) {
            if (casePtr->type() == Case::Vide) {
                ++casesParcourues;
            }
        }
    }
    std::cout << "Nombre de cases parcourues : " << casesParcourues << '\n';
}
*/

int Labyrinthe::largeur() const
{
    return d_cases[0].size();
}

int Labyrinthe::hauteur() const
{
    return d_cases.size();
}
