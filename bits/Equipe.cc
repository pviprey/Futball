#include <cstdlib>

#include "Equipe.h"
#include "Terrain.h"

namespace{
    constexpr int TAILLE_EQUIPE = 5;
}

Equipe::Equipe(){
}

Equipe::Equipe(std::vector<Joueur> equipe):composition(equipe){
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

bool Equipe::addJoueur(int poste, int style, gf::ResourceManager& resources){
    return addJoueur(Joueur(poste, style, resources));
}

void Equipe::deplacement(gf::Event event){
    for (auto & joueur : composition){
        if(joueur.getCurrent()){
            switch (event.type){
                case gf::EventType::KeyReleased:     //touche relaché
                    switch (event.key.keycode){
                        case gf::Keycode::Space:
                        case gf::Keycode::RightCtrl:
                            joueur.switchCurrent(composition.at(rand() % TAILLE_EQUIPE));
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

void Equipe::render(gf::RenderTarget& target){
    for(auto & joueur : composition){
        joueur.render(target);
    }
}

void Equipe::update(gf::Time time){
    for(auto & joueur : composition){
        joueur.update(time);
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
    printf("---- pass disposition ----\n");
    int nbDefenseur = 0;
    int nbAttaquant = 0;

    for(auto & joueur : composition){
        switch(joueur.getPoste()){
            case Joueur::Poste::Gardien:
                joueur.setPositionY(64*(GROUND_HEIGH)/2);
                printf("gardien ajouté.\n");
                break;
            case Joueur::Poste::Defenseur:
                nbDefenseur++;
                printf("defenseur ajouté. (%i)\n", nbDefenseur);
                break;
            case Joueur::Poste::Attaquant:
                nbAttaquant++;
                printf("attaquant ajouté. (%i)\n", nbAttaquant);
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
                joueur.setPositionY((64*(GROUND_HEIGH)/(nbDefenseur+1))*countDef);
                countDef++;
                break;
            case Joueur::Poste::Attaquant:
                joueur.setPositionY((64*(GROUND_HEIGH)/(nbAttaquant+1))*countAtk);
                countAtk++;
                break;
        }        
    }
}