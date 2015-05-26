#include "bomb.h"

void Bomb::shoot(){
	{
		move(_velocity);
		if(isOutOfWindow()){
			kill();
		}
	}
}