#pragma once
using namespace std;

//PLAYER
class Player : public Entity {
	int lives = 3;
public:
	Player() : Entity(1, 3) {};
	int hearts() {
		return lives;
	}
	void hit() {
		lives--;
	}
};