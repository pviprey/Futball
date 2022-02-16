#include "Joueur.h"
#include <gf/Window.h>
#include <gf/RenderWindow.h>
#include <gf/Shapes.h>
#include <gf/Color.h>
#include <gf/Sprite.h>

namespace{
    static constexpr float SPEED = 120.0f;
}

Joueur::Joueur(int poste, int style, gf::ResourceManager& resources):texture(resources.getTexture("Players/characterBlue (1).png")){
    switch(poste){
        case 0:
            this->poste = Poste::Gardien;
            position.x = 70;
            break;
        case 1:
            this->poste = Poste::Defenseur;
            position.x = 400;
            break;
        case 2:
            this->poste = Poste::Attaquant;
            position.x = 800;
            break;
    }

    switch(style){
        case 0:
            this->style = Style::Recule;
            position.x -= position.x*0.1;
            break;
        case 1:
            this->style = Style::Normal;
            break;
        case 2:
            this->style = Style::Avance;
            position.x += position.x*0.1;
            break;
    }

    this->velocite = {0,0};
    this->current = false;
}


void Joueur::setPosition(gf::Vector2f position){
    this->position = position;
    printf("(%f, %f)\n", position.x, position.y);
}

void Joueur::setPosition(float posX, float posY){
    setPosition({posX, posY});
}

void Joueur::setPositionY(float posY){
    setPosition({this->position.x, posY});
}


bool Joueur::getCurrent(){
    return this->current;
}

void Joueur::setCurrent(){
    this->current = true;
}

void Joueur::removeCurrent(){
    this->current = false;
}

void Joueur::switchCurrent(Joueur& joueur){
    this->removeCurrent();
    joueur.setCurrent();
}


Joueur::Poste Joueur::getPoste() const {
    return poste;
}


void Joueur::deplacement(gf::Event event){
    if(current){
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
}
void Joueur::render(gf::RenderTarget& target){
    gf::Sprite shape;
    shape.setTexture(texture);
    shape.setScale(1.2);
    shape.setPosition(position);
    shape.setAnchor(gf::Anchor::Center);
    target.draw(shape);

    if(this->current){
        gf::CircleShape circleShape;
        circleShape.setRadius(20.0f);
        circleShape.setColor(gf::Color::Transparent);
        circleShape.setOutlineColor(gf::Color::Red);
        circleShape.setOutlineThickness(3.0f);
        circleShape.setPosition(position);
        circleShape.setAnchor(gf::Anchor::Center);
        target.draw(circleShape);
    }
}   

void Joueur::update(gf::Time time){
    position += velocite * time.asSeconds();
}