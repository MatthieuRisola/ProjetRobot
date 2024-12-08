#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

#include<string>

class Case
{
    public:
        enum TypeCase {Vide, Mur, Depart, Arrivee};
        Case(const TypeCase& type);
        TypeCase type() const;
        void changeType(const TypeCase& type);
    private:
        TypeCase d_type;
};

/** CHANGEMENT

changement ent�te constructeur -> rajout de const et &
changement ent�te m�thode type() -> renvoit string et pas un TypeCase
ajout m�thode changeType()

*/

#endif // CASE_H_INCLUDED
