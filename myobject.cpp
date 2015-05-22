#include "myobject.h"
#include "stage.h"

MyObject::MyObject(string textureFilePath, sf::Vector2f objPosition, string type, bool bindKeyboardEvent){
	if(!m_texture.loadFromFile(textureFilePath)){
		cout << "Error loading texture file: " << textureFilePath << endl;
		exit(1);
	}
	setTexture(m_texture);
	setPosition(sf::Vector2f(0,0));
	move(objPosition);
	__type__ = type;
	listenKeyEvent = bindKeyboardEvent;
	isAlive = true;
	m_position = objPosition;
}

/*
void MyObject::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_sprite, states);
}
*/

bool MyObject::isOutOfWindow(){
	if(getPosition().x < 0 || getPosition().x + getObjSize().x > __stage__->getWindowSize().x || 
		getPosition().y < 0 || getPosition().y + getObjSize().y > __stage__->getWindowSize().y ){
		return true;
	}
	return false;
}