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
        Joueur(int poste, int style, gf::ResourceManager& resources);

        void setPosition(gf::Vector2f);
        void setPosition(float posX, float posY);
        void setPositionY(float posY);

        bool getCurrent();
        void setCurrent();
        void removeCurrent();
        void switchCurrent(Joueur& Joueur);

        enum class Poste{
            Gardien,
            Defenseur,
            Attaquant
        };
        Poste getPoste() const;

        void deplacement(gf::Event event);
        void update(gf::Time time);
        void render(gf::RenderTarget& target);
    private:

        const gf::Texture& texture;

        enum class Style{
            Recule,
            Normal,
            Avance
        };

        Poste poste;  //0: gardien, 1: defenseur, 2: attaquant
        Style style;  //0: reculé, 1: normal, 2:avancé

        gf::Vector2f velocite;
        gf::Vector2f position;

        bool current;
};

#endif  //JOUEUR_H