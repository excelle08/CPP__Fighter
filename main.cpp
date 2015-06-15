//g++ -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio main.cpp -o main

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "shuttle.h"
#include "background.h"
#include "bomb.h"
#include "stage.h"
#include "config.h"
#include "enemy.h"
#include "bonus.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <iostream>

#define RATE 11

void generateEnemy(Stage *stage);
void timer(Stage *stage);
void generateLifeBonus(Stage *stage);
sf::Vector2f getVelocityVect(sf::Vector2f start, sf::Vector2f end, float length);

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
    stage.setGameStatus(STANDBY);
    // Create a enemy generator thread
    sf::Thread thread(&generateEnemy, &stage);
    // This is a timer thread
    sf::Thread th_timer(&timer, &stage);
    // Collision tester
    sf::Thread th_coltest(&Stage::collisionTest, &stage);
    // Create a life-point bonus generator thread
    sf::Thread th_bonus_life(&generateLifeBonus, &stage);

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
                th_bonus_life.terminate();
            }
        }

        if (stage.getGameStatus() == STANDBY){
            string msg = 
            "  Welcome to Fighter\nPress ESC to start playing\nPress H to get help message\nPress Q to quit the game.\n";
            stage.drawMessage(msg);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                thread.launch();
                th_coltest.launch();
                th_timer.launch();
                th_bonus_life.launch();
                stage.setGameStatus(START);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
                stage.setGameStatus(HELPMSG);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                std::exit(0);
            }
        } else if (stage.getGameStatus() == START){
            stage.loadFrame();
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
                if(stage.getPlaneLife() <= 0){
                    stage.setGameStatus(GAMEOVER);
                }
            }
        } else if (stage.getGameStatus() == HELPMSG){
            string msg = "1.Use direction keys to control your\n shuttle\n2.Press space key to launch bomb\n3.You get 20 points for each hit\n4.Every bomb costs 5 points\n5.Every 500 points you get a level up\n6.Difficulty increases as your level up\n7.After level 7 every missed enemy\n costs 10pts\n8.Avoid bombs from enemies\n9.If life goes to zero you lose\n10.Press Equal to stop BGM\n11.Press minus to revive BGM\n12.Press 0 to stop sound effect\n13.Press 9 to revive sound effect\n    HAVE FUN~\n  PRESS BACKSPACE TO GO BACK";
            stage.drawMessage(msg);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                stage.setGameStatus(STANDBY);
            }

        } else if (stage.getGameStatus() == GAMEOVER){
            thread.terminate();
            th_timer.terminate();
            th_coltest.terminate();
            th_bonus_life.terminate();
            string msg = "  GAME OVER!!\nPress Q to end and R to replay.\n";
            stage.drawMessage(msg);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                thread.launch();
                th_timer.launch();
                th_coltest.launch();
                stage.reset();
                stage.setGameStatus(START);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                std::exit(0);
            }
        } else {

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)){
            stage.stopBackMusic();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){
            stage.reviveBackMusic();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
            stage.disableSoundEffect();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
            stage.enableSoundEffect();
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
        // Lock resource for thread safety
        stage->addEnemy(e);
        // When level is greater than 2, launch bomb randomly
        if(stage->getLevel() >= 2 && stage->getLevel() <= 5 && random_var % 2 == 0){
            Bomb b(e, sf::Vector2f(0, stage->getBombSpeed()*2), TextureLib::bomb_enemy);
            b.setColor(sf::Color::Red);
            stage->addBomb(b);
        } else if (stage->getLevel() >= 6 && random_var % 3 != 0){
            Bomb b(e, getVelocityVect(e.getPosition(), stage->getHeroPos(), stage->getBombSpeed()*1.5), TextureLib::bomb_enemy);
            b.setColor(sf::Color::Yellow);
            stage->addBomb(b);
        }
        // Update time
        sf::sleep(sf::milliseconds(1000 * ( ( 800 / stage->getEnemySpeed() ) / 60 ) / stage->getEnemyGenRate()));
    }
}

void generateLifeBonus(Stage *stage){
    std::srand(std::time(0));
    while(true){
        int random_var = std::rand();
        BonusLife b(sf::Vector2f(random_var%400, 0), sf::Vector2f(0, stage->getBombSpeed()));
        stage->addLifeBonus(b);
        sf::sleep(sf::milliseconds(9000));

    }
}

void timer(Stage *stage){
    while(true){
        // TODO: Add timing funcs
        stage->increAvaliableBomb();
        unsigned long int before = stage->getFrameCount();
        // Update time
        sf::sleep(sf::milliseconds(stage->getShootingRate()));
        // Draw text
        unsigned long int now = stage->getFrameCount();
        using namespace std;
        stringstream ss;
        string score_str;
        ss << "Score: ";
        ss << stage->getPoints() << endl;
        ss << "Level: ";
        ss << stage->getLevel() << endl;
        ss << "Life: ";
        ss << stage->getPlaneLife() << endl;
        score_str = ss.str();
        stage->setScoreText(score_str);

    }
}

sf::Vector2f getVelocityVect(sf::Vector2f start, sf::Vector2f end, float length){
    float x = (end.x - start.x) / sqrtf((end.x - start.x)*(end.x - start.x) + (end.y-start.y)*(end.y-start.y));
    float y = (end.y - start.y) / sqrtf((end.x - start.x)*(end.x - start.x) + (end.y-start.y)*(end.y-start.y));
    return sf::Vector2f(x * length, y * length);
}