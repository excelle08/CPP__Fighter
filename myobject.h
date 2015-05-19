#ifndef MYOBJECT_H
#define MYOBJECT_H

// This is an base class representing all objects to be painted.

#include <SFML/Graphics.hpp>

#ifndef IOSTREAM_INC
#define IOSTREAM_INC
#include <iostream>
#endif // IOSTREAM_INC

using namespace std;

class MyObject : public sf::Drawable, public sf::Transformable {
public:
	MyObject(string textureFilePath, sf::Vector2f objPosition);
	~MyObject(){

	}
	// Move functions requires RELATIVE displacement value.
	virtual void Move(float x, float y){
		move(x, y);
	}
	sf::Vector2u getObjSize(){
		return m_texture.getSize();
	}
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::Texture m_vertices;
};

#endif // MYOBJECT_H
