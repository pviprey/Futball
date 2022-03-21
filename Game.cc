#include <iostream>
#include <random>

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
#include "bits/Ballon.h"
#include "bits/Equipe.h"
#include "bits/Physics.h"


int main() {
    // Create the main window and the renderer
    gf::Window window("Futsall", { 1024, 768 });
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);    
    gf::RenderWindow renderer(window);
    window.setFullscreen();

    gf::ViewContainer views;

    gf::ExtendView view(gf::vec(0, 0), gf::vec(GROUND_LENGTH, GROUND_HEIGH) * 70.0f);
    views.addView(view);
    view.setInitialFramebufferSize({ 1024, 768 });

    gf::Text score;
    int scoreLeft = 0;
    int scoreRight = 0;

    /*(ref 2. update)*/
    gf::Clock clock;
    renderer.clear(gf::Color::Black); //nettoyer l'écran avant de commencer

    gf::ResourceManager resources;
    resources.addSearchDir("data");
    gf::TextureAtlas atlas("futsal_spritesheet.xml", resources);

    Terrain terrain(atlas, resources);
    terrain.setData();

    Ballon ballon(resources);

    Equipe equipeLeft = Equipe(true);
    equipeLeft.addJoueur(0, 1, resources);
    equipeLeft.addJoueur(1, 1, resources);
    equipeLeft.addJoueur(1, 1, resources);
    equipeLeft.addJoueur(1, 1, resources);
    equipeLeft.addJoueur(2, 1, resources);
    equipeLeft.switchCurrentToClosest(ballon);

    Equipe equipeRight = Equipe(false);
    equipeRight.addJoueur(0, 1, resources);
    equipeRight.addJoueur(1, 1, resources);
    equipeRight.addJoueur(1, 1, resources);
    equipeRight.addJoueur(1, 1, resources);
    equipeRight.addJoueur(2, 1, resources);
    equipeRight.switchCurrentToClosest(ballon);

    Physics physic(ballon, equipeLeft, equipeRight, terrain);

    // Start the game loop 
    while (window.isOpen()){
        // Process events
        gf::Event event;

        // 1. recevoir les actions du joueur
        while (window.pollEvent(event)){   //reception action sur clavier
            equipeLeft.deplacement(event);
            equipeRight.deplacement(event);

            switch (event.type){
                case gf::EventType::Closed: //fermeture de la fenetre
                    window.close();
                break;

                case gf::EventType::KeyPressed:     //touche appuyé
                    switch (event.key.keycode){
                        case gf::Keycode::Escape:
                            window.close();
                        break;

                        case gf::Keycode::Tab:
                            equipeLeft.switchCurrentToClosest(ballon);
                        break;

                        case gf::Keycode::Space:
                            equipeRight.switchCurrentToClosest(ballon);
                        break;

                        default:
                        break;
                    }
                break;

                default:
                break;
            }

            equipeRight.isDefending(ballon, terrain);

            views.processEvent(event);
        }

        // 2. update 60 fois MINIMUM

        if(physic.ballInLeftGoal()){
            scoreRight++;
            equipeLeft.engagement(true);
            equipeRight.engagement(false);
            ballon.engagement();

            equipeLeft.switchCurrentToClosest(ballon);
            equipeRight.switchCurrentToClosest(ballon);

            std::cout << "Équipe Gauche: " << scoreLeft << "\tÉquipe droite: " << scoreRight << std::endl;
        }

        if(physic.ballInRightGoal()){
            scoreLeft++;
            equipeLeft.engagement(false);
            equipeRight.engagement(true);
            ballon.engagement();

            equipeLeft.switchCurrentToClosest(ballon);
            equipeRight.switchCurrentToClosest(ballon);

            std::cout << "Équipe Gauche: " << scoreLeft << "\tÉquipe droite: " << scoreRight << std::endl;
        }

        gf::Time ips = clock.restart();
        //std::printf("%g\n", 1/ips.asSeconds());
        equipeLeft.update(ips);
        equipeRight.update(ips);

        physic.collisionEquipeEquipe();
        physic.collisionsEquipeTerrain();
        physic.collisionBallonEquipe();
        physic.collisionsBallonTerrain();
        
        ballon.update(ips);

        // Draw the entities
        renderer.setView(view);
        renderer.clear();

        terrain.render(renderer);
        ballon.render(renderer);
        equipeLeft.render(renderer);
        equipeRight.render(renderer);

        renderer.display();
    }

    return 0;
}
