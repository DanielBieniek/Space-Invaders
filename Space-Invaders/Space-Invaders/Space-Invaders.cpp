#include "stdafx.h"
#include <iostream>
#include <vector>
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
};

//PROJECTILE
class Projectile : public Entity {
public:
	Projectile(int y) {
		posX = 5;
		posY = y;
	}
};

//ENEMY
class Enemy : public Entity {
public:
	Enemy(int y) {
		posX = 18;
		posY = y;
	}
};

//PLAYER
class Player : public Entity {
	int lives = 2;
public:
	Player() {
		posX = 1;
		posY = 3;
	}
	int hearts() {
		return lives;
	}
};

//BOARD
class Board {
	int width = 20;
	int height = 7;
	int EnemyCount;
	Player player;
	vector<Enemy> enemies = {};
	vector<Projectile> projectiles = {};
public:
	void spawnEnemy(int h) {
		Enemy e(h);
		enemies.push_back(e);
	}
	void spawnProjectile() {
		Projectile p( player.locationY() ); //create a projectile at player location
		projectiles.push_back(p);
	}
	void draw() {
		cout << endl << "\t";
		for (int h = -1; h <= height; h++) {
			for (int w = -1; w <= width; w++) {
				if (w == -1 || w == width) {
					cout << "|"; //draw border
				} else {
					if (h == -1) {
						if (w == 1 && player.hearts() >= 1) cout << "o"; //draw lives
						else if (w == 2 && player.hearts() >= 2) cout << "o";
						else if (w == 3 && player.hearts() >= 3) cout << "o";
						else cout << "-"; //draw border
					} else if (h == height) {
							cout << "-"; //draw border
					} else {
						cout << drawEntity(w,h); //DRAW INSIDE THE BOARD
					}
				}
			}
			cout << endl << "\t";
		}
		cout << endl;
	}
	char drawEntity(int w, int h) {
		//draw player
		if (w == 1 && h == player.locationY()) {
			return '>';
			
		}
		//draw enemies
		for (int i = 0; i < enemies.size(); i++) { //for all enemies
			if (w == enemies[i].locationX() && h == enemies[i].locationY()) {
				return '#'; //draw enemy
			}
		}
		//draw projectile
		for (int i = 0; i < projectiles.size(); i++) { //for all projectiles
			if (w == projectiles[i].locationX() && h == projectiles[i].locationY()) {
				return '-'; //draw projectiles
			}
		}

		//draw empty space
		return ' ';
	}
};

int main()
{
	Board board;

	//GAME LOOP
	board.spawnEnemy(5);
	board.spawnProjectile();
	board.draw();

	/*cout << endl;
	cout << "\t|-ooo----------------|" << endl;
	cout << "\t|                #   |" << endl;
	cout << "\t|                   #|" << endl;
	cout << "\t| >  -             # |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|               #    |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|--------------------|" << endl;
	cout << endl;*/
    return 0;
}