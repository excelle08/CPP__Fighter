//g++ -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio main.cpp -o main

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "shuttle.h"
#include "background.h"
#include "config.h"
#include "bomb.h"
#include "stage.h"
#include "enemy.h"
#include <cstdlib>
#include <ctime>

#define RATE 11

void generateEnemy(Stage *stage);
void timer(Stage *stage);

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
    stage.setHero(&plane);
    plane.placeAtBottom();
    stage.playBackMusic();
    // Create a enemy generator thread
    sf::Thread thread(&generateEnemy, &stage);
    thread.launch();
    // This is a timer thread
    sf::Thread th_timer(&timer, &stage);
    th_timer.launch();
    // Collision tester
    sf::Thread th_coltest(&Stage::collisionTest, &stage);
    th_coltest.launch();

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed){
                window.close();
                thread.terminate();
                th_timer.terminate();
                th_coltest.terminate();
            }
        }

        stage.load();
        if(window.hasFocus()){
            // Press Q to exit
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                window.close();
                thread.terminate();
                std::exit(0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                Bomb b(plane, sf::Vector2f(0,-7));
                stage.addBomb(b);
            }
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)){
                stage.stopBackMusic();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
                stage.playBackMusic();
            }
        }
    }
    return EXIT_SUCCESS;
}

void generateEnemy(Stage *stage){
    std::srand(std::time(0));
    while(true){
        int random_var = std::rand();
        Enemy e(sf::Vector2f(random_var%400, 0));
        e.setVelocity(sf::Vector2f(0,4));
        stage->addEnemy(e);
        sf::sleep(sf::milliseconds(1000));
    }
}

void timer(Stage *stage){
    while(true){
        // TODO: Add timing funcs
        stage->increAvaliableBomb();
        sf::sleep(sf::milliseconds(500));
    }
}