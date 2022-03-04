#include "Joueur.h"
#include <gf/Window.h>
#include <gf/RenderWindow.h>
#include <gf/Shapes.h>
#include <gf/Color.h>
#include <gf/Sprite.h>
#include <gf/VectorOps.h>
#include <gf/Log.h>

namespace{
    //static constexpr float SPEED = 120.0f;
}

Joueur::Joueur(int poste, int style, gf::ResourceManager& resources):texture(&resources.getTexture("Players/characterBlue (1).png")){
    switch(poste){
        case 0:
            this->poste = Poste::Gardien;
            hitbox.center.x = 13 * -64;
            break;
        case 1:
            this->poste = Poste::Defenseur;
            hitbox.center.x = 9 * -64;
            break;
        case 2:
            this->poste = Poste::Attaquant;
            hitbox.center.x = 3 * -64;
            break;
    }

    switch(style){
        case 0:
            this->style = Style::Recule;
            hitbox.center.x -= hitbox.center.x*0.1;
            break;
        case 1:
            this->style = Style::Normal;
            break;
        case 2:
            this->style = Style::Avance;
            hitbox.center.x += hitbox.center.x*0.1;
            break;
    }

    this->velocite = {0,0};

    this->hitbox.radius = 11.0f;

    this->current = false;
    this->interacting = false;
}


void Joueur::setPosition(gf::Vector2f position){
    this->hitbox.center = position;
}

void Joueur::setPosition(float posX, float posY){
    setPosition({posX, posY});
}

void Joueur::setPositionY(float posY){
    setPosition({this->hitbox.center.x, posY});
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
    this->velocite = {0.0f, 0.0f};
    this->removeCurrent();
    joueur.setCurrent();
}


Joueur::Poste Joueur::getPoste() const {
    return poste;
}

gf::CircF Joueur::getHitbox() const {
    return hitbox;
}

void Joueur::deplacement(gf::Event event){
    if(current){
        switch (event.type){
            case gf::EventType::KeyPressed:     //touche appuyé
                switch (event.key.keycode){
                    case gf::Keycode::Up:       //monter
                    case gf::Keycode::Z:
                        velocite.y = -1;
                    break;

                    case gf::Keycode::Down:     //descendre
                    case gf::Keycode::S:
                        velocite.y = 1;
                    break;

                    case gf::Keycode::Left:     //gauche
                    case gf::Keycode::Q:
                        velocite.x = -1;
                    break;

                    case gf::Keycode::Right:    //droite
                    case gf::Keycode::D:
                        velocite.x = 1;
                    break;

                    default:
                    break;
                }
            break;


            case gf::EventType::KeyReleased:     //touche relaché
                switch (event.key.keycode){
                    case gf::Keycode::Up:       //monter
                    case gf::Keycode::Z:
                        velocite.y = 0;
                    break;

                    case gf::Keycode::Down:     //descendre
                    case gf::Keycode::S:
                        velocite.y = 0;
                    break;

                    case gf::Keycode::Left:     //gauche
                    case gf::Keycode::Q:
                        velocite.x = 0;
                    break;

                    case gf::Keycode::Right:    //droite
                    case gf::Keycode::D:
                        velocite.x = 0;
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

void Joueur::update(gf::Time time){
    if(velocite.x != 0 || velocite.y != 0){
        velocite = gf::normalize(velocite);
    }

    hitbox.center += velocite * time.asSeconds() * SPEED;
}

void Joueur::interact(gf::Penetration penetration){
    hitbox.center -= penetration.depth * penetration.normal;
    //velocite -= gf::dot(velocite, penetration.normal);
    velocite *= gf::Vector2f{.2, .2};
    printf("velocite : %f, %f\n", velocite.x, velocite.y);
    printf("penetration normal: %f, %f\n", penetration.normal.x, penetration.normal.y);
    printf("penetration depth: %f\n", penetration.depth);

    interacting = true;
}

void Joueur::render(gf::RenderTarget& target){
    gf::Sprite shape;
    shape.setTexture(*texture);
    shape.setScale(1.3);
    shape.setPosition(hitbox.center);
    shape.setAnchor(gf::Anchor::Center);
    shape.setRotation(gf::angle(velocite));

    target.draw(shape);

    if(this->current){
        gf::CircleShape circleShape;
        circleShape.setRadius(20.0f);
        circleShape.setColor(gf::Color::Transparent);
        circleShape.setOutlineColor(gf::Color::Red);
        circleShape.setOutlineThickness(3.0f);
        circleShape.setPosition(hitbox.center);
        circleShape.setAnchor(gf::Anchor::Center);
        target.draw(circleShape);
    }

    //debug
    gf::CircleShape hitboxShape;
    hitboxShape.setRadius(hitbox.getRadius());
    hitboxShape.setPosition(hitbox.getCenter());
    hitboxShape.setColor(gf::Color::Transparent);
    hitboxShape.setOutlineColor(gf::Color::Blue);
    hitboxShape.setOutlineThickness(1.0f);
    hitboxShape.setAnchor(gf::Anchor::Center);
    target.draw(hitboxShape);    
}