#include "bomb.h"

void Bomb::shoot(float speed){
	for(int i=0; i<=100; i++){
		Move(0, -speed);
	}
}