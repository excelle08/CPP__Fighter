#ifndef BOMB_H
#define BOMB_H

#include "myobject.h"
#include "shuttle.h"

class Bomb : public MyObject {
public:
	Bomb(Shuttle &src, sf::Vector2f velocity, string textureFilePath=TextureLib::bomb, string type="Bomb") 
	: MyObject(textureFilePath, sf::Vector2f(0, 0), type), _src(src), _velocity(velocity){
		setPosition(src.getPosition().x + src.getObjSize().x / 2, src.getPosition().y);
	}
	~Bomb(){
	}
	void shoot();
private:
	Shuttle _src;
	sf::Vector2f _velocity;
};

#endif // BOMB_H
