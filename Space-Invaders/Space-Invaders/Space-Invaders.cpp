#include "stdafx.h"
#include <iostream> 
#include <vector>
#include <cstdlib> //srand, rand
#include <ctime> //time for rand
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

//PROJECTILE
class Projectile : public Entity {
public:
	Projectile(int x, int y) {
		posX = x;
		posY = y;
	}
};

//ENEMY
class Enemy : public Entity {
public:
	Enemy(int x, int y) {
		posX = x;
		posY = y;
	}
};

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

//BOARD
class Board {
	int width;
	int height;
	int EnemyCount;
	Player player;
	vector<Enemy> enemies = {};
	vector<Projectile> projectiles = {};
public:
	Board(int w, int h) {
		width = w;
		height = h;
	}
	void spawnEnemy(int h) {
		Enemy e(width-1,h);
		enemies.push_back(e);
	}
	void spawnProjectile() {
		Projectile p(player.locationX()+1, player.locationY()); //create a projectile at player location
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
	void spawnEnemiesTEMPORARY() {
		Enemy e1(15, 4);
		Enemy e2(16, 0);
		Enemy e3(18, 2);
		Enemy e4(19, 1);
		enemies.push_back(e1);
		enemies.push_back(e2);
		enemies.push_back(e3);
		enemies.push_back(e4);
	}
	void spawnProjectilesTEMPORARY() {
		Projectile p1(4, 2);
		Projectile p2(11, 3);
		projectiles.push_back(p1);
		projectiles.push_back(p2);
	}
};

int main()
{
	Board board(20,7);
	srand(time(NULL));

	//GAME LOOP;
	//board.spawnEnemy(rand() % 7); //randomize the spawn location between 0 and 7.
	board.spawnEnemiesTEMPORARY();
	//board.spawnProjectile();
	board.spawnProjectilesTEMPORARY();
	cout << "GENERATED";
	board.draw();

	cout << "HARD CODED";
	cout << endl;
	cout << "\t|-ooo----------------|" << endl;
	cout << "\t|                #   |" << endl;
	cout << "\t|                   #|" << endl;
	cout << "\t| >  -             # |" << endl;
	cout << "\t|           -        |" << endl;
	cout << "\t|               #    |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|--------------------|" << endl;
	cout << endl;
    return 0;
}