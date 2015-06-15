#include "super.h"
#include "bomb.h"
#include "config.h"
#include "stage.h"

void Super::animate() {
	move(_velocity);
	// Randomly output bombs
	int ran_var = std::rand();
	if(ran_var % 5 == 0){
		Bomb b(*this, getVelocityVect(getPosition(), __stage__->getHeroPos(), __stage__->getBombSpeed()*1.5), TextureLib::bomb_enemy);
		__stage__->addBomb(b);
	}
	if(life <= 20 && life > 16){
		setTexture(txt);
	} else if(life <= 16 && life >= 10){
		setTexture(txtDamage1);
	} else if (life < 10 && life >= 3){
		setTexture(txtDamage2);
	} else if (life < 3){
		setTexture(txtDamage3);
	}
	if(isOutOfWindow()){
		isAlive = false;
	}
}

void Super::kill(bool isBoom){
	life --;
	if(life <= 0){
		isAlive = false;
		isBoomed = true;
	}
}