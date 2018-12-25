#pragma once
using namespace std;

//ENTITY
class Entity {
protected:
	int posX;
	int posY;
public:
	int locationX() {
		return posX;
	}
	int locationY() {
		return posY;
	}
	void moveX(int x) {
		posX += x;
	}
	void moveY(int y) {
		posY += y;
	}
};