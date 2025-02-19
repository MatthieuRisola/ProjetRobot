#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

#include<string>

class Case
{
    public:
        enum TypeCase {Vide, Mur, Depart, Arrivee};
        Case();
        Case(const TypeCase& type);
        TypeCase type() const;
        std::string typeEnChaine() const;
        void changeType(const TypeCase& type);
    private:
        TypeCase d_type;
};

#endif // CASE_H_INCLUDED
