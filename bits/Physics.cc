#include "Physics.h"
#include <iostream>

void Physics::collisionEquipeEquipe(){
    std::vector<Joueur>& joueurs = equipe1.getJoueurs();
    joueurs.insert(joueurs.end(), equipe2.getJoueurs().begin(), equipe2.getJoueurs().end());

    gf::Penetration penetration;

    for(size_t i = 0; i < joueurs.size(); i++){
        for(size_t j = i+1; j < joueurs.size(); j++){
            if(gf::collides(joueurs[i].getHitbox(), joueurs[j].getHitbox(), penetration)){
                joueurs[i].interact(penetration);
            }
        }
    }
}

void Physics::collisionsEquipeTerrain(){
    std::vector<Joueur>& joueurs = equipe1.getJoueurs();
    joueurs.insert(joueurs.end(), equipe2.getJoueurs().begin(), equipe2.getJoueurs().end());

    gf::Penetration penetration;

    for(size_t i = 0; i < joueurs.size(); i++){
        for(auto hitbox:terrain.getHitboxs()){
            if(gf::collides(joueurs[i].getHitbox(), hitbox, penetration)){
                joueurs[i].interact(penetration);
            }
        }   
    }
}

void Physics::collisionBallonEquipe(){
    std::vector<Joueur>& joueurs = equipe1.getJoueurs();
    joueurs.insert(joueurs.end(), equipe2.getJoueurs().begin(), equipe2.getJoueurs().end());

    gf::Penetration penetration;

    for(size_t i = 0; i < joueurs.size(); i++){
        if(gf::collides(ballon.getHitbox(), joueurs[i].getHitbox(), penetration)){
            ballon.interact(penetration, joueurs[i].getVelocite(), joueurs[i].getMarche());
        }
    }
}

void Physics::collisionsBallonTerrain(){
    gf::Penetration penetration;

    for(auto hitbox:terrain.getHitboxs()){
        if(gf::collides(ballon.getHitbox(), hitbox, penetration)){
            ballon.interact(penetration);
        }
    }
}