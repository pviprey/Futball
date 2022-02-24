#ifndef BALLON_H
#define BALLON_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <gf/ResourceManager.h>
#include <gf/Entity.h>
#include <gf/Vector.h>

class Ballon : public gf::Entity{
    public:
        Ballon(gf::ResourceManager& resources);

        void update(gf::Time time);
        void render(gf::RenderTarget& target);        
    private:
        const gf::Texture& texture;

        gf::Vector2f position;
        gf::Vector2f velocite;

        bool pushed;
};

#endif  //BALLON_H