#include "Case.h"

Case::Case():
    d_type{Case::Vide}
{}

Case::Case(const TypeCase& type):
    d_type{type}
{}

Case::TypeCase Case::type() const
{
    switch(d_type)
    {
        case Vide : return Case::Vide;
        case Mur : return Case::Mur;
        case Depart : return Case::Depart;
        case Arrivee : return Case::Arrivee;
    }
}

std::string Case::typeEnChaine() const
{
    switch (d_type)
    {
        case Case::Vide: return "Vide";
        case Case::Mur: return "Mur";
        case Case::Depart: return "Depart";
        case Case::Arrivee: return "Arrivee";
    }
}

 void Case::changeType(const TypeCase& type)
 {
     d_type=type;
 }
