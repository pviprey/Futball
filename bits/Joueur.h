#ifndef JOUEUR_H
#define JOUEUR_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <gf/Entity.h>
#include <gf/Vector.h>

class Joueur : public gf::Entity{
    public:
        Joueur(int, int);

        void deplacement();
    private:
        int poste;  //0: gardien, 1: defenseur, 2: attaquant
        int style;  //0: reculé, 1: normal, 2:avancé

        gf::Vector2f velocite;
        bool courir;

        gf::Vector2f position;
};

inline Joueur::Joueur(int poste, int style):
    poste(poste),
    style(style),
    velocite(0,0),
    courir(false)
    {}

#endif  //JOUEUR_H