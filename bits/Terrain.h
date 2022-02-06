#ifndef TERRAIN_H
#define TERRAIN_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <gf/Entity.h>
#include <gf/Vector.h>
#include <gf/TextureAtlas.h>
#include <gf/Array2D.h>

class Terrain : public gf::Entity{
    public:
        Terrain();
        Terrain(const gf::TextureAtlas& atlas);

        void render(gf::RenderTarget& target, const gf::RenderStates& states) override;        
    private:

        enum class Textures{
            Lines,
            TShape,
            LShape,
            Ground,
            Net
        };

        const gf::Texture& texture;
        gf::Array2D<Textures, int> tiles;     
};

#endif  //TERRAIN_H