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
#include <gf/ResourceManager.h>
#include <gf/Collision.h>

#include "Data.h"

#define GROUND_HEIGH 13
#define GROUND_LENGTH 29

class Terrain : public gf::Entity{
    public:
        Terrain(const gf::TextureAtlas& atlas, gf::ResourceManager& resources);

        std::vector<gf::RectF>& getHitboxs();
        std::vector<gf::RectF>& getGoals();
        gf::RectF getLeftGoal();
        gf::RectF getRightGoal();


        void setData();
        void render(gf::RenderTarget& target);
    private:
        gf::RectF hitboxTop,
        hitboxLeftTop,
        hitboxRightTop,

        hitboxBottom,
        hitboxLeftBottom,
        hitboxRightBottom,

        hitboxGoalLeft,
        hitboxGoalRight;

        std::vector<gf::RectF> hitboxs;
        std::vector<gf::RectF> goals;

        const gf::Texture& texture;

        gf::RectF LineVertical,
        LineVerticalDot,
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

        Circle3dTopCross,
        Circle3dTopRight,
        Circle3dRight,
        Circle3dBottomRight,
        Circle3dBottomCross,
        Circle3dBottomLeft,
        Circle3dLeft,
        Circle3dTopLeft,

        Ground;

        const gf::Texture& NetTopLeft;
        const gf::Texture& NetLeft;
        const gf::Texture& NetBottomLeft;
        const gf::Texture& NetTopRight;
        const gf::Texture& NetRight;
        const gf::Texture& NetBottomRight;

        enum class Texture{
            LineVertical,
            LineVerticalDot,
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

            Circle3dTopCross,
            Circle3dTopRight,
            Circle3dRight,
            Circle3dBottomRight,
            Circle3dBottomCross,
            Circle3dBottomLeft,
            Circle3dLeft,
            Circle3dTopLeft,

            NetTopLeft,
            NetLeft,
            NetBottomLeft,
            NetTopRight,
            NetRight,
            NetBottomRight,

            Ground
        };

        gf::Array2D<Texture, int> tiles;
};

#endif  //TERRAIN_H
