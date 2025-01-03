#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "Labyrinthe.h"

Labyrinthe::Labyrinthe() : d_cases{}
{}

void Labyrinthe::lisDepuisFichier(const std::string& fichier) {
    std::ifstream file(fichier);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir fichier : "+fichier);
    }

    d_cases.clear(); // Vider les anciennes données
    std::string ligne;

    while (std::getline(file, ligne)) {
        std::vector<Case> ligneCases;
        for (char c : ligne) {
            if (c == '\r' || c == '\n' || c == ' ') {
            continue; // Ignorer les retours à la ligne et espaces
            }
            switch (c) {
                case 'X': ligneCases.push_back(Case::Mur); break;
                case '.': ligneCases.push_back(Case::Vide); break;
                case 'D': ligneCases.push_back(Case::Depart); break;
                case 'A': ligneCases.push_back(Case::Arrivee); break;
                default:
                    throw std::invalid_argument("Caractère invalide: '" + std::string(1, c) + "' à la position " + std::to_string(d_cases.size()) + "," + std::to_string(ligneCases.size()));
            }
        }
        d_cases.push_back(ligneCases);
    }
}


void Labyrinthe::sauvegardeSur(const std::string& fichier) const {
    std::ofstream file(fichier);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + fichier);
    }
    for (const auto& ligne : d_cases) {
        for (const auto& casexy : ligne) {
            switch (casexy.type()) {
                case Case::Mur: file << "X"; break;
                case Case::Vide: file << "."; break;
                case Case::Depart: file << "D"; break;
                case Case::Arrivee: file << "A"; break;
            }
        }
        file << '\n';
    }
}


void Labyrinthe::afficheSansRobot(const Affichage& affichage) const {
    affichage.afficheSansRobot(*this);
}


void Labyrinthe::afficheAvecRobot(const Affichage& affichage, const Robot& robot) const {
    affichage.afficheDepart(*this, robot);
}

bool Labyrinthe::estValide() const {
    bool departTrouvee = false, arriveeTrouvee = false;
    for (const auto& ligne : d_cases) {
        for (const auto& casexy : ligne) {
            if (casexy.type() == Case::Depart) departTrouvee = true;
            if (casexy.type() == Case::Arrivee) arriveeTrouvee = true;
        }
    }
    return departTrouvee && arriveeTrouvee;
}

const Case& Labyrinthe::informationCase(int x, int y) const {
// x doit être compris entre 0 et la largeur du labyrinthe (d_cases[0].size() - 1),
// y doit être compris entre 0 et la hauteur du labyrinthe (d_cases.size() - 1).
    if (x<0||x>=d_cases[0].size()||y < 0||y >=d_cases.size()) {
        throw std::out_of_range("Coordonnée hors des limites du labyrinthe.");
    }
    return d_cases[y][x];
}

Case::TypeCase Labyrinthe::typeCase(int x, int y) const
{
    return d_cases[y][x].type();
}

const std::vector<std::vector<Case>>& Labyrinthe::cases() const
{
    return d_cases;
}

int Labyrinthe::largeur() const
{
    return d_cases[0].size();
}

int Labyrinthe::hauteur() const
{
    return d_cases.size();
}
