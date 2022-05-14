#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/RenderTarget.h>

#include "Ballon.h"
#include "Joueur.h"

#include <iostream>

namespace{
    static constexpr float BALLON_SPEED = 300.0f;
    static constexpr float BALLON_ACCELERATION = -300.0f;
}

Ballon::Ballon(gf::ResourceManager& resources, bool debug):texture(resources.getTexture("Ball/ball_soccer4.png")), debug(debug){
    engagement();
}

void Ballon::engagement(){
    norm = 0.0f;
    velocite = {0, 0};
    pushed = false;
    marche = false;
    depth_marche = 0;

    hitbox.center = {0, 0};
    hitbox.radius = 8.0f;
}

gf::CircF Ballon::getHitbox() const {
    return hitbox;
}

bool Ballon::getPushed() const {
    return pushed;
}

void Ballon::update(gf::Time time){
    if(pushed){
        if(marche){
            hitbox.center += depth_marche * velocite;
        
            marche = false;
            depth_marche = 0;
        }else{
            norm += BALLON_ACCELERATION * time.asSeconds();
            
            if(norm < 0.01){ 
                pushed = false;
                norm = 0;
                velocite = { 0, 0 };
            }

            hitbox.center += velocite * norm * time.asSeconds();
        }
    }
}

void Ballon::interact(gf::Penetration penetration, gf::Vector2f deplacement, bool marche){
    pushed = true;
    norm = BALLON_SPEED;
    velocite = deplacement;

    this->marche = marche;
    depth_marche = penetration.depth;
}

void Ballon::interact(gf::Penetration penetration){
    hitbox.center -= penetration.depth * penetration.normal;
}

void Ballon::render(gf::RenderTarget& target){
    gf::Sprite shape;
    shape.setTexture(texture);
    shape.setScale(1);
    shape.setPosition(hitbox.center);
    shape.setAnchor(gf::Anchor::Center);

    target.draw(shape);

    //debug
    if(debug){
        gf::CircleShape hitboxShape;
        hitboxShape.setRadius(hitbox.getRadius());
        hitboxShape.setPosition(hitbox.getCenter());
        hitboxShape.setColor(gf::Color::Transparent);
        hitboxShape.setOutlineColor(gf::Color::Green);
        hitboxShape.setOutlineThickness(3.0f);
        hitboxShape.setAnchor(gf::Anchor::Center);
        target.draw(hitboxShape);
    }
}
