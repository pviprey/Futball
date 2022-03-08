#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/RenderTarget.h>

#include "Ballon.h"
#include "Joueur.h"

Ballon::Ballon(gf::ResourceManager& resources):texture(resources.getTexture("Ball/ball_soccer4.png")){
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
        float acceleration = gf::euclideanLength(velocite);

        hitbox.center += velocite * acceleration * time.asSeconds() * SPEED;

        if(acceleration < 0.01){ 
            pushed = false;
        }
    }
}

void Ballon::interact(gf::Penetration penetration, gf::Vector2f deplacement){
    pushed = true;

    hitbox.center += penetration.depth * deplacement;
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