#pragma 
using namespace std;

//PROJECTILE
class Projectile : public Entity {
public:
	Projectile(int x, int y) : Entity(x, y) {};
	void moveX() {
		posX++;
	}
};