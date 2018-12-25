#pragma once
using namespace std;

//PLAYER
class Player : public Entity {
	int lives = 3;
public:
	Player() {
		posX = 1;
		posY = 2;
	}
	int hearts() {
		return lives;
	}
};