#include "Terrain.h"

namespace{
  const char terrain[] = {
    "O-------------------------------------------------Y-------------------------------------------------P"
    "|                                                 '                                                 |"
    "|                                                 '                                                 |"
    "G                                                 '                                                 D"
    "|                                                 '                                                 |"
    "|                                                 '                                                 |"
    "|                                                 '                                                 |"
    "|                                                 '                                                 |"
    "|                                                 X                                                 |"
    "|                                                 '                                                 |"
    "#                                                 '                                                 #"
    "#            ¤                               (    ¤    )                               ¤            #"
    "#                                                 '                                                 #"
    "|                                                 '                                                 |"
    "|                                                 x                                                 |"
    "|                                                 '                                                 |"
    "|                                                 '                                                 |"
    "|                                                 '                                                 |"
    "|                                                 '                                                 |"
    "g                                                 '                                                 d"
    "|                                                 '                                                 |"
    "|                                                 '                                                 |"
    "L-------------------------------------------------y-------------------------------------------------M"
  };

  constexpr gf::Vector2i TerrainSize = gf::vec(101, 23);
}

Terrain::Terrain():gf::Entity(1){
    
}

Terrain::Terrain(const gf::TextureAtlas& atlas):gf::Entity(1),
    texture(atlas.getTexture())//,
    // ballon(Ballon()),
    // equipe1(Equipe({Joueur(0, 0), Joueur(1, 1), Joueur(1, 2), Joueur(1, 1), Joueur(2,1)})),
    // equipe2(Equipe({Joueur(0, 0), Joueur(1, 1), Joueur(1, 2), Joueur(1, 1), Joueur(2,1)}))
    {

    }