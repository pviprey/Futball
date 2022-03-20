#include "Physics.h"
#include <iostream>

void Physics::collisionEquipeEquipe(){
    std::vector<Joueur>& joueurs1 = equipe1.getJoueurs();
    std::vector<Joueur>& joueurs2 = equipe2.getJoueurs();
    gf::Penetration penetration;

    for(size_t i = 0; i < joueurs1.size(); i++){
        for(size_t j = i+1; j < joueurs1.size(); j++){
            if(gf::collides(joueurs1[i].getHitbox(), joueurs1[j].getHitbox(), penetration)){
                joueurs1[i].interact(penetration);
            }
        }

        for(size_t j = 0; j < joueurs2.size(); j++){
            if(gf::collides(joueurs1[i].getHitbox(), joueurs2[j].getHitbox(), penetration)){
                joueurs1[i].interact(penetration);
            }
        }        
    }


    for(size_t i = 0; i < joueurs2.size(); i++){
        for(size_t j = i+1; j < joueurs2.size(); j++){
            if(gf::collides(joueurs2[i].getHitbox(), joueurs2[j].getHitbox(), penetration)){
                joueurs2[i].interact(penetration);
            }
        }

        for(size_t j = 0; j < joueurs1.size(); j++){
            if(gf::collides(joueurs2[i].getHitbox(), joueurs1[j].getHitbox(), penetration)){
                joueurs2[i].interact(penetration);
            }
        }        
    }   
}

void Physics::collisionsEquipeTerrain(){
    std::vector<Joueur>& joueurs1 = equipe1.getJoueurs();
    std::vector<Joueur>& joueurs2 = equipe2.getJoueurs();
    gf::Penetration penetration;

    for(size_t i = 0; i < joueurs1.size(); i++){
        for(auto hitbox:terrain.getHitboxs()){
            if(gf::collides(joueurs1[i].getHitbox(), hitbox, penetration)){
                joueurs1[i].interact(penetration);
            }
        }   
    }

    for(size_t i = 0; i < joueurs2.size(); i++){
        for(auto hitbox:terrain.getHitboxs()){
            if(gf::collides(joueurs2[i].getHitbox(), hitbox, penetration)){
                joueurs2[i].interact(penetration);
            }
        }   
    }    
}

void Physics::collisionBallonEquipe(){
    std::vector<Joueur>& joueurs1 = equipe1.getJoueurs();
    std::vector<Joueur>& joueurs2 = equipe2.getJoueurs();
    gf::Penetration penetration;

    for(size_t i = 0; i < joueurs1.size(); i++){
        if(gf::collides(ballon.getHitbox(), joueurs1[i].getHitbox(), penetration)){
            ballon.interact(penetration, joueurs1[i].getVelocite(), joueurs1[i].getMarche());
        }
    }

    for(size_t i = 0; i < joueurs2.size(); i++){
        if(gf::collides(ballon.getHitbox(), joueurs2[i].getHitbox(), penetration)){
            ballon.interact(penetration, joueurs2[i].getVelocite(), joueurs2[i].getMarche());
        }
    }    
}

void Physics::collisionsBallonTerrain(){
    gf::Penetration penetration;

    for(auto hitbox : terrain.getHitboxs()){
        if(gf::collides(ballon.getHitbox(), hitbox, penetration)){
            ballon.interact(penetration);
        }
    }
}

bool Physics::ballInLeftGoal(){
    gf::Penetration penetration;

    return gf::collides(ballon.getHitbox(), terrain.getLeftGoal(), penetration);
}

bool Physics::ballInRightGoal(){
    gf::Penetration penetration;

    return gf::collides(ballon.getHitbox(), terrain.getRightGoal(), penetration);
}

void Physics::getClosest(){
    std::vector<Joueur>& joueurs = equipe1.getJoueurs();
    
    Joueur& closest = joueurs[0];
    Joueur& current = joueurs[0];

    for(size_t i = 1; i < joueurs.size(); i++){
        if(gf::euclideanDistance(ballon.getHitbox().center, closest.getHitbox().center) > gf::euclideanDistance(ballon.getHitbox().center, joueurs[i].getHitbox().center)){
            closest = joueurs[i];
        }

        if(joueurs[i].getCurrent()){
            current = joueurs[i];
        }
    }

    current.switchCurrentTo(closest);
}