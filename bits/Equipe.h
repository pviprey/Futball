#ifndef EQUIPE_H
#define EQUIPE_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <array>
#include "Joueur.h"

class Equipe{
    public:
        Equipe(std::array<Joueur, 5>);
    private:
        std::array<Joueur, 5> composition;
};

inline Equipe::Equipe(std::array<Joueur, 5> composition):
    composition(composition)
    {}


#endif  //EQUIPE_H