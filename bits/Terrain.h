#ifndef TERRAIN_H
#define TERRAIN_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <gf/Vector.h>
#include <gf/Entity.h>
#include <gf/TextureAtlas.h>
#include <gf/Array2D.h>
#include <gf/RenderTarget.h>

#include "Data.h"

#define GROUND_HEIGH 13
#define GROUND_LENGTH 27

class Terrain : public gf::Entity{
    public:
        Terrain(const gf::TextureAtlas& atlas);

        void setData();
        void render(gf::RenderTarget& target);        
    private:
        
        const gf::Texture& texture;

        gf::RectF LineVertical,
        LineHorizontal,
        LineTop,
        LineRight,
        LineBottom,
        LineLeft,

        TShapeTop,
        TShapeRight,
        TShapeBottom,
        TShapeLeft,

        CornerTopRight,
        CornerTopLeft,
        CornerBottomRight,
        CornerBottomLeft,

        Ground;

        enum class Texture{
            LineVertical,
            LineHorizontal,
            LineTop,
            LineRight,
            LineBottom,
            LineLeft,

            TShapeTop,
            TShapeRight,
            TShapeBottom,
            TShapeLeft,

            CornerTopLeft,
            CornerTopRight,
            CornerBottomRight,
            CornerBottomLeft,

            Ground
        };

        gf::Array2D<Texture, int> tiles;
};

#endif  //TERRAIN_H