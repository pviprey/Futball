#include "Physics.h"

void Physics::collisionEquipeEquipe(){
    std::vector<Joueur>& joueurs = equipe1.getJoueurs();
    joueurs.insert(joueurs.end(), equipe2.getJoueurs().begin(), equipe2.getJoueurs().end());

    gf::Penetration penetration;

    for(size_t i = 0; i < joueurs.size(); i++){
        for(size_t j = i+1; j < joueurs.size(); j++){
            if(gf::collides(joueurs[i].getHitbox(), joueurs[j].getHitbox(), penetration)){
                printf("%f %f\n", penetration.normal.x, penetration.normal.y);
                joueurs[i].interact(penetration);
            }
        }
    }
}

//void collisionsEquipeTerrain(){}

void Physics::collisionEquipeBallon(){
    std::vector<Joueur>& joueurs = equipe1.getJoueurs();
    joueurs.insert(joueurs.end(), equipe2.getJoueurs().begin(), equipe2.getJoueurs().end());

    gf::Penetration penetration;

    for(size_t i = 0; i < joueurs.size(); i++){
        if(gf::collides(ballon.getHitbox(), joueurs[i].getHitbox(), penetration)){
            ballon.interact(penetration);
        }
    }    
}