#include "Ballon.h"
#include "Joueur.h"

#include <gf/Sprite.h>
#include <gf/RenderTarget.h>

Ballon::Ballon(gf::ResourceManager& resources):texture(resources.getTexture("Ball/ball_soccer4.png")){
    this->position = {0, 0};
    this->velocite = {0, 0};
    this->pushed = false;
}

void Ballon::update(gf::Time time){
    position += velocite * time.asSeconds() * SPEED;
}

void Ballon::render(gf::RenderTarget& target){
    gf::Sprite shape;
    shape.setTexture(texture);
    shape.setScale(1.2);
    shape.setPosition(position);
    shape.setAnchor(gf::Anchor::Center);

    target.draw(shape);
}