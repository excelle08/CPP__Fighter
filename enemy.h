#ifndef ENEMY_H
#define ENEMY_H

#include "myobject.h"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Enemy : public MyObject {
public:
	Enemy(sf::Vector2f enemyInitPos, string textureFilePath="resources/images/enemy.png", string type="Enemy") : 
		MyObject(textureFilePath, enemyInitPos, type), _velocity(sf::Vector2f(0, 10)), ttl(24){

	}
	~Enemy(){
		
	}
	void setVelocity(sf::Vector2f v){
		_velocity = v;
	}
	void animate();
	int explodeAnimateTtl(){
		ttl --;
		return ttl;
	}
	void playBoomEffect();
private:
	sf::Vector2f _velocity;
	int ttl;
};

#endif // ENEMY_H
