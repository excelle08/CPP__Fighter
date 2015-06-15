#ifndef SUPER_H
#define SUPER_H

#include "myobject.h"
#include <SFML/Graphics.hpp>

class Super : public MyObject{
public:
	Super(sf::Vector2f enemyInitPos, string textureFilePath="resources/images/super.png", string type="SuperEnemy") : 
		MyObject(textureFilePath, enemyInitPos, type), _velocity(sf::Vector2f(0, 2)), life(20){
		txtDamage1.loadFromFile("resources/images/super_damage1.png");
		txtDamage2.loadFromFile("resources/images/super_damage2.png");
		txtDamage3.loadFromFile("resources/images/super_damage3.png");
	}
	~Super(){

	}
	void animate();
	void kill(bool isBoom=false);
private:
	sf::Vector2f _velocity;
	sf::Texture txtDamage1;
	sf::Texture txtDamage2;
	sf::Texture txtDamage3;
	int life;
};

#endif // SUPER_H
