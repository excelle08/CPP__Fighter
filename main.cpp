//g++ -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio main.cpp -o main

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "shuttle.h"
#include "background.h"
#include "config.h"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fighter");
    // Set framerate limit
    window.setFramerateLimit(60);

    // Load the background
    Background bg;
    // Play BGM. If failure then display a warning.
    if(!bg.loadBackMusic()){
        cout << "Warning: Failed to load BGM file." << endl;
        cout << "Be sure to check if [" << bg.getBGMPath() << "] exists." << endl;
    }
    
    // Load the shuttle
    Shuttle plane;
    
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the background
        window.draw(bg);
        // Draw the sprite
        window.draw(plane);
        plane.placeAtBottom();
        // Listen to keyboard press when the window is active
        if (window.hasFocus()){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                plane.Move(-5, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                plane.Move(5, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                plane.Move(0, -5);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                plane.Move(0, 5);
            }
            // Press Q to exit
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                window.close();
            }
        }
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}