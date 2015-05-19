#ifndef BOMB_H
#define BOMB_H

#include "myobject.h"
#include "shuttle.h"

class Bomb : public MyObject {
public:
	Bomb(Shuttle &src, string textureFilePath="resources/images/bomb.png") : MyObject(textureFilePath, 
		sf::Vector2f(src.getPosition().x + src.getObjSize().x / 2, 
			src.getPosition().y)) {
	}
	Bomb(string textureFilePath="resources/images/bomb.png", sf::Vector2f initPos=sf::Vector2f(0, 0))
		: MyObject(textureFilePath, initPos) {
	}
	~Bomb(){
	}

	void shoot(float speed=5);
};

#endif // BOMB_H
