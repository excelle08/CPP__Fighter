#ifndef STAGE_H
#define STAGE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "myobject.h"
#include "background.h"
#include "enemy.h"
#include "bomb.h"
#include "shuttle.h"

#define OBJECTS_MAX_VAL 8

class Stage
{
public:

	Stage(sf::RenderWindow &currentWindow, Background &bg) : m_window(&currentWindow), m_bg(&bg){
	
	}
	virtual ~Stage(){
	
	}
	void setHero(Shuttle *hero);
	void addEnemy(Enemy e);
	void addBomb(Bomb b);
	void load();
	void playBackMusic();
	void stopBackMusic();
	sf::Vector2u getWindowSize(){
		return m_window->getSize();
	}

private:
	void drawProperties();
	inline void keyBoardEvents(MyObject *obj);
	sf::RenderWindow *m_window;
	std::vector<Enemy> m_enemies;
 	std::vector<Bomb> m_bombs;
	Shuttle *hero;
	Background *m_bg;
};

#endif // STAGE_H
