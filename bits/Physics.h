#ifndef PHYSICS_H
#define PHYSICS_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <string>
#include <optional>

#include <gf/TextureAtlas.h>
#include <gf/Collision.h>

#include "Equipe.h"
#include "Ballon.h"
#include "Terrain.h"


class Physics {
    public:
        Physics(Ballon& b, Equipe& e1, Equipe& e2, Terrain& t):
            ballon(b),
            equipe1(e1),
            equipe2(e2),
            terrain(t){}

        void collisionEquipeEquipe();
        void collisionsEquipeTerrain();
        
        void collisionBallonEquipe();
        void collisionsBallonTerrain();

        void getClosest();
    private:
        Ballon& ballon;
        Equipe& equipe1;
        Equipe& equipe2;
        Terrain& terrain;

};

#endif  //PHYSICS_H