#include "stage.h"
#include <iostream>
#include <cstring>
#include <cstddef>

void Stage::setHero(Shuttle *hero){
    this->hero = hero;
}

void Stage::addEnemy(Enemy e){
    mutex.lock();
    e.setStage(this);
    m_enemies.push_back(e);
    mutex.unlock();
}

void Stage::addBomb(Bomb &b){
    if(avaliableBomb <= 0){
        return;
    }
    b.setStage(this);
    mutex.lock();
    m_bombs.push_back(b);
    mutex.unlock();
    avaliableBomb --;
}

void Stage::addBomb_e(Bomb &b){
    mutex.lock();
    b.setStage(this);
    m_bombs_e.push_back(b);
    mutex.unlock();
}

void Stage::addLifeBonus(BonusLife b){
    mutex.lock();
    b.setStage(this);
    m_bonus_life.push_back(b);
    mutex.unlock();
}

void Stage::addSuper(Super s){
    mutex.lock();
    s.setStage(this);
    m_super.push_back(s);
    mutex.unlock();
}

void Stage::loadFrame(){
	// Clear previous frame
    sf::Clock c;
    unsigned int start = c.getElapsedTime().asMilliseconds();
	m_window->clear();
    // Draw stage properties
    drawProperties();
    // Display and finish this frame
    m_window->display();
    unsigned int end = c.getElapsedTime().asMilliseconds();
    fps = 1000 / (end - start);
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
            if((!(*i).isExplosion())){
               // After level 7, every missed enemy costs 10 points
               points -= 10 * level;
            }
            // If out of window then die
            if((*i).isOutOfWindow()){
                mutex.lock();
                i = m_enemies.erase(i);
                m_enemies.swap(m_enemies);
                mutex.unlock();
                continue;
            }
            // If a enemy is hit play explosion animation then die.
            if(((*i).isExplosion()) && !(*i).playExplodeAnimate()){
                // IMPORTANT: Method erase() returns the next iterator
                // To pass the next iterator to var i will prevent from operating wild pointer.
                mutex.lock();
                i = m_enemies.erase(i);
                m_enemies.swap(m_enemies);
                mutex.unlock();
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
            mutex.lock();
            i = m_bombs.erase(i);
            m_bombs.swap(m_bombs);
            mutex.unlock();
        }
    }

    for(std::vector<Bomb>::iterator i = m_bombs_e.begin(); i != m_bombs_e.end();){
        if(m_bombs_e.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).reloadTexture();
            (*i).shoot();
            m_window->draw(*i);
            i++;
        } else {
            mutex.lock();
            i = m_bombs_e.erase(i);
            m_bombs_e.swap(m_bombs_e);
            mutex.unlock();
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
            mutex.lock();
            i = m_bonus_life.erase(i);
            m_bonus_life.swap(m_bonus_life);
            mutex.unlock();
        }
    }

    // Draw super shuttles
    for(std::vector<Super>::iterator i = m_super.begin(); i != m_super.end();){
        if(m_super.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).animate();
            m_window->draw(*i);
            i++;
        } else {
            mutex.lock();
            i = m_super.erase(i);
            if((*i).isExplosion()){
                points += 250;
            }
            m_super.swap(m_super);
            mutex.unlock();
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
    while(true){
        sf::sleep(sf::milliseconds(100));
        mutex.lock();
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
                if((pos_e.x <= pos_b.x && pos_e.x + size_e.x >= pos_b.x) && (pos_e.y + size_e.y >= pos_b.y && pos_e.y <= pos_b.y)) {
                    points += 20;
                    playBoomEffect();
                    e->kill(true);
                    b->kill();
                }
            }
        }
        for(std::vector<Bomb>::iterator b = m_bombs_e.begin(); b != m_bombs_e.end(); ++b){
            if(m_bombs_e.size() == 0){
                break;
            }
            // Bombs and shuttle
            sf::Vector2f pos_b = b->getPosition();
            sf::Vector2u size_h = hero->getObjSize();
            sf::Vector2f pos_h = hero->getPosition();
            if((pos_h.x <= pos_b.x && pos_h.x + size_h.x >= pos_b.x) && (pos_h.y + size_h.y >= pos_b.y && pos_h.y <= pos_b.y)){
                playDamageEffect();
                hero->kill();
                b->kill();
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
                if( (b->getSrcType() == "Shuttle") && (pos_e.x <= pos_b.x && pos_e.x + size_e.x >= pos_b.x) && (pos_e.y + size_e.y >= pos_b.y && pos_e.y <= pos_b.y)) {
                    hero->addLife();
                    playBoomEffect();
                    bn->kill(true);
                    b->kill();
                }
            }
            for(std::vector<Super>::iterator s = m_super.begin(); s != m_super.end(); ++s){
                if(m_super.size() == 0){
                    break;
                }
                if(!(*s).getLifeState()){
                    continue;
                }
                sf::Vector2u size_e = s->getObjSize();
                sf::Vector2f pos_e = s->getPosition();
                sf::Vector2f pos_b = b->getPosition();
                if( (b->getSrcType() == "Shuttle") && (pos_e.x <= pos_b.x && pos_e.x + size_e.x >= pos_b.x) && (pos_e.y + size_e.y >= pos_b.y && pos_e.y <= pos_b.y)) {
                    playBoomEffect();
                    s->kill(true);
                    b->kill();
                }
            }
        }
        mutex.unlock();
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
    m_bonus_life.clear();
    m_super.clear();
    hero->setLife(50);
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
