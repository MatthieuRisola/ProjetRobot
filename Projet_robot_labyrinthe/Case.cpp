#include "Case.h"

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

 void Case::changeType(const TypeCase& type)
 {
     d_type=type;
 }
