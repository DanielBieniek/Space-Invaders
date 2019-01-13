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
	virtual void moveX() {} //Polymorphism, for Projectile add 1 to X coordinate, for Enemy subtract 1 from X coordinate.
};