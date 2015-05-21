#include "bomb.h"
#include "stage.h"

void Bomb::thisMove(float x, float y){
	move(x, y);
	pos_Y += y;
	pos_X += x;
}

void Bomb::shoot(float speed){
	thisMove(0, -speed);
	__stage__->drawOnce(this);
	std::cout<<pos_Y<<std::endl;
}