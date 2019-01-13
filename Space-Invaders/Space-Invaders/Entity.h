#pragma once
using namespace std;

//ENTITY
class Entity {
protected:
	int posX;
	int posY;
public:
	Entity(int x, int y) {
		posX = x;
		posY = y;
	}
	int locationX() {
		return posX;
	}
	int locationY() {
		return posY;
	}
	void moveY(int y) {
		posY += y;
	}
	virtual void moveX() {} //Polymorphism, for projectile add 1 to x coordinate, for enemy add -1 to x coordinate.
};