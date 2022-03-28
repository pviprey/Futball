#include "Joueur.h"
#include <gf/Window.h>
#include <gf/RenderWindow.h>
#include <gf/Shapes.h>
#include <gf/Color.h>
#include <gf/Sprite.h>
#include <gf/VectorOps.h>
#include <gf/Log.h>

#include <iostream>

Joueur::Joueur(int poste, int style, gf::ResourceManager& resources, bool sens):sens(sens){
    if(sens){
        texture = &resources.getTexture("Players/characterBlue (1).png");
    }else{
        texture = &resources.getTexture("Players/characterRed (1).png");
    }
    switch(poste){
        case 0:
            this->poste = Poste::Gardien;
        break;

        case 1:
            this->poste = Poste::Defenseur;
        break;

        case 2:
            this->poste = Poste::Attaquant;
        break;
    }

    switch(style){
        case 0:
            this->style = Style::Recule;
        break;

        case 1:
            this->style = Style::Normal;
        break;

        case 2:
            this->style = Style::Avance;
        break;
    }

    hitbox.radius = 11.0f;

    engagement();
}

void Joueur::engagement(){
    marche = false;
    velocite = {0,0};
    current = false;
    interacting = false;

    if(sens){
        angle = 0;
    }else{
        angle = gf::Pi;
    }
}

void Joueur::setPosition(gf::Vector2f position){
    this->hitbox.center = position;
}

void Joueur::setPosition(float posX, float posY){
    setPosition({posX, posY});
}

bool Joueur::getMarche(){
    return marche;
}

gf::Vector2f Joueur::getVelocite(){
    return velocite;
}

bool Joueur::getCurrent(){
    return current;
}

Joueur::Poste Joueur::getPoste() const {
    return poste;
}

Joueur::Style Joueur::getStyle() const {
    return style;
}

gf::CircF Joueur::getHitbox() const {
    return hitbox;
}

void Joueur::switchCurrentTo(Joueur& joueur){
    velocite = {0.0f, 0.0f};

    removeCurrent();
    joueur.setCurrent();
}

void Joueur::deplacement(gf::Vector2f arrivee){

    float angle = gf::radiansToDegrees(gf::angle(hitbox.center - arrivee));
    std::cout << "angle: " << angle << std::endl;

    /*
    if(abs(hitbox.center.x - arrivee.x) > 0.1 || abs(hitbox.center.y - arrivee.y) > 0.1){
        if(approxAngle(angle, 0, 45/2)){    //transformer les angles en radiant CONNARD
            velocite.x = 1;
        }
        else if(approxAngle(angle, 45, 45/2)){
            velocite.x = 1;
            velocite.y = 1;
        }
        else if(approxAngle(angle, 90, 45/2)){
            velocite.y = 1;
        }
        else if(approxAngle(angle, 135, 45/2)){
            velocite.x = -1;
            velocite.y = 1;
        }
        else if(approxAngle(angle, 180, 45/2)){
            velocite.x = -1;
        }
        else if(approxAngle(angle, 225, 45/2)){
            velocite.x = -1;
            velocite.y = -1;
        }
        else if(approxAngle(angle, 270, 45/2)){
            velocite.y = -1;
        }
        else if(approxAngle(angle, 315, 45/2)){
            velocite.x = 1;
            velocite.y = -1;
        }
    }
    */
}

bool Joueur::approxAngle(float value, float test, float amplitude){
    return value >= test-amplitude && value <= test+amplitude;
}

void Joueur::deplacement(gf::Event event){
    if(current){
        switch (event.type){
            case gf::EventType::KeyPressed:     //touche appuyé
                switch (event.key.keycode){
                    case gf::Keycode::Up:       //monter
                        if(!sens){
                            velocite.y = -1;
                        }
                    break;
                    case gf::Keycode::Z:
                        if(sens){
                            velocite.y = -1;
                        }
                    break;


                    case gf::Keycode::Down:     //descendre
                        if(!sens){
                            velocite.y = 1;
                        }
                    break;
                    case gf::Keycode::S:
                        if(sens){
                            velocite.y = 1;
                        }
                    break;


                    case gf::Keycode::Left:     //gauche
                        if(!sens){
                            velocite.x = -1;
                        }
                    break;
                    case gf::Keycode::Q:
                        if(sens){
                            velocite.x = -1;
                        }
                    break;


                    case gf::Keycode::Right:    //droite
                        if(!sens){
                            velocite.x = 1;
                        }
                    break;                        
                    case gf::Keycode::D:
                        if(sens){
                            velocite.x = 1;
                        }
                    break;

                    case gf::Keycode::RightAlt:     //marcher
                        if(!sens){
                            marche = true;
                        }
                    break;
                    case gf::Keycode::LeftShift:
                        if(sens){
                            marche = true;
                        }
                    break;

                    default:
                    break;
                }
            break;


            case gf::EventType::KeyReleased:     //touche relaché
                switch (event.key.keycode){
                    case gf::Keycode::Up:       //monter
                        if(!sens){
                            velocite.y = 0;
                        }
                    break;
                    case gf::Keycode::Z:
                        if(sens){
                            velocite.y = 0;
                        }
                    break;


                    case gf::Keycode::Down:     //descendre
                        if(!sens){
                            velocite.y = 0;
                        }                    
                    break;
                    case gf::Keycode::S:
                        if(sens){
                            velocite.y = 0;
                        }
                    break;


                    case gf::Keycode::Left:     //gauche
                        if(!sens){
                            velocite.x = 0;
                        }                    
                    break;
                    case gf::Keycode::Q:
                        if(sens){
                            velocite.x = 0;
                        }
                    break;


                    case gf::Keycode::Right:    //droite
                        if(!sens){
                            velocite.x = 0;
                        }                    
                    break;
                    case gf::Keycode::D:
                        if(sens){
                            velocite.x = 0;
                        }
                    break;

                    case gf::Keycode::RightAlt:     //marcher
                        if(!sens){
                            marche = false;
                        }
                    break;
                    case gf::Keycode::LeftShift:
                        if(sens){
                            marche = false;
                        }
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
    
    if(marche){
        hitbox.center += velocite * time.asSeconds() * SPEED/1.4;
    }else{
        hitbox.center += velocite * time.asSeconds() * SPEED;
    }
}

void Joueur::interact(gf::Penetration penetration){
    hitbox.center -= penetration.depth * penetration.normal;
    velocite *= gf::Vector2f{.2, .2};

    interacting = true;
}

void Joueur::render(gf::RenderTarget& target){
    gf::Sprite shape;
    shape.setTexture(*texture);
    shape.setScale(1.3);
    shape.setPosition(hitbox.center);
    shape.setAnchor(gf::Anchor::Center);
    
    if(velocite.x != 0 || velocite.y != 0){
        angle = gf::angle(velocite);
    }
    shape.setRotation(angle);

    target.draw(shape);

    if(current){
        gf::CircleShape circleShape;
        circleShape.setRadius(20.0f);
        circleShape.setColor(gf::Color::Transparent);
        if(sens){
            circleShape.setOutlineColor(gf::Color::Red);
        }else{
            circleShape.setOutlineColor(gf::Color::Blue);
        }
        circleShape.setOutlineThickness(3.0f);
        circleShape.setPosition(hitbox.center);
        circleShape.setAnchor(gf::Anchor::Center);
        target.draw(circleShape);
    }

    //debug
    /*
    gf::CircleShape hitboxShape;
    hitboxShape.setRadius(hitbox.getRadius());
    hitboxShape.setPosition(hitbox.getCenter());
    hitboxShape.setColor(gf::Color::Transparent);
    hitboxShape.setOutlineColor(gf::Color::Blue);
    hitboxShape.setOutlineThickness(1.0f);
    hitboxShape.setAnchor(gf::Anchor::Center);
    target.draw(hitboxShape);
    */
}

void Joueur::setCurrent(){
    current = true;
}

void Joueur::removeCurrent(){
    current = false;
}