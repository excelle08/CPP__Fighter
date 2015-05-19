#ifndef SHUTTLE_H
#define SHUTTLE_H

#include "myobject.h"

class Shuttle : public MyObject {
public:
	Shuttle(string textureFilePath="resources/images/plane.png", sf::Vector2f initPos=sf::Vector2f(0, 0))
		: MyObject(textureFilePath, initPos){}
	~Shuttle(){
	}
	void Move(float x, float y);
	void placeAtBottom();
	void fire(sf::RenderWindow &window);
private: 
};

#endif // SHUTTLE_H
