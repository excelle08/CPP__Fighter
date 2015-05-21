#include "myobject.h"

MyObject::MyObject(string textureFilePath, sf::Vector2f objPosition, string type, bool bindKeyboardEvent){
	if(!m_texture.loadFromFile(textureFilePath)){
		cout << "Error loading texture file: " << textureFilePath << endl;
		exit(1);
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(objPosition);
	__type__ = type;
	listenKeyEvent = bindKeyboardEvent;
}

void MyObject::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_sprite, states);
}