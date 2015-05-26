#include "enemy.h"

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