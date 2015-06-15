#ifndef SUPER_H
#define SUPER_H

#include "myobject.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <ctime>

class Super : public MyObject{
public:
	Super(sf::Vector2f enemyInitPos, string textureFilePath="resources/images/super.png", string type="SuperEnemy") : 
		MyObject(textureFilePath, enemyInitPos, type), _velocity(sf::Vector2f(0, 1)), life(20){
		txtDamage1.loadFromFile("resources/images/super_damage1.png");
		txtDamage2.loadFromFile("resources/images/super_damage2.png");
		txtDamage3.loadFromFile("resources/images/super_damage3.png");
		std::srand(std::time(0));
	}
	~Super(){

	}
	void animate();
	void kill(bool isBoom=false);
private:
	sf::Vector2f getVelocityVect(sf::Vector2f start, sf::Vector2f end, float length){
    	float x = (end.x - start.x) / sqrtf((end.x - start.x)*(end.x - start.x) + (end.y-start.y)*(end.y-start.y));
    	float y = (end.y - start.y) / sqrtf((end.x - start.x)*(end.x - start.x) + (end.y-start.y)*(end.y-start.y));
    	return sf::Vector2f(x * length, y * length);
	}
	sf::Vector2f _velocity;
	sf::Texture txtDamage1;
	sf::Texture txtDamage2;
	sf::Texture txtDamage3;
	int life;
};

#endif // SUPER_H
