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
#include "config.h"

#define OBJECTS_MAX_VAL 8

class Stage
{
public:

	Stage(sf::RenderWindow &currentWindow, Background &bg, string expSoundPath=AudioLib::bang, string fontPath=FontLib::arial) : 
		m_window(&currentWindow), m_bg(&bg){
		avaliableBomb = 1;
		maxBomb = 1;
		explosionEffectData.loadFromFile(expSoundPath);
		explosionEff.setBuffer(explosionEffectData);
		msgFont.loadFromFile(fontPath);
		score.setFont(msgFont);
		score.setColor(sf::Color(sf::Color::Red));
		score.setPosition(sf::Vector2f(0,0));
		score.setString("Score: 10");
		points = 0;
		level = 1;
	}
	virtual ~Stage(){
	
	}
	void setHero(Shuttle *hero);
	void addEnemy(Enemy e);
	void addBomb(Bomb b);
	void load();
	void playBackMusic();
	void stopBackMusic();
	void playBoomEffect();
	sf::Vector2u getWindowSize(){
		return m_window->getSize();
	}
	void increAvaliableBomb(){
		if(avaliableBomb >= maxBomb || points <= 0){
			return;
		}
		avaliableBomb ++;
		points -= 5;
	}
	void setScoreText(string str){
		score.setString(str);
	}
	int getAvaliableBomb() {
		return avaliableBomb;
	}
	int getMaxBomb(){
		return maxBomb;
	}
	int getPoints(){
		level = points / 500 + 1;
		return points;
	}
	int getLevel(){
		return level;
	}
	int getPlaneSpeed(){
		return 2 + level * 2;
	}
	int getBombSpeed(){
		return 2 + level * 3;
	}
	int getEnemySpeed(){
		return level * 4;
	}
	int getEnemyGenRate(){
		return 3200 / level;
	}
	void collisionTest();

private:
	void drawProperties();
	inline void keyBoardEvents(MyObject *obj);
	sf::RenderWindow *m_window;
	std::vector<Enemy> m_enemies;
 	std::vector<Bomb> m_bombs;
 	int points;
	int level;
 	sf::SoundBuffer explosionEffectData;
 	sf::Font msgFont;
 	sf::Text score;
 	sf::Sound explosionEff;
	Shuttle *hero;
	Background *m_bg;
	int avaliableBomb;
	int maxBomb;

};

#endif // STAGE_H
