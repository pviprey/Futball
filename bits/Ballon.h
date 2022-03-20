#ifndef BALLON_H
#define BALLON_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <gf/ResourceManager.h>
#include <gf/Entity.h>
#include <gf/Vector.h>
#include <gf/Circ.h>
#include <gf/Collision.h>


class Ballon : public gf::Entity{
    public:
        Ballon(gf::ResourceManager& resources);

        void engagement();

        gf::CircF getHitbox() const;
        bool getPushed() const;

        void update(gf::Time time);
        void interact(gf::Penetration penetration, gf::Vector2f deplacement, bool marche);
        void interact(gf::Penetration penetration);
        void render(gf::RenderTarget& target);

    private:
        const gf::Texture& texture;

        float norm;
        gf::Vector2f velocite;

        gf::CircF hitbox;

        bool pushed;
        bool marche;
        float depth_marche;
};

#endif  //BALLON_H
