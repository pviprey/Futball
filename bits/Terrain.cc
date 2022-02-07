#include <gf/Sprite.h>

#include <gf/Color.h>

#include "Terrain.h"

#define GUILLEMET '\''

namespace{
    const char TERRAIN[] =
        "O-----------------------------------------------Y-----------------------------------------------P"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "G                                               '                                               D"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "|                                               X                                               !"
        "#                                               '                                               #"
        "#           .                                (  .  )                                .           #"
        "#                                               '                                               #"
        "|                                               x                                               !"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "g                                               '                                               d"
        "|                                               '                                               !"
        "|                                               '                                               !"
        "L_______________________________________________y_______________________________________________M"
    ;

    constexpr gf::Vector2i TERRAINSIZE = gf::vec(97, 23);
    constexpr gf::Vector2f SpriteSize(64.0f, 64.0f);  
  
}

Terrain::Terrain(const gf::TextureAtlas& atlas):gf::Entity(1),
  texture(atlas.getTexture()),

  LineVertical(atlas.getTextureRect("Centerred_Vertical_Line.png")),
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

  Ground(atlas.getTextureRect("Ground.png")),
  tiles(TERRAINSIZE)
  {}

void Terrain::setData() {

    Data tb = Data(TERRAIN, TERRAINSIZE);

    for (auto coords : tiles.getPositionRange()) {
        switch (tb(coords)) {
            case 'X':
            case 'x':
            case GUILLEMET:
                tiles(coords) = Texture::LineVertical;
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
            case 'y':
                tiles(coords) = Texture::TShapeBottom;
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

            case ' ':
            default:
                tiles(coords) = Texture::Ground;
                break;
        }
    }
}

void Terrain::render(gf::RenderTarget& target) {
    for (auto coords : tiles.getPositionRange()) {
        gf::Sprite sprite(texture);

        switch (tiles(coords)) {

            case Texture::LineVertical:
                sprite.setTextureRect(LineVertical);
                break;            
            case Texture::LineHorizontal:
                sprite.setTextureRect(LineHorizontal);
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
            case Texture::Ground:
                sprite.setTextureRect(Ground);
                break;  

            default:
                continue;
        }

        sprite.setPosition(coords * SpriteSize);
        sprite.setAnchor(gf::Anchor::TopLeft);
        target.draw(sprite);
    }    
}