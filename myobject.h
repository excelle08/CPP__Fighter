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
class MyObject : public sf::Drawable, public sf::Transformable {
public:
	MyObject(string textureFilePath, sf::Vector2f objPosition, string type="Object", bool bindKeyboardEvent=false);
	~MyObject(){

	}
	// Move functions requires RELATIVE displacement value.
	virtual void Move(float x, float y){
		move(x, y);
	}
	sf::Vector2u getObjSize(){
		return m_texture.getSize();
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
	bool getKeyboardBinding(){
		return listenKeyEvent;
	}
protected:
    Stage *__stage__;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::Texture m_vertices;
    string __type__;
    bool listenKeyEvent;
};

#endif // MYOBJECT_H
