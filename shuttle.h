#ifndef SHUTTLE_H
#define SHUTTLE_H

#include "myobject.h"
#include <vector>

class Shuttle : public MyObject {
public:
	Shuttle(string textureFilePath="resources/images/plane.png", sf::Vector2f initPos=sf::Vector2f(0, 0), string type="Shuttle")
		: MyObject(textureFilePath, initPos, type, true){}
	virtual ~Shuttle(){
	}
	void Move(float x, float y);
	void placeAtBottom();
	void fire();
private: 

};

#endif // SHUTTLE_H
