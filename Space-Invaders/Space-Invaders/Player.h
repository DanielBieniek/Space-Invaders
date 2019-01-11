#pragma once
using namespace std;

//PLAYER
class Player : public Entity {
	int lives = 3;
public:
	Player() {
		posX = 1;
		posY = 3;
	}
	Player(int x, int y) {
		posX = x;
		posY = y;
	}
	int hearts() {
		return lives;
	}
	void hit() {
		lives--;
	}
};