#include "Equipe.h"
#include "Terrain.h"

#include <cstdlib>

namespace{
    constexpr int TAILLE_EQUIPE = 5;
}

Equipe::Equipe(){
}

Equipe::Equipe(std::vector<Joueur> equipe):
    composition(equipe){
        disposition();
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

bool Equipe::addJoueur(int poste, int style, gf::ResourceManager& resources, bool sens){
    return addJoueur(Joueur(poste, style, resources, sens));
}

std::vector<Joueur>& Equipe::getJoueurs() {
    return composition;
}

void Equipe::deplacement(gf::Event event){
    for (auto & joueur : composition){
        if(joueur.getCurrent()){
            switch (event.type){
                case gf::EventType::KeyReleased:     //touche relaché
                    switch (event.key.keycode){
                        case gf::Keycode::Space:
                        case gf::Keycode::RightCtrl:
                            joueur.switchCurrent(composition.at(rand() % TAILLE_EQUIPE)); //TODO with ballon
                        break;

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
                joueur.setCurrent();
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