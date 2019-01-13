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
		if (player.hearts() <= 0) {
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
		system("cls");
		cout << endl << "\t";
		cout << "|-";
		for (int l = 3; l >= 1; l--) { //draw lives
			cout << (l <= player.hearts() ? 'o' : '-');
		}
		cout << "------------";
		if (points >= 999) cout << "999";				//
		else cout << setfill('0') << setw(3) << points; //draw points, if >=999, write 999
		cout << "-|";
		for (int h = 0; h < height; h++) {
			cout << endl << "\t" << "|";
			for (int w = 0; w < width; w++) {
				cout << drawEntity(w, h); //DRAW INSIDE THE BOARD
			}
			cout << "|";
			
		}
		cout << endl << "\t" << "|--------------------|" << endl;
	}

	char drawEntity(int w, int h) {
		//draw player
		if (h == player.locationY() && w == 1) {
			return '>'; //draw player
		}
		//draw enemies
		for (int i = 0; i < height; i++) { //for all rows
			if (i == h) {
				for (int j = 0; j < (int)enemies[i].size(); j++) { //for all enemies
					if (w == enemies[i][j].locationX()) {
						return '#'; //draw enemy
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

	/* OLD FUNCTIONS

	void drawOld() { //OLD DRAWING FUNCTION
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
	*/