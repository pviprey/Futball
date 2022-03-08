#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/RenderTarget.h>

#include "Ballon.h"
#include "Joueur.h"

namespace{
    static constexpr float BALLON_SPEED = 320.0f;
    static constexpr float BALLON_ACCELERATION = -320.0f;
}

Ballon::Ballon(gf::ResourceManager& resources):texture(resources.getTexture("Ball/ball_soccer4.png")){
    this->norm = 0.0f;
    this->velocite = {0, 0};
    this->hitbox.center = {0, 0};
    this->hitbox.radius = 8.0f;
    this->pushed = false;
}

gf::CircF Ballon::getHitbox() const {
    return hitbox;
}

void Ballon::update(gf::Time time){
    if(pushed){
        norm += BALLON_ACCELERATION * time.asSeconds();      
        
        if(norm < 0.01){ 
            pushed = false;
            norm = 0;
            velocite = { 0, 0 };
        }

        hitbox.center += velocite * norm * time.asSeconds();
    }
}

void Ballon::interact(gf::Penetration penetration, gf::Vector2f deplacement){
    pushed = true;
    norm = BALLON_SPEED;
    velocite = deplacement;
}

void Ballon::render(gf::RenderTarget& target){
    gf::Sprite shape;
    shape.setTexture(texture);
    shape.setScale(1);
    shape.setPosition(hitbox.center);
    shape.setAnchor(gf::Anchor::Center);

    target.draw(shape);

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
