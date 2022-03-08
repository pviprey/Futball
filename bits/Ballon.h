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

        gf::CircF getHitbox() const;

        void update(gf::Time time);
        void interact(gf::Penetration penetration, gf::Vector2f deplacement);
        void render(gf::RenderTarget& target);        
    private:
        const gf::Texture& texture;

        gf::Vector2f velocite;

        gf::CircF hitbox;

        bool pushed;
};

#endif  //BALLON_H