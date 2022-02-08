#include "Joueur.h"
#include <gf/Window.h>
#include <gf/RenderWindow.h>
#include <gf/Shapes.h>
#include <gf/Color.h>

namespace{
    static constexpr float SPEED = 100.0f;
}

Joueur::Joueur(int poste, int style){
    this->poste = poste;
    this->style = style;
    this->velocite = {0,0};

    switch(poste){
        case 0:
            position = {70, 0};
            break;
        case 1:
            position = {150, 0};
            break;
        case 2:
            position = {250, 0};
    }

    switch (style){
    case 0:
        position.x -= position.x*0.1;
        break;

    case 1:
    default:
        break;

    case 2:
        position.x += position.x*0.1;
        break;
    }
}

void Joueur::deplacement(gf::Event event){
    switch (event.type){
        case gf::EventType::KeyPressed:     //touche appuyé
            switch (event.key.keycode){
                case gf::Keycode::Up:       //monter
                case gf::Keycode::Z:
                    velocite.y-= SPEED;
                break;

                case gf::Keycode::Down:     //descendre
                case gf::Keycode::S:
                    velocite.y+= SPEED;
                break;

                case gf::Keycode::Left:     //gauche
                case gf::Keycode::Q:
                    velocite.x-= SPEED;
                break;

                case gf::Keycode::Right:    //droite
                case gf::Keycode::D:
                    velocite.x+= SPEED;
                break;

                default:
                break;
            }
        break;


        case gf::EventType::KeyReleased:     //touche relaché
            switch (event.key.keycode){
                case gf::Keycode::Up:       //monter
                case gf::Keycode::Z:
                    velocite.y+= SPEED;
                break;

                case gf::Keycode::Down:     //descendre
                case gf::Keycode::S:
                    velocite.y-= SPEED;
                break;

                case gf::Keycode::Left:     //gauche
                case gf::Keycode::Q:
                    velocite.x+= SPEED;
                break;

                case gf::Keycode::Right:    //droite
                case gf::Keycode::D:
                    velocite.x-= SPEED;
                break;

                default:
                break;
            }
        break;

        default:
        break;
    }    
}
void Joueur::render(gf::RenderTarget& target){
    gf::CircleShape shape({30.0f});
    shape.setPosition(position);
    shape.setColor(gf::Color::Blue);
    shape.setAnchor(gf::Anchor::Center);
    target.draw(shape);
}

void Joueur::update(gf::Time time){
    position += velocite * time.asSeconds();
}