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
#include "Terrain.h"
#include "Ballon.h"

class Equipe{
    public:
        Equipe(bool sens);
        Equipe(std::vector<Joueur> equipe, bool sens);

        bool addJoueur(int poste, int style,  gf::ResourceManager& resources);

        void engagement(bool possession);

        std::vector<Joueur>& getJoueurs();
        void switchCurrentToClosest(Ballon& ballon);

        void deplacement(gf::Event event);
        void update(gf::Time time);
        void render(gf::RenderTarget& target);

        void isDefending(Ballon& ballon, Terrain& terrain);
        void isAttacking();
    private:
        std::vector<Joueur> composition;
        bool sens;

        bool addJoueur(const Joueur& joueur);
        bool hasGoal();
        void disposition();
};

#endif  //EQUIPE_H