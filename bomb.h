#ifndef BOMB_H
#define BOMB_H

#include "myobject.h"
#include "shuttle.h"

class Bomb : public MyObject {
public:
	Bomb(Shuttle &src, string textureFilePath="resources/images/bomb.png", string type="Bomb") 
	: MyObject(textureFilePath, 
				sf::Vector2f(src.getPosition().x + src.getObjSize().x / 2, 
							 src.getPosition().y)), 
	  pos_X(src.getPosition().x), pos_Y(src.getPosition().y) {
	}
	~Bomb(){
	}
	void shoot(float speed=5);
private:
	void thisMove(float x, float y);
	float pos_X;
	float pos_Y;
};

#endif // BOMB_H
