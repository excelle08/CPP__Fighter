#include "super.h"

void Super::animate(){
	{
		move(_velocity);
		if(isOutOfWindow()){
			isAlive = false;
		}
	}
}

void Super::kill(bool isBoom){
	life --;
	if(life <= 16 && life >= 10){
		setTexture(txtDamage1);
	} else if (life < 10 && life >= 3){
		setTexture(txtDamage2);
	} else if (life < 3){
		setTexture(txtDamage3);
	}
	if(life <= 0){
		isAlive = false;
	}
}