#pragma once
using namespace std;

//BOARD
class Board {
	int width = 20;
	int height = 7;
	Player player;
	deque<Enemy> enemies = {};
	deque<Projectile> projectiles = {};
public:
	Board() {} //DEFAULT CONSTRUCTOR
	bool gameLoop = true; //used to be able to stop the game if the player lost all lives

	//OUTPUT BOARD DIMENSIONS
	int BoardHeight() {
		return height;
	}
	int BoardWidth() {
		return width;
	}

	//MOVE ENTITIES
	void moveEnemies() {
		for (int i = 0; i < (int)enemies.size(); i++) {
			try {
				if (enemies[i].locationX() - 1 <= player.locationX()) throw 1;
				enemies[i].moveX(); //move enemies
			}
			catch (int e) {
				player.hit();
				enemies.pop_front();
			}
		}
	}

	void movePlayer(int d) {
		try {
			if (player.locationY() + d < 0 || player.locationY() + d >= height) throw 1;
			player.moveY(d); //move a player
		}
		catch (int e) {} //if cant move there, dont do anything
		
	}

	void moveProjectiles() {
		for (int i = 0; i < (int)projectiles.size(); i++) {
			try {
				if (projectiles[i].locationX() + 1 > width) throw 1;
				projectiles[i].moveX(); //move projectiles
			}
			catch (int e) {
				projectiles.pop_front();
			}
			
		}
	}

	//SPAWN ENTITIES
	void spawnEnemy(int h) {
		Enemy e = Enemy(width - 1, h); //create new enemy
		enemies.push_back(e); //and push it to vector of enemies
	}
	void spawnProjectile() {
		Projectile p(player.locationX() + 1, player.locationY()); //create a projectile at player location
		projectiles.push_back(p);
	}

	//DRAW THE BOARD
	void draw() {
		system("cls");
		cout << endl << "\t";
		cout << "|-";
		for (int l = 3; l >= 1; l--) { //draw the amount of lives the player has
			cout << (l <= player.hearts() ? 'o' : '-');
		}
		cout << "----------------|";
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
		for (int i = 0; i < (int)enemies.size(); i++) { //for all enemies
			if (h == enemies[i].locationY() && w == enemies[i].locationX()) {
				return '#'; //draw enemy
			}
		}
		//draw projectile
		for (int i = 0; i < (int)projectiles.size(); i++) { //for all projectiles
			if (h == projectiles[i].locationY() && w == projectiles[i].locationX()) {
				return '-'; //draw projectiles
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