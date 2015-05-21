//g++ -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio main.cpp -o main

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "shuttle.h"
#include "background.h"
#include "config.h"
#include "bomb.h"
#include "stage.h"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fighter");
    // Set framerate limit
    window.setFramerateLimit(60);
    // Load the background
    Background bg;
    // Load the shuttle
    Shuttle plane;
    // Create a game stage
    Stage stage(window, bg);
    stage.appendObject(plane);
    stage.playBackMusic();
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        stage.load();
        plane.placeAtBottom();
        if(window.hasFocus()){
            // Press Q to exit
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                window.close();
            }
        }
    }
    return EXIT_SUCCESS;
}