#ifndef JOUEUR_H
#define JOUEUR_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <gf/Entity.h>
#include <gf/Vector.h>
#include <gf/Event.h>
#include <gf/Time.h>
#include <gf/ResourceManager.h>


class Joueur : public gf::Entity{
    public:
        Joueur(int, int, gf::ResourceManager& resources);

        void deplacement(gf::Event event);
        void render(gf::RenderTarget& target);
        void update(gf::Time time);
    private:
        const gf::Texture& texture;

        int poste;  //0: gardien, 1: defenseur, 2: attaquant
        int style;  //0: reculé, 1: normal, 2:avancé

        gf::Vector2f velocite;
        gf::Vector2f position;

        bool current;
};

#endif  //JOUEUR_H