#include "shuttle.h"
#include "config.h"
#include "bomb.h"

// TODO: Define custom functions

// Override Move method to implement border limit
void Shuttle::Move(float x, float y){
	sf::Vector2f curPos = getPosition();
	sf::Vector2u curSize = getObjSize();
	float curX = curPos.x;
	float curY = curPos.y;
	float sizeX = curSize.x;
	float sizeY = curSize.y;

	if((curX + x < 0) || (curY + y < 0)){
		return;
	}
	if((curX + sizeX + x > WINDOW_WIDTH) || (curY + sizeY + y > WINDOW_HEIGHT)){
		return;
	}
	move(x, y);
}

void Shuttle::placeAtBottom(){
	sf::Vector2u curSize = getObjSize();
	float x = WINDOW_WIDTH / 2 - curSize.x;
	float y = WINDOW_HEIGHT - curSize.y;
	Move(x, y);
}

void Shuttle::fire(sf::RenderWindow &window){
	Bomb bomb(*this);
	window.draw(bomb);
	bomb.shoot();
}