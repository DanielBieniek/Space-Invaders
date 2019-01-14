#pragma once

#define WIDTH 20
#define HEIGHT 7

using namespace std;

//BOARD
class Board {
	int width = WIDTH;
	int height = HEIGHT;
	int points = 0;
	Player player;
	deque<Enemy> enemies[HEIGHT];
	deque<Projectile> projectiles[HEIGHT];
public:
	Board() {} //DEFAULT CONSTRUCTOR
	bool gameLoop = true; //used to be able to stop the game if the player lost all lives

	//OUTPUT INFO
	int BoardHeight() {
		return height;
	}
	int getPoints() {
		return points;
	}

	//SPAWN ENTITIES
	void spawnEnemy(int h) {
		Enemy e = Enemy(width - 1, h); //create new enemy
		enemies[h].push_back(e); //and push it to a deque of enemies
	}
	void spawnProjectile() {
		Projectile p(player.locationX() + 1, player.locationY()); //create a projectile at player location
		projectiles[player.locationY()].push_back(p); //and push it to a deque of projectiles
	}

	//MOVE ENTITIES
	void moveEnemies() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < (int)enemies[i].size(); j++) {
				try {
					if (enemies[i][j].locationX() - 1 <= player.locationX()) throw 1; //if enemy reaches the player
					enemies[i][j].moveX(); //move enemies
				}
				catch (int e) {
					player.hit(); //decrease the amount of lives the player has
					checkPlayerLives(); //check whether the player lost all lives 
					enemies[i].pop_front(); //delete the enemy if it reached the player
				}
			}
		}
	}

	void movePlayer(int d) {
		try {
			if (player.locationY() + d < 0 || player.locationY() + d >= height) throw 1; //check if player is still on the board
			player.moveY(d); //move a player
		}
		catch (int e) {} //if can't move there, dont do anything
	}

	void moveProjectiles() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < (int)projectiles[i].size(); j++) {
				try {
					if (projectiles[i][j].locationX() + 1 > width) throw 1;
					projectiles[i][j].moveX(); //move projectiles
				}
				catch (int e) {
					projectiles[i].pop_front();
				}
			}
		}
	}

	//CHECK GAME STATES
	void checkPlayerLives() {
		if (player.hearts() < 0) {
			gameLoop = false;
		}
	}

	void checkProjectiles() {
		for (int i = 0; i < height; i++) { //for all rows
			if (!projectiles[i].empty() && !enemies[i].empty()) {
				if (projectiles[i].front().locationX() >= enemies[i].front().locationX()) { //if projectile is on an enemy (or behind to fix a bug where a projectile would fly past an enemy)
					projectiles[i].pop_front();
					enemies[i].pop_front();
					points++;
				}
			}
		}
	}

	//DRAW THE BOARD
	void draw() {
		COORD coord; //used for SetConsoleCursorPosition
		coord.X = 0;
		coord.Y = 0;
		//reset the position of a console cursor to the begining instead of clearing the console every time.
		//fixed flickering of the board
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
		cout << endl << "\t" << char(201) << char(205) << char(185) << char(3);
		if (player.hearts() >= 9) cout << "9";		//
		else if (player.hearts() < 0) cout << "0";	// write number of lives (9 if >9, or 0 if <0)
		else cout << player.hearts();				//
		cout << char(204);
		for (int i = 0; i < 8; i++) cout << char(205);
		cout << char(185) <<  '$';
		if (points >= 999) cout << "999";				//
		else cout << setfill('0') << setw(3) << points; //draw points, if >=999, write 999
		cout << char(204) << char(205) << char(187);
		for (int h = 0; h < height; h++) {
			cout << endl << "\t" << char(186);
			for (int w = 0; w < width; w++) {
				cout << drawEntity(w, h); //DRAW INSIDE THE BOARD
			}
			cout << char(186);
			
		}
		cout << endl << "\t" << char(200);
		for (int i = 0; i<20; i++) cout << char(205);
		cout << char(188) << endl;
	}

	char drawEntity(int w, int h) {
		//draw player
		if (h == player.locationY() && w == 1) {
			return char(16); //draw player
		}
		//draw enemies
		for (int i = 0; i < height; i++) { //for all rows
			if (i == h) {
				for (int j = 0; j < (int)enemies[i].size(); j++) { //for all enemies
					if (w == enemies[i][j].locationX()) {
						return char(4); //draw enemy
					}
				}
			}
		}
		//draw projectile
		for (int i = 0; i < height; i++) { //for all rows
			if (i == h) {
				for (int j = 0; j < (int)projectiles[i].size(); j++) { //for all projectiles
					if (w == projectiles[i][j].locationX()) {
						return '-'; //draw projectiles
					}
				}
			}
		}
		return ' '; //draw empty space
	}
};