#ifndef ENEMY_H
#define ENEMY_H

#include "myobject.h"

class Enemy : public MyObject {
public:
	Enemy(sf::Vector2f enemyInitPos, string textureFilePath="resources/images/enemy.png", string type="Enemy") : 
		MyObject(textureFilePath, enemyInitPos, type), _velocity(sf::Vector2f(0, 10)){

	}
	~Enemy(){
		
	}
	void setVelocity(sf::Vector2f v){
		_velocity = v;
	}
	void animate();
private:
	sf::Vector2f _velocity;
};

#endif // ENEMY_H
