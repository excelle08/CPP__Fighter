#ifndef MYOBJECT_H
#define MYOBJECT_H

// This is an base class representing all objects to be painted.

#include <SFML/Graphics.hpp>

#ifndef IOSTREAM_INC
#define IOSTREAM_INC
#include <iostream>
#endif // IOSTREAM_INC

using namespace std;

class Stage;
class MyObject : public sf::Sprite {
public:
	MyObject(string textureFilePath, sf::Vector2f objPosition, string type="Object", bool bindKeyboardEvent=false);
	~MyObject(){

	}
	// Move functions requires RELATIVE displacement value.
	virtual void Move(float x, float y){
		m_position.x += x;
		m_position.y += y;
		move(x, y);

	}
	sf::Vector2u getObjSize(){
		return sf::Vector2u(getTextureRect().width, getTextureRect().height);
	}
	// The original method getPosition() and getOrigin() sometimes returns wrong value(like zero)”
	sf::Vector2f getObjPos(){
		return m_position;
	}
	string getType(){
		return __type__;
	}
	Stage *getStage(){
		return __stage__;
	}
	void setStage(Stage *s){
		__stage__ = s;
	}
	virtual void kill(bool boom=false){
		isAlive = false;
		isBoomed = boom;
	}
	bool isExplosion(){
		return isBoomed;
	}
	bool getKeyboardBinding(){
		return listenKeyEvent;
	}
	bool getLifeState(){
		return isAlive;
	}
	void reloadTexture(){
		setTexture(m_texture);
	}
	virtual bool isOutOfWindow();
protected:
    Stage *__stage__;
    sf::Texture m_texture;
    bool isAlive;
    bool isBoomed;
private:
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::Vector2f m_position;
    string __type__;
    bool listenKeyEvent;
};

#endif // MYOBJECT_H
