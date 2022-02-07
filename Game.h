#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <string>
#include <gf/TextureAtlas.h>

#include "bits/Terrain.h"


class Game {
    public:
        Game(const gf::TextureAtlas& atlas);
    private:
        Terrain terrain;

};

#endif  //GAME_H