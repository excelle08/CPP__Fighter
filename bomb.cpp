#include "bomb.h"
#include "stage.h"

void Bomb::shoot(){
	{
		move(_velocity);
		//__stage__->drawOnce(*this);
		if(isOutOfWindow()){
			kill();
		}
	}
}