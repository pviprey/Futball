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
    hitbox.center += velocite * time.asSeconds() * SPEED;

    if(pushed){
        velocite -= 0.1;
        if(velocite.x == 0 && velocite.y == 0){
            pushed = false;
        }
    }
}

void Ballon::interact(gf::Penetration penetration){
    pushed = true;

    hitbox.center -= penetration.depth * penetration.normal;
    velocite = penetration.normal * gf::Vector2f{1.5, 1.5};
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