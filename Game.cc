#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/TextureAtlas.h>
#include <gf/ResourceManager.h>

#include "Game.h"
#include "bits/Terrain.h"
#include "bits/Ballon.h"
#include "bits/Equipe.h"
#include "bits/Joueur.h"

int main() {
    // Create the main window and the renderer
    gf::Window window("Futsal", { 1024, 768 });
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);    
    gf::RenderWindow renderer(window);
    


    /*(ref 2. update)*/
    gf::Clock clock;
    renderer.clear(gf::Color::Black); //nettoyer l'écran avant de commencer
    gf::Vector2f mousePosition;

    gf::ResourceManager resources;
    resources.addSearchDir("/home/pierre/Documents/L3/projet/Football/data/groundTarmac.png");
    gf::TextureAtlas atlas("data/futsal_spritesheet.xml", resources);

    Terrain terrain = Terrain(atlas);


    // Start the game loop 
    while (window.isOpen()){
        // Process events
        gf::Event event;

        // 1. recevoir les actions du joueur
        while (window.pollEvent(event)){   //reception action sur clavier
            switch (event.type){
                case gf::EventType::Closed: //fermeture de la fenetre
                    window.close();
                break;
                
                #if 0
                case gf::EventType::MouseMoved:
                    mousePosition = renderer.mapPixelToCoords(event.mouseCursor.coords);
                break;
                
                case gf::EventType::KeyPressed:     //touche appuyé
                    switch (event.key.keycode){
                        case gf::Keycode::Up:       //monter
                        case gf::Keycode::Z:
                            // velocity.y-= Speed;
                        break;

                        case gf::Keycode::Down:     //descendre
                        case gf::Keycode::S:
                            // velocity.y+= Speed;
                        break;

                        case gf::Keycode::Left:     //gauche
                        case gf::Keycode::Q:
                            // velocity.x-= Speed;
                        break;

                        case gf::Keycode::Right:    //droite
                        case gf::Keycode::D:
                            // velocity.x+= Speed;
                        break;

                        default:
                        break;
                    }
                break;


                case gf::EventType::KeyReleased:     //touche relaché
                    switch (event.key.keycode){
                        case gf::Keycode::Up:       //monter
                        case gf::Keycode::Z:
                            // velocity.y+= Speed;
                        break;

                        case gf::Keycode::Down:     //descendre
                        case gf::Keycode::S:
                            // velocity.y-= Speed;
                        break;

                        case gf::Keycode::Left:     //gauche
                        case gf::Keycode::Q:
                            // velocity.x+= Speed;
                        break;

                        case gf::Keycode::Right:    //droite
                        case gf::Keycode::D:
                            // velocity.x-= Speed;
                        break;

                        default:
                        break;
                    }
                break;
                #endif

                default:
                break;
            }                          
        }

    // 2. update 60 fois MINIMUM
    float ips = clock.restart().asSeconds();
    std::printf("%g\n", 1/ips);
    //entity.setVelocity(velocity);
    //entity.update(ips);


    // Draw the entities
    renderer.clear();
    renderer.display();
    terrain.render(renderer);
    }

    return 0;
}