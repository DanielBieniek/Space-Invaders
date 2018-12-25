#pragma once
using namespace std;

//ENEMY
class Enemy : public Entity {
public:
	Enemy(int x, int y) {
		posX = x;
		posY = y;
	}
};