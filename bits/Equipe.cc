#include "Equipe.h"

#include <cstdlib>
#include <iostream>

namespace{
    constexpr int TAILLE_EQUIPE = 5;
}

Equipe::Equipe(bool sens):
    sens(sens){}

Equipe::Equipe(std::vector<Joueur> equipe, bool sens):
    composition(equipe),
    sens(sens){
        disposition();
}

bool Equipe::addJoueur(int poste, int style, gf::ResourceManager& resources){
    return addJoueur(Joueur(poste, style, resources, sens));
}

bool Equipe::addJoueur(const Joueur& joueur){
    if(composition.size() == TAILLE_EQUIPE){
        return false;
    }

    if(joueur.getPoste() == Joueur::Poste::Gardien){
        if(hasGoal()){
            return false;
        }
    }

    composition.push_back(joueur);
    if(composition.size() == TAILLE_EQUIPE){
        disposition();
    }

    return true;
}

std::vector<Joueur>& Equipe::getJoueurs(){
    return composition;
}

void Equipe::switchCurrentToClosest(Ballon& ballon){
    int closest = 0;
    int current = 0;

    for(size_t i = 1; i < composition.size(); i++){
        if(gf::euclideanDistance(ballon.getHitbox().center, composition[closest].getHitbox().center) > gf::euclideanDistance(ballon.getHitbox().center, composition[i].getHitbox().center)){
            closest = i;
        }

        if(composition[i].getCurrent()){
            current = i;
        }
    }

    composition[current].switchCurrentTo(composition[closest]);
}

void Equipe::deplacement(gf::Event event){
    for (auto & joueur : composition){
        if(joueur.getCurrent()){
            switch (event.type){
                case gf::EventType::KeyReleased:     //touche relaché
                    switch (event.key.keycode){

                        default:
                        break;
                    }

                default:
                break;
            }
        }
        joueur.deplacement(event);
    }
}

void Equipe::update(gf::Time time){
    for(auto & joueur : composition){
        joueur.update(time);
    }
}

void Equipe::render(gf::RenderTarget& target){
    for(auto & joueur : composition){
        joueur.render(target);
    }
}

void Equipe::isDefending(Ballon& ballon, Terrain& terrain){
    for(auto & joueur : composition){
        switch(joueur.getPoste()){
            case Joueur::Poste::Gardien:
                if(sens){
                    if(ballon.getPushed()){
                        //joueur.deplacement(gf::Vector2f{terrain.getLeftGoal().getCenter().x + terrain.getLeftGoal().getSize().x/2 + 15, ballon.getHitbox().center.y - terrain.getLeftGoal().getCenter().y});
                    }
                }else{
                    if(ballon.getPushed()){
                        std::cout << "DEBUG:" << terrain.getRightGoal().getCenter().x - terrain.getRightGoal().getSize().x/2 - 15 << std::endl;
                        joueur.deplacement(gf::Vector2f{
                            terrain.getRightGoal().getCenter().x - terrain.getRightGoal().getSize().x/2 - 15,
                            tan(gf::angle(terrain.getRightGoal().getCenter() - ballon.getHitbox().center)) * (terrain.getRightGoal().getCenter().x - terrain.getRightGoal().getSize().x - 15)
                        });
                    }                    
                }
            break;

            case Joueur::Poste::Defenseur:
                
            break;

            case Joueur::Poste::Attaquant:
                
            break;
        }
    }
}

bool Equipe::hasGoal(){
    for(auto & joueur : composition){
        if(joueur.getPoste() == Joueur::Poste::Gardien){
            return true;
        }
    }

    return false;
}


void Equipe::disposition(){
    int nbDefenseur = 0;
    int nbAttaquant = 0;

    for(auto & joueur : composition){
        switch(joueur.getPoste()){
            case Joueur::Poste::Gardien:
                joueur.setPositionY(0);
            break;

            case Joueur::Poste::Defenseur:
                nbDefenseur++;
            break;

            case Joueur::Poste::Attaquant:
                nbAttaquant++;
            break;
        }
    }



    int countAtk = 1;
    int countDef = 1;
    for(auto& joueur : composition){
        switch(joueur.getPoste()){
            case Joueur::Poste::Gardien:
            break;

            case Joueur::Poste::Defenseur:
                joueur.setPositionY(((64*(GROUND_HEIGH)/(nbDefenseur+1))*countDef)-GROUND_HEIGH*64/2);
                countDef++;
            break;

            case Joueur::Poste::Attaquant:
                joueur.setPositionY(((64*(GROUND_HEIGH)/(nbAttaquant+1))*countAtk)-GROUND_HEIGH*64/2);
                countAtk++;
            break;
        }        
    }
}