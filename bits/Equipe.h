#ifndef EQUIPE_H
#define EQUIPE_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <vector>

#include <gf/Event.h>
#include <gf/RenderTarget.h>
#include <gf/Time.h>

#include "Joueur.h"

class Equipe{
    public:
        Equipe();
        Equipe(std::vector<Joueur> equipe);

        bool addJoueur(const Joueur& joueur);
        bool addJoueur(int poste, int style,  gf::ResourceManager& resources);

        void deplacement(gf::Event event);
        void render(gf::RenderTarget& target);
        void update(gf::Time time);        
    private:
        std::vector<Joueur> composition;

        bool hasGoal();

        void disposition();
};

#endif  //EQUIPE_H