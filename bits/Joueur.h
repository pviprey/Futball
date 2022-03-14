#ifndef JOUEUR_H
#define JOUEUR_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <gf/Entity.h>
#include <gf/Vector.h>
#include <gf/Event.h>
#include <gf/Time.h>
#include <gf/RenderWindow.h>
#include <gf/ResourceManager.h>
#include <gf/Circ.h>
#include <gf/Collision.h>

namespace{
    static constexpr float SPEED = 160.0f;
}

class Joueur : public gf::Entity{
    public:
        Joueur(int poste, int style, gf::ResourceManager& resources, bool sens);

        void setPosition(gf::Vector2f);
        void setPosition(float posX, float posY);
        void setPositionY(float posY);

        bool getMarche();

        gf::Vector2f getVelocite();

        bool getCurrent();
        void switchCurrentTo(Joueur& Joueur);

        enum class Poste{
            Gardien,
            Defenseur,
            Attaquant
        };
        Poste getPoste() const;

        gf::CircF getHitbox() const;

        void deplacement(gf::Event event);
        void update(gf::Time time);
        void interact(gf::Penetration penetration);
        void render(gf::RenderTarget& target);
    private:
        void setCurrent();
        void removeCurrent();

        const gf::Texture *texture;
        bool sens;

        enum class Style{
            Recule,
            Normal,
            Avance
        };

        Poste poste;  //0: gardien, 1: defenseur, 2: attaquant
        Style style;  //0: reculé, 1: normal, 2:avancé

        bool marche;

        gf::Vector2f velocite;

        gf::CircF hitbox;

        bool current;
        bool interacting;

        // gf::Vector2f mousePosition;
};

#endif  //JOUEUR_H