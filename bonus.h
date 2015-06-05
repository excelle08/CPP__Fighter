#ifndef BONUS_H
#define BONUS_H

#include "myobject.h"
#include "config.h"

class BonusLife : public MyObject{
public:
	BonusLife(sf::Vector2f enemyInitPos, sf::Vector2f velocity, string textureFilePath=TextureLib::bonusLife, string type="Enemy") : 
		MyObject(textureFilePath, enemyInitPos, type), _velocity(sf::Vector2f(velocity)){

	}
	~BonusLife(){}
	void animate(){
		if(isOutOfWindow()){
			kill();
		}
		move(_velocity);
		rotate(6);
	}

private:
	sf::Vector2f _velocity;
};

#endif // BONUS_H
