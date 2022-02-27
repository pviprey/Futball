#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/TextureAtlas.h>
#include <gf/ResourceManager.h>
#include <gf/ViewContainer.h>
#include <gf/Views.h>
#include <gf/Time.h>

#include "Game.h"
#include "bits/Terrain.h"
#include "bits/Ballon.h"
#include "bits/Equipe.h"
#include "bits/Joueur.h"

int main() {
    // Create the main window and the renderer
    gf::Window window("Futsall", { 1024, 768 });
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);    
    gf::RenderWindow renderer(window);
    window.setFullscreen();

    gf::ViewContainer views;

    gf::ExtendView view(gf::vec(GROUND_LENGTH, GROUND_HEIGH) * 32.0f, gf::vec(GROUND_LENGTH, GROUND_HEIGH) * 70.0f);
    views.addView(view);
    view.setInitialFramebufferSize({ 1024, 768 });

    /*(ref 2. update)*/
    gf::Clock clock;
    renderer.clear(gf::Color::Black); //nettoyer l'écran avant de commencer
    gf::Vector2f mousePosition;

    gf::ResourceManager resources;
    resources.addSearchDir("data");
    gf::TextureAtlas atlas("futsal_spritesheet.xml", resources);

    Terrain terrain(atlas, resources);
    terrain.setData();

    Ballon ballon(resources);

    Equipe equipe1 = Equipe();

    equipe1.addJoueur(Joueur(0, 1, resources));
    equipe1.addJoueur(Joueur(1, 1, resources));
    equipe1.addJoueur(Joueur(1, 1, resources));
    equipe1.addJoueur(Joueur(1, 1, resources));
    equipe1.addJoueur(Joueur(2, 1, resources));

    // Start the game loop 
    while (window.isOpen()){
        // Process events
        gf::Event event;

        // 1. recevoir les actions du joueur
        while (window.pollEvent(event)){   //reception action sur clavier

            equipe1.deplacement(event);

            switch (event.type){
                case gf::EventType::Closed: //fermeture de la fenetre
                    window.close();
                break;
                
                case gf::EventType::MouseMoved:
                    mousePosition = renderer.mapPixelToCoords(event.mouseCursor.coords);
                break;
                
                case gf::EventType::KeyPressed:     //touche appuyé
                    switch (event.key.keycode){
                        case gf::Keycode::Escape:
                            window.close();
                        break;

                        default:
                        break;
                    }
                break;

                default:
                break;
            }

            views.processEvent(event);
        }

    // 2. update 60 fois MINIMUM
    gf::Time ips = clock.restart();
    //std::printf("%g\n", 1/ips.asSeconds());
    equipe1.update(ips);


    // Draw the entities
    renderer.setView(view);
    renderer.clear();

    terrain.render(renderer);
    ballon.render(renderer);
    equipe1.render(renderer);

    renderer.display();
    }

    return 0;
}