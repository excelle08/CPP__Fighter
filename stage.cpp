#include "stage.h"
#include <iostream>
#include <cstring>

void Stage::setHero(Shuttle *hero){
    this->hero = hero;
}

void Stage::addEnemy(Enemy e){

    e.setStage(this);
    m_enemies.push_back(e);
}

void Stage::addBomb(Bomb b){
    if(avaliableBomb <= 0){
        return;
    }
    b.setStage(this);
    m_bombs.push_back(b);
    avaliableBomb --;
}

void Stage::load(){
	// Clear previous frame
	m_window->clear();
    // Draw stage properties
    drawProperties();
    // Display and finish this frame
    m_window->display();
}

void Stage::playBackMusic(){
	// Play BGM. If failure then display a warning.
	if(m_bg->getMusicState() != sf::SoundStream::Playing){
		if(!m_bg->loadBackMusic()){
        	std::cout << "Warning: Failed to load BGM file." << std::endl;
        	std::cout << "Be sure to check if [" << m_bg->getBGMPath() << "] exists." << std::endl;
    	}
        m_bg->setLoop(true);
	}
}

void Stage::stopBackMusic(){
	m_bg->stopBackMusic();
}

void Stage::playBoomEffect(){
    explosionEff.play();
}


void Stage::drawProperties(){
	// Draw background
    m_window->draw(*m_bg);
    // Draw hero
    m_window->draw(*hero);
    // Draw score text
    m_window->draw(score);
    // Draw and move enemy shuttles
    for(std::vector<Enemy>::iterator i = m_enemies.begin(); i != m_enemies.end();){
        if(m_enemies.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            //(*i).reloadTexture();
            (*i).animate();
            m_window->draw(*i);
            i++;
        } else {
            // IMPORTANT: Method erase() returns the next iterator
            // To pass the next iterator to var i will prevent from operating wild pointer.
            if(level >= 7 || !(*i).isExplosion()){
                // After level 7, every missed enemy costs 10 points
                points -= 10;
            }
            i = m_enemies.erase(i);
        }
    }
    // Draw and move bombs
    for(std::vector<Bomb>::iterator i = m_bombs.begin(); i != m_bombs.end();){
        if(m_bombs.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).reloadTexture();
            (*i).shoot();
            m_window->draw(*i);
            i++;
        } else {
            i = m_bombs.erase(i);
        }
    }
}

int Stage::getValueByLevel(int count, ...){
    int args[count];
    va_list a;
    va_start(a, count);
    for(int i=0; i<count; i++){
        args[i] = va_arg(a, int);
    }
    va_end(a);
    if(level >= count){
        return args[count-1]; 
    } else {
        return args[level-1];
    }
}

void Stage::collisionTest(){
    // Collision test between bombs and enemies
    while(true){
        for(std::vector<Enemy>::iterator e = m_enemies.begin(); e != m_enemies.end(); ++e){
            if(m_enemies.size() == 0){
                break;
            }
            for(std::vector<Bomb>::iterator b = m_bombs.begin(); b != m_bombs.end(); ++b){
                if(m_bombs.size() == 0){
                    break;
                }
                sf::Vector2u size_e = e->getObjSize();
                sf::Vector2u size_b = b->getObjSize();
                sf::Vector2f pos_e = e->getPosition();
                sf::Vector2f pos_b = b->getPosition();
                if( (pos_e.x <= pos_b.x && pos_e.x + size_e.x >= pos_b.x) && (pos_e.y + size_e.y >= pos_b.y && pos_e.y <= pos_b.y)) {
                    points += 20;
                    playBoomEffect();
                    e->kill(true);
                    b->kill();
                }
            }
        }
        sf::sleep(sf::milliseconds(50));
    }
}

inline void Stage::keyBoardEvents(MyObject *obj){
	// Listen to keyboard press when the window is active
    if (m_window->hasFocus()){

	}
} 
