#include "stage.h"
#include <iostream>
#include <cstring>
#include <cstddef>

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

void Stage::addLifeBonus(BonusLife b){
    b.setStage(this);
    m_bonus_life.push_back(b);
}

void Stage::load(){
	// Clear previous frame
	m_window->clear();
    // Draw stage properties
    drawProperties();
    // Display and finish this frame
    m_window->display();
    framecount ++;
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

void Stage::reviveBackMusic(){
    m_bg->reviveBackMusic();
}

void Stage::playBoomEffect(){
    if(allowSoundEffect){
        explosionEff.setVolume(50);
        explosionEff.play();
    }
}

void Stage::playDamageEffect(){
    if(allowSoundEffect){
        damageEff.play();
    }
}

void Stage::playUpgradeEffect(){
    if(allowSoundEffect){
        upgradeEff.setVolume(100);
        upgradeEff.play();
    }
}


void Stage::drawProperties(){
    elementsLock = true;
    //std::cout << "Stage::draw::elLock: " << elementsLock << endl;
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
            (*i).animate();
            m_window->draw(*i);
            i++;
        } else {
            if(level >= 7 && (!(*i).isExplosion())){
               // After level 7, every missed enemy costs 10 points
               points -= 10;
            }
            // If out of window then die
            if((*i).isOutOfWindow() && !coltestLock){
                i = m_enemies.erase(i);
                m_enemies.swap(m_enemies);
                continue;
            }
            // If a enemy is hit play explosion animation then die.
            if(((*i).isExplosion()) && !(*i).playExplodeAnimate() && !coltestLock){
                // IMPORTANT: Method erase() returns the next iterator
                // To pass the next iterator to var i will prevent from operating wild pointer.
                i = m_enemies.erase(i);
                m_enemies.swap(m_enemies);
            } else {
                m_window->draw(*i);
                i++;
            }
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
            if(!coltestLock){
                i = m_bombs.erase(i);
                m_bombs.swap(m_bombs);
            }
        }
    }

    // Draw life-point bonus
    for(std::vector<BonusLife>::iterator i = m_bonus_life.begin(); i != m_bonus_life.end();){
        if(m_bonus_life.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).animate();
            m_window->draw(*i);
            i++;
        } else {
            if(!coltestLock){
                i = m_bonus_life.erase(i);
                m_bonus_life.swap(m_bonus_life);
            }
        }
    }
    elementsLock = false;
    //std::cout << "Stage::draw::elLock: " << elementsLock << endl;
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
    while(true){
        //std::cout << "FPS: " << (now - before) * 10);
        //std::cout << "bombs: " << getBombCount() << ";enemies: " << getEnemyCount() << ";bonus: " << getBonusCount() << endl;
        sf::sleep(sf::milliseconds(100));
        if(elementsLock){
            continue;
        }
        coltestLock = true;
        //std::cout<<"ColTest: elLock: " << elementsLock << "\t" << endl;
        for(std::vector<Enemy>::iterator e = m_enemies.begin(); e != m_enemies.end(); ++e){
            if(m_enemies.size() == 0){
                break;
            }  
            if(!(*e).getLifeState()){
                continue;
            }
            for(std::vector<Bomb>::iterator b = m_bombs.begin(); b != m_bombs.end(); ++b){
                if(m_bombs.size() == 0){
                    break;
                } 
                sf::Vector2u size_e = e->getObjSize();
                sf::Vector2f pos_e = e->getPosition();
                sf::Vector2f pos_b = b->getPosition();
                // Collision test between bombs and enemies
                if( (b->getSrcType() == "Shuttle") && (pos_e.x <= pos_b.x && pos_e.x + size_e.x >= pos_b.x) && (pos_e.y + size_e.y >= pos_b.y && pos_e.y <= pos_b.y)) {
                    points += 20;
                    playBoomEffect();
                    e->kill(true);
                    b->kill();
                }
                // Bombs and shuttle
                sf::Vector2u size_h = hero->getObjSize();
                sf::Vector2f pos_h = hero->getPosition();
                if( (b->getSrcType() == "Enemy") && (pos_h.x <= pos_b.x && pos_h.x + size_h.x >= pos_b.x) && (pos_h.y + size_h.y >= pos_b.y && pos_h.y <= pos_b.y)){
                    playDamageEffect();
                    hero->kill();
                    b->kill();
                }
            }
        }
        // Collision test between bonus object and bomb
        for(std::vector<Bomb>::iterator b = m_bombs.begin(); b != m_bombs.end(); ++b){
            if(m_bombs.size() == 0){
                break;
            }
            for(std::vector<BonusLife>::iterator bn = m_bonus_life.begin(); bn != m_bonus_life.end(); ++bn){
                if(m_bonus_life.size() == 0){
                    break;
                }
                if(!(*bn).getLifeState()){
                    continue;
                }
                sf::Vector2u size_e = bn->getObjSize();
                sf::Vector2f pos_e = bn->getPosition();
                sf::Vector2f pos_b = b->getPosition();
                // Collision test between bombs and enemies
                if( (b->getSrcType() == "Shuttle") && (pos_e.x <= pos_b.x && pos_e.x + size_e.x >= pos_b.x) && (pos_e.y + size_e.y >= pos_b.y && pos_e.y <= pos_b.y)) {
                    hero->addLife();
                    playBoomEffect();
                    bn->kill(true);
                    b->kill();
                }
            }
        }
        coltestLock = false;
    }
}

inline void Stage::keyBoardEvents(MyObject *obj){
	// Listen to keyboard press when the window is active
    if (m_window->hasFocus()){

	}
} 

void Stage::reset(){
    points = 50;
    level = 1;
    m_bombs.clear();
    m_enemies.clear();
    hero->setLife(20);
}

void Stage::drawMessage(string msg, sf::Vector2f position, int fontSize, sf::Color color){
    // Clear previous frame
    m_window->clear();
    // Draw background
    m_window->draw(*m_bg);
    sf::Text message;
    message.setFont(msgFont);
    message.setColor(color);
    message.setCharacterSize(fontSize);
    message.setPosition(position);
    message.setString(msg);
    m_window->draw(message);
    // Display
    m_window->display();
}
