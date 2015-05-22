#include "stage.h"
#include <iostream>

void Stage::setHero(Shuttle *hero){
    this->hero = hero;
}

void Stage::addEnemy(Enemy e){

    e.setStage(this);
    m_enemies.push_back(e);
}

void Stage::addBomb(Bomb b){

    b.setStage(this);
    m_bombs.push_back(b);
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
	}
}

void Stage::stopBackMusic(){
	m_bg->stopBackMusic();
}


void Stage::drawProperties(){
	// Draw background
    m_window->draw(*m_bg);
    // Draw hero
    m_window->draw(*hero);
    // Keyboard binding to hero
    keyBoardEvents(hero);
    // Draw and move enemy shuttles
    for(std::vector<Enemy>::iterator i = m_enemies.begin(); i != m_enemies.end(); ++i){
        if(m_enemies.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).animate();
            m_window->draw(*i);
        } else {
            m_enemies.erase(i);
        }
    }
    // Draw and move bombs
    for(std::vector<Bomb>::iterator i = m_bombs.begin(); i != m_bombs.end(); ++i){
        if(m_bombs.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).reloadTexture();
            (*i).shoot();
            m_window->draw(*i);
        } else {
            m_bombs.erase(i);
        }
    }
    
}

inline void Stage::keyBoardEvents(MyObject *obj){
	// Listen to keyboard press when the window is active
    if (m_window->hasFocus()){

	}
} 
