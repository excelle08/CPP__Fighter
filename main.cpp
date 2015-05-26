//g++ -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio main.cpp -o main

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "shuttle.h"
#include "background.h"
#include "bomb.h"
#include "stage.h"
#include "config.h"
#include "enemy.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

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
        int b_spd = stage.getBombSpeed();
        int p_spd = stage.getPlaneSpeed();
        if(window.hasFocus()){
            // Press Q to exit
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                window.close();
                thread.terminate();
                std::exit(0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                Bomb b(plane, sf::Vector2f(0,-b_spd));
                stage.addBomb(b);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                plane.Move(-p_spd, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                plane.Move(p_spd, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                plane.Move(0, -p_spd);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                plane.Move(0, p_spd);
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
        e.setVelocity(sf::Vector2f(0,stage->getEnemySpeed()));
        stage->addEnemy(e);
        // When level is greater than 2, launch bomb randomly
        if(stage->getLevel() >= 2 && random_var % 2 == 0){
            Bomb b(e, sf::Vector2f(0, stage->getBombSpeed()));
            stage->addBomb(b);
        }
        // Update time
        sf::sleep(sf::milliseconds(stage->getEnemyGenRate()));
    }
}

void timer(Stage *stage){
    while(true){
        // TODO: Add timing funcs
        stage->increAvaliableBomb();
        // Draw text
        using namespace std;
        stringstream ss;
        string score_str;
        ss << "Score: ";
        ss << stage->getPoints() << endl;
        ss << "Level: ";
        ss << stage->getLevel() << endl;
        score_str = ss.str();
        stage->setScoreText(score_str);
        // Update time
        sf::sleep(sf::milliseconds(250));
    }
}