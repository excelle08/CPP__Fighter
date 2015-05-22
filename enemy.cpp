#include "enemy.h"
#include "stage.h"

void Enemy::animate(){
	{
		move(_velocity);
		//__stage__->drawOnce(*this);
		if(isOutOfWindow()){
			kill();
		}
	}
}
