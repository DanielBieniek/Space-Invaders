#pragma once
using namespace std;

//BOARD
class Board {
	int width;
	int height;
	Player player;
	vector<Enemy> enemies = {};
	vector<Projectile> projectiles = {};
public:
	Board(int w, int h) { //CONSTRUCTOR
		width = w;
		height = h;
	}
	/*
	int BoardHeight() {
		return height;
	}
	int BoardWidth() {
		return width;
	}
	*/
	void EveryFrame() {
		for (int i = 0; i < (int)projectiles.size(); i++) {
			projectiles[i].moveX(1); //move projectiles right every frame
		}
		draw(); //draw the board every frame
	}

	void EverySecond() {
		for (int i = 0; i < (int)enemies.size(); i++) {
			enemies[i].moveX(-1); //move enemies every second
		}
		spawnEnemy(rand() % height); //spawn new enemy
	}

	void spawnEnemy(int h) {
		Enemy e = Enemy(width - 1, h); //create new enemy
		enemies.push_back(e); //and push it to vector of enemies
	}
	void spawnProjectile() {
		Projectile p(player.locationX() + 1, player.locationY()); //create a projectile at player location
		projectiles.push_back(p);
	}

	void draw() {
		system("cls");
		cout << endl << "\t";
		for (int h = -1; h <= height; h++) {
			for (int w = -1; w <= width; w++) {
				if (w == -1 || w == width) {
					cout << "|"; //draw border
				}
				else {
					if (h == -1) {
						if (w == 1 && player.hearts() >= 1) cout << "o"; //draw lives
						else if (w == 2 && player.hearts() >= 2) cout << "o";
						else if (w == 3 && player.hearts() >= 3) cout << "o";
						else cout << "-"; //draw border
					}
					else if (h == height) {
						cout << "-"; //draw border
					}
					else {
						cout << drawEntity(w, h); //DRAW INSIDE THE BOARD
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
		for (int i = 0; i < (int)enemies.size(); i++) { //for all enemies
			if (w == enemies[i].locationX() && h == enemies[i].locationY()) {
				return '#'; //draw enemy
			}
		}
		//draw projectile
		for (int i = 0; i < (int)projectiles.size(); i++) { //for all projectiles
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