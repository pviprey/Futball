#include "Ballon.h"
#include "Joueur.h"

#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/RenderTarget.h>

Ballon::Ballon(gf::ResourceManager& resources):texture(resources.getTexture("Ball/ball_soccer4.png")){
    this->position = {0, 0};
    this->velocite = {0, 0};
    this->hitboxe.center = position;
    this->hitboxe.radius = 8.0f;
    this->pushed = false;
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
    gf::CircleShape hitboxeShape;
    hitboxeShape.setRadius(hitboxe.getRadius());
    hitboxeShape.setPosition(hitboxe.getCenter());
    hitboxeShape.setColor(gf::Color::Transparent);
    hitboxeShape.setOutlineColor(gf::Color::Blue);
    hitboxeShape.setOutlineThickness(1.0f);
    target.draw(hitboxeShape);    
}