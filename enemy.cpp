#include "enemy.h"
#include <sstream>

void Enemy::animate(){
	{
		move(_velocity);
		if(isExplosion()){
			playBoomEffect();
		}
		if(isOutOfWindow()){
			kill();
		}
	}
}

void Enemy::playBoomEffect(){
	sf::Music boom;
    if(!boom.openFromFile("resources/audios/bang.ogg")){
        std::cout<<"Warning: Error opening sound effect file"<<std::endl;
    }
    boom.play();
}

bool Enemy::playExplodeAnimate(){
	using namespace std;
	stringstream fn;
	string filename;
	fn << "resources/images/explosion/";
	fn << "explosion_" << 17 - ttl/2 << ".png";
	//std::cout << fn.str() << endl;;
	filename = fn.str();
	if (ttl <= 0){
		return false;
	} else {
		m_texture.loadFromFile(filename);
		setTexture(m_texture);
		ttl --;
		return true;
	}
}