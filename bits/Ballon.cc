#include "Ballon.h"
#include "Joueur.h"

#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/RenderTarget.h>

Ballon::Ballon(gf::ResourceManager& resources):texture(resources.getTexture("Ball/ball_soccer4.png")){
    this->position = {0, 0};
    this->velocite = {0, 0};
    this->hitbox.center = position;
    this->hitbox.radius = 8.0f;
    this->pushed = false;
}

gf::CircF Ballon::getHitbox() const {
    return hitbox;
}

void Ballon::update(gf::Time time){
    position += velocite * time.asSeconds() * SPEED;
}

void Ballon::render(gf::RenderTarget& target){
    gf::Sprite shape;
    shape.setTexture(texture);
    shape.setScale(1);
    shape.setPosition(position);
    shape.setAnchor(gf::Anchor::Center);

    target.draw(shape);

    //debug
    gf::CircleShape hitboxShape;
    hitboxShape.setRadius(hitbox.getRadius());
    hitboxShape.setPosition(hitbox.getCenter());
    hitboxShape.setColor(gf::Color::Transparent);
    hitboxShape.setOutlineColor(gf::Color::Blue);
    hitboxShape.setOutlineThickness(1.0f);
    target.draw(hitboxShape);    
}