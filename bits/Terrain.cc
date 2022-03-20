#include <gf/Sprite.h>

#include <gf/Color.h>
#include <gf/AssetManager.h>
#include <gf/Shapes.h>

#include "Terrain.h"

#define GUILLEMET '\''

namespace{
    const char TERRAIN[] =
        " O------------Y------------P "
        " |            '            ! "
        " G            '            D "
        " |            '            ! "
        " |            '            ! "
        "W|           1A2           !X"
        "#|   .       (.)       .   !="
        "V|           4a3           !C"
        " |            '            ! "
        " |            '            ! "
        " G            '            D "
        " |            '            ! "
        " L____________y____________M "
    ;
    constexpr gf::Vector2i TERRAINSIZE = gf::vec(GROUND_LENGTH, GROUND_HEIGH);
    constexpr gf::Vector2f SpriteSize(64.0f, 64.0f);
}

Terrain::Terrain(const gf::TextureAtlas& atlas, gf::ResourceManager& resources):gf::Entity(1),
    hitboxTop(gf::RectF::fromPositionSize(gf::Vector2f{-GROUND_LENGTH*64/2, -GROUND_HEIGH*64/2-15}, gf::Vector2f{GROUND_LENGTH*64, 22})),
    hitboxLeftTop(gf::RectF::fromPositionSize(gf::Vector2f{-GROUND_LENGTH*64/2, -GROUND_HEIGH*64/2-15}, gf::Vector2f{70, (GROUND_HEIGH-8)*64+47})),
    hitboxRightTop(gf::RectF::fromPositionSize(gf::Vector2f{GROUND_LENGTH*64/2-70, -GROUND_HEIGH*64/2-15}, gf::Vector2f{70, (GROUND_HEIGH-8)*64+47})),

    hitboxBottom(gf::RectF::fromPositionSize(gf::Vector2f{-GROUND_LENGTH*64/2, GROUND_HEIGH*64/2-7}, gf::Vector2f{GROUND_LENGTH*64, 22})),
    hitboxLeftBottom(gf::RectF::fromPositionSize(gf::Vector2f{-GROUND_LENGTH*64/2, GROUND_HEIGH*64/2+15-(GROUND_HEIGH-8)*64-47}, gf::Vector2f{70, (GROUND_HEIGH-7)*64-17})),
    hitboxRightBottom(gf::RectF::fromPositionSize(gf::Vector2f{GROUND_LENGTH*64/2-70, GROUND_HEIGH*64/2+15-(GROUND_HEIGH-8)*64-47}, gf::Vector2f{70, (GROUND_HEIGH-7)*64-17})),

    hitboxGoalLeft(gf::RectF::fromPositionSize(gf::Vector2f{-GROUND_LENGTH*64/2, -64}, gf::Vector2f{70, 64*2})),
    hitboxGoalRight(gf::RectF::fromPositionSize(gf::Vector2f{GROUND_LENGTH*64/2-70, -64}, gf::Vector2f{70, 64*2})),

    hitboxs(),

    texture(atlas.getTexture()),

    LineVertical(atlas.getTextureRect("Centerred_Vertical_Line.png")),
    LineVerticalDot(atlas.getTextureRect("Centerred_Vertical_Line_Dot.png")),
    LineHorizontal(atlas.getTextureRect("Centerred_Horizontal_Line.png")),
    LineTop(atlas.getTextureRect("Top_Line.png")),
    LineRight(atlas.getTextureRect("Right_Line.png")),
    LineBottom(atlas.getTextureRect("Bottom_Line.png")),
    LineLeft(atlas.getTextureRect("Left_Line.png")),

    TShapeTop(atlas.getTextureRect("Top_TShape.png")),
    TShapeRight(atlas.getTextureRect("Right_TShape.png")),
    TShapeBottom(atlas.getTextureRect("Bottom_TShape.png")),
    TShapeLeft(atlas.getTextureRect("Left_TShape.png")),

    CornerTopRight(atlas.getTextureRect("TopRight_Corner.png")),
    CornerTopLeft(atlas.getTextureRect("TopLeft_Corner.png")),
    CornerBottomRight(atlas.getTextureRect("BottomRight_Corner.png")),
    CornerBottomLeft(atlas.getTextureRect("BottomLeft_Corner.png")),

    Circle3dTopCross(atlas.getTextureRect("Top_Circle3d_Middle_Line.png")),
    Circle3dTopRight(atlas.getTextureRect("TopRight_Circle3d.png")),
    Circle3dRight(atlas.getTextureRect("Right_Circle3d.png")),
    Circle3dBottomRight(atlas.getTextureRect("BottomRight_Circle3d.png")),
    Circle3dBottomCross(atlas.getTextureRect("Bottom_Circle3d_Middle_Line.png")),
    Circle3dBottomLeft(atlas.getTextureRect("BottomLeft_Circle3d.png")),
    Circle3dLeft(atlas.getTextureRect("Left_Circle3d.png")),
    Circle3dTopLeft(atlas.getTextureRect("TopLeft_Circle3d.png")),

    Ground(atlas.getTextureRect("Ground.png")),

    NetTopLeft(resources.getTexture("Elements/TopLeft_Net.png")),
    NetLeft(resources.getTexture("Elements/Left_Net.png")),
    NetBottomLeft(resources.getTexture("Elements/BottomLeft_Net.png")),
    NetTopRight(resources.getTexture("Elements/TopRight_Net.png")),
    NetRight(resources.getTexture("Elements/Right_Net.png")),
    NetBottomRight(resources.getTexture("Elements/BottomRight_Net.png")),
    
    tiles(TERRAINSIZE)
    {
        hitboxs.push_back(hitboxTop);
        hitboxs.push_back(hitboxLeftTop);
        hitboxs.push_back(hitboxRightTop);
        hitboxs.push_back(hitboxBottom);
        hitboxs.push_back(hitboxLeftBottom);
        hitboxs.push_back(hitboxRightBottom);

        goals.push_back(hitboxGoalLeft);
    }

std::vector<gf::RectF>& Terrain::getHitboxs(){
    return hitboxs;
}

std::vector<gf::RectF>& Terrain::getGoals(){
    return goals;
}

gf::RectF Terrain::getLeftGoal(){
    return hitboxGoalLeft;
}

gf::RectF Terrain::getRightGoal(){
    return hitboxGoalRight;
}

void Terrain::setData() {
    std::vector<gf::RectF> hitboxs{hitboxTop, hitboxLeftTop, hitboxRightTop, hitboxBottom, hitboxLeftBottom, hitboxRightBottom};

    Data tb = Data(TERRAIN, TERRAINSIZE);

    for (auto coords : tiles.getPositionRange()) {
        switch (tb(coords)) {
            case GUILLEMET:
                tiles(coords) = Texture::LineVertical;
                break;
            case '.':
                tiles(coords) = Texture::LineVerticalDot;
                break;
            case '-':
                tiles(coords) = Texture::LineTop;
                break;
            case '!':
                tiles(coords) = Texture::LineRight;
                break;
            case '_':
                tiles(coords) = Texture::LineBottom;
                break;
            case '|':
                tiles(coords) = Texture::LineLeft;
                break;
            case 'Y':
                tiles(coords) = Texture::TShapeTop;
                break;
            case 'D':
                tiles(coords) = Texture::TShapeRight;
                break;
            case 'y':
                tiles(coords) = Texture::TShapeBottom;
                break;
            case 'G':
                tiles(coords) = Texture::TShapeLeft;
                break;


            case 'O':
                tiles(coords) = Texture::CornerTopLeft;
                break;
            case 'P':
                tiles(coords) = Texture::CornerTopRight;
                break;
            case 'M':
                tiles(coords) = Texture::CornerBottomRight;
                break;
            case 'L':
                tiles(coords) = Texture::CornerBottomLeft;
                break;


            case 'A':
                tiles(coords) = Texture::Circle3dTopCross;
                break;
            case '2':
                tiles(coords) = Texture::Circle3dTopRight;
                break;
            case ')':                
                tiles(coords) = Texture::Circle3dRight;
                break;
            case '3':
                tiles(coords) = Texture::Circle3dBottomRight;
                break;
            case 'a':
                tiles(coords) = Texture::Circle3dBottomCross;
                break;
            case '4':
                tiles(coords) = Texture::Circle3dBottomLeft;
                break;
            case '(':    
                tiles(coords) = Texture::Circle3dLeft;
                break;
            case '1':    
                tiles(coords) = Texture::Circle3dTopLeft;
                break;


            case 'W':
                tiles(coords) = Texture::NetBottomRight;
                break;
            case 'X':
                tiles(coords) = Texture::NetBottomLeft;
                break;
            case '=':
                tiles(coords) = Texture::NetLeft;
                break;
            case 'C':
                tiles(coords) = Texture::NetTopLeft;
                break;
            case 'V':
                tiles(coords) = Texture::NetTopRight;
                break;
            case '#':
                tiles(coords) = Texture::NetRight;
                break;                                                                


            case ' ':
            default:
                tiles(coords) = Texture::Ground;
                break;
        }
    }
}

void Terrain::render(gf::RenderTarget& target) {
    for(auto coords : tiles.getPositionRange()) {
        gf::Sprite sprite(texture);
        sprite.setTextureRect(Ground);
        sprite.setPosition((coords * SpriteSize)-TERRAINSIZE*SpriteSize/2);
        sprite.setAnchor(gf::Anchor::TopLeft);
        target.draw(sprite);
    }


    for (auto coords : tiles.getPositionRange()) {
        gf::Sprite sprite(texture);

        switch (tiles(coords)) {

            case Texture::LineVertical:
                sprite.setTextureRect(LineVertical);
                break; 
            case Texture::LineVerticalDot:
                sprite.setTextureRect(LineVerticalDot);
                break;
            case Texture::LineHorizontal:
                break;            
            case Texture::LineTop:
                sprite.setTextureRect(LineTop);
                break;            
            case Texture::LineRight:
                sprite.setTextureRect(LineRight);
                break;            
            case Texture::LineBottom:
                sprite.setTextureRect(LineBottom);
                break;            
            case Texture::LineLeft:
                sprite.setTextureRect(LineLeft);
                break;            


            case Texture::TShapeTop:
                sprite.setTextureRect(TShapeTop);
                break;
            case Texture::TShapeRight:
                sprite.setTextureRect(TShapeRight);
                break;            
            case Texture::TShapeBottom:
                sprite.setTextureRect(TShapeBottom);
                break;
            case Texture::TShapeLeft:
                sprite.setTextureRect(TShapeLeft);
                break;


            case Texture::CornerTopLeft:
                sprite.setTextureRect(CornerTopLeft);
                break;              
            case Texture::CornerTopRight:
                sprite.setTextureRect(CornerTopRight);
                break;              
            case Texture::CornerBottomRight:
                sprite.setTextureRect(CornerBottomRight);
                break;              
            case Texture::CornerBottomLeft:
                sprite.setTextureRect(CornerBottomLeft);
                break;  


            case Texture::Circle3dTopCross:
                sprite.setTextureRect(Circle3dTopCross);
                break;
            case Texture::Circle3dTopRight:
                sprite.setTextureRect(Circle3dTopRight);
                break;
            case Texture::Circle3dRight:
                sprite.setTextureRect(Circle3dRight);
                break;
            case Texture::Circle3dBottomRight:
                sprite.setTextureRect(Circle3dBottomRight);
                break;
            case Texture::Circle3dBottomCross:
                sprite.setTextureRect(Circle3dBottomCross);
                break;
            case Texture::Circle3dBottomLeft:
                sprite.setTextureRect(Circle3dBottomLeft);
                break;
            case Texture::Circle3dLeft:
                sprite.setTextureRect(Circle3dLeft);
                break;
            case Texture::Circle3dTopLeft:
                sprite.setTextureRect(Circle3dTopLeft);
                break;


            case Texture::NetBottomRight:
                sprite.setTexture(NetBottomRight);
                break;
            case Texture::NetBottomLeft:
                sprite.setTexture(NetBottomLeft);
                break;
            case Texture::NetLeft:
                sprite.setTexture(NetLeft);
                break;
            case Texture::NetTopLeft:
                sprite.setTexture(NetTopLeft);
                break;
            case Texture::NetTopRight:
                sprite.setTexture(NetTopRight);
                break;
            case Texture::NetRight:
                sprite.setTexture(NetRight);
                break;


            // case Texture::Ground:
            //     sprite.setTextureRect(Ground);
            //     break;  

            default:
                continue;
        }

        sprite.setPosition((coords * SpriteSize)-TERRAINSIZE*SpriteSize/2);
        sprite.setAnchor(gf::Anchor::TopLeft);
        target.draw(sprite);

        //debug
        gf::RectangleShape hitboxShapeTop;
        hitboxShapeTop.setPosition(hitboxTop.getCenter());
        hitboxShapeTop.setSize(hitboxTop.getSize());
        hitboxShapeTop.setColor(gf::Color::Transparent);
        hitboxShapeTop.setOutlineColor(gf::Color::Green);
        hitboxShapeTop.setOutlineThickness(1.5f);
        hitboxShapeTop.setAnchor(gf::Anchor::Center);
        target.draw(hitboxShapeTop);
        
        gf::RectangleShape hitboxShapeLeftTop;
        hitboxShapeLeftTop.setPosition(hitboxLeftTop.getCenter());
        hitboxShapeLeftTop.setSize(hitboxLeftTop.getSize());
        hitboxShapeLeftTop.setColor(gf::Color::Transparent);
        hitboxShapeLeftTop.setOutlineColor(gf::Color::Green);
        hitboxShapeLeftTop.setOutlineThickness(1.5f);
        hitboxShapeLeftTop.setAnchor(gf::Anchor::Center);
        target.draw(hitboxShapeLeftTop);

        gf::RectangleShape hitboxShapeRightTop;
        hitboxShapeRightTop.setPosition(hitboxRightTop.getCenter());
        hitboxShapeRightTop.setSize(hitboxRightTop.getSize());
        hitboxShapeRightTop.setColor(gf::Color::Transparent);
        hitboxShapeRightTop.setOutlineColor(gf::Color::Green);
        hitboxShapeRightTop.setOutlineThickness(1.5f);
        hitboxShapeRightTop.setAnchor(gf::Anchor::Center);
        target.draw(hitboxShapeRightTop);

        gf::RectangleShape hitboxShapeBottom;
        hitboxShapeBottom.setPosition(hitboxBottom.getCenter());
        hitboxShapeBottom.setSize(hitboxBottom.getSize());
        hitboxShapeBottom.setColor(gf::Color::Transparent);
        hitboxShapeBottom.setOutlineColor(gf::Color::Green);
        hitboxShapeBottom.setOutlineThickness(1.5f);
        hitboxShapeBottom.setAnchor(gf::Anchor::Center);
        target.draw(hitboxShapeBottom);

        gf::RectangleShape hitboxShapeLeftBottom;
        hitboxShapeLeftBottom.setPosition(hitboxLeftBottom.getCenter());
        hitboxShapeLeftBottom.setSize(hitboxLeftBottom.getSize());
        hitboxShapeLeftBottom.setColor(gf::Color::Transparent);
        hitboxShapeLeftBottom.setOutlineColor(gf::Color::Green);
        hitboxShapeLeftBottom.setOutlineThickness(1.5f);
        hitboxShapeLeftBottom.setAnchor(gf::Anchor::Center);
        target.draw(hitboxShapeLeftBottom);

        gf::RectangleShape hitboxShapeRightBottom;
        hitboxShapeRightBottom.setPosition(hitboxRightBottom.getCenter());
        hitboxShapeRightBottom.setSize(hitboxRightBottom.getSize());
        hitboxShapeRightBottom.setColor(gf::Color::Transparent);
        hitboxShapeRightBottom.setOutlineColor(gf::Color::Green);
        hitboxShapeRightBottom.setOutlineThickness(1.5f);
        hitboxShapeRightBottom.setAnchor(gf::Anchor::Center);
        target.draw(hitboxShapeRightBottom);

        gf::RectangleShape hitboxShapeGoalLeft;
        hitboxShapeGoalLeft.setPosition(hitboxGoalLeft.getCenter());
        hitboxShapeGoalLeft.setSize(hitboxGoalLeft.getSize());
        hitboxShapeGoalLeft.setColor(gf::Color::Violet);
        hitboxShapeGoalLeft.setOutlineColor(gf::Color::Violet);
        hitboxShapeGoalLeft.setOutlineThickness(1.5f);
        hitboxShapeGoalLeft.setAnchor(gf::Anchor::Center);
        target.draw(hitboxShapeGoalLeft);

        gf::RectangleShape hitboxShapeGoalRight;
        hitboxShapeGoalRight.setPosition(hitboxGoalRight.getCenter());
        hitboxShapeGoalRight.setSize(hitboxGoalRight.getSize());
        hitboxShapeGoalRight.setColor(gf::Color::Violet);
        hitboxShapeGoalRight.setOutlineColor(gf::Color::Violet);
        hitboxShapeGoalRight.setOutlineThickness(1.5f);
        hitboxShapeGoalRight.setAnchor(gf::Anchor::Center);
        target.draw(hitboxShapeGoalRight);
    }    
}
