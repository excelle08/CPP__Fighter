#ifndef STAGE_H
#define STAGE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdarg>
#include "myobject.h"
#include "background.h"
#include "enemy.h"
#include "bomb.h"
#include "shuttle.h"
#include "bonus.h"
#include "super.h"
#include "config.h"

#define OBJECTS_MAX_VAL 8

enum Status{
	STANDBY=0,
	START=1,
	GAMEOVER=2,
	HELPMSG=3
};

class Stage
{
public:
	Stage(sf::RenderWindow &currentWindow, Background &bg, string expSoundPath=AudioLib::bang, string fontPath=FontLib::arial,
		string damageSoundPath=AudioLib::damage, string upgradeSoundPath=AudioLib::upgrade) : 
		m_window(&currentWindow), m_bg(&bg){
		avaliableBomb = 1;
		maxBomb = 1;
		explosionEffectData.loadFromFile(expSoundPath);
		explosionEff.setBuffer(explosionEffectData);
		damageEffectData.loadFromFile(damageSoundPath);
		damageEff.setBuffer(damageEffectData);
		upgradeEffectData.loadFromFile(upgradeSoundPath);
		upgradeEff.setBuffer(upgradeEffectData);
		msgFont.loadFromFile(fontPath);
		score.setFont(msgFont);
		score.setColor(sf::Color(sf::Color::Red));
		score.setPosition(sf::Vector2f(0,0));
		score.setString("Score: 50");
		points = 50;
		level = 1;
		allowSoundEffect = true;
		framecount = 0;

	}
	virtual ~Stage(){
	
	}
	void setHero(Shuttle *hero);
	void addEnemy(Enemy e);
	void addBomb(Bomb b);
	void addLifeBonus(BonusLife b);
	void addSuper(Super s);
	void loadFrame();
	void playBackMusic();
	void stopBackMusic();
	void reviveBackMusic();
	void playBoomEffect();
	void playDamageEffect();
	void playUpgradeEffect();
	sf::Vector2u getWindowSize(){
		return m_window->getSize();
	}
	sf::Vector2f getHeroPos(){
		return hero->getPosition();
	}
	void increAvaliableBomb(){
		if(avaliableBomb >= maxBomb || points <= 0){
			return;
		}
		avaliableBomb ++;
		// Every bomb consumes 5 points
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
		int level_pre = level;
		level = points / 500 + 1;
		if(level > level_pre){
			playUpgradeEffect();
		}
		return points;
	}
	int getLevel(){
		return level;
	}
	int getPlaneSpeed(){
		return getValueByLevel(8,6,6,6,7,8,9,10,10);
	}
	int getBombSpeed(){
		return getValueByLevel(8,5,6,7,8,9,10,10,10);
	}
	int getEnemySpeed(){
		return getValueByLevel(8,5,6,6,7,7,8,8,10);
	}
	int getShootingRate(){
		return getValueByLevel(8,500,400,250,250,200,150,120,120);
	}
	int getEnemyGenRate(){
		return getValueByLevel(8,2,2,3,3,3,4,5,6);
	}
	int getPlaneLife(){
		return hero->getLife();
	}
	void setPlaneLife(int val){
		hero->setLife(val);
	}
	void setGameStatus(int stat){
		gameStatus = stat;
	}
	int getGameStatus(){
		return gameStatus;
	}
	void disableSoundEffect(){
		allowSoundEffect = false;
	}
	void enableSoundEffect(){
		allowSoundEffect = true;
	}
	unsigned long int getFrameCount(){
		return framecount;
	}
	int getBombCount(){
		return m_bombs.size();
	}
	int getEnemyCount(){
		return m_enemies.size();
	}
	int getBonusCount(){
		return m_bonus_life.size();
	}
	void reset();
	void collisionTest();
	void drawMessage(string msg, sf::Vector2f position = sf::Vector2f(10, 240), int fontSize=24, sf::Color color = sf::Color::Black);
	sf::Mutex mutex;
private:
	void drawProperties();
	int getValueByLevel(int count, ...);
	inline void keyBoardEvents(MyObject *obj);
	sf::RenderWindow *m_window;
	std::vector<Enemy> m_enemies;
 	std::vector<Bomb> m_bombs;
 	std::vector<BonusLife> m_bonus_life;
 	std::vector<Super> m_super;
 	int points;
	int level;
 	sf::SoundBuffer explosionEffectData;
 	sf::SoundBuffer damageEffectData;
 	sf::SoundBuffer upgradeEffectData;
 	sf::Font msgFont;
 	sf::Text score;
 	sf::Sound explosionEff;
 	sf::Sound damageEff;
 	sf::Sound upgradeEff;
	Shuttle *hero;
	Background *m_bg;
	int avaliableBomb;
	int maxBomb;
	int gameStatus;
	bool allowSoundEffect;
	unsigned long int framecount;

};

#endif // STAGE_H
