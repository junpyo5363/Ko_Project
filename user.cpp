#include "user.h"

User::User() : Player(), Keys(new Key[4]), ismaking(false)
	, territorycolor(new float[3]) {
	setKey(DIRECTION::RIGHT, GLUT_KEY_RIGHT, true);
	setKey(DIRECTION::LEFT, GLUT_KEY_LEFT, true);
	setKey(DIRECTION::DOWN, GLUT_KEY_DOWN, true);
	setKey(DIRECTION::UP, GLUT_KEY_UP, true);
}
User::User(float x, float y)
	: Player(x, y), Keys(new Key[4]), ismaking(false)
	, territorycolor(new float[3]) {
	setKey(DIRECTION::RIGHT, GLUT_KEY_RIGHT, true);
	setKey(DIRECTION::LEFT, GLUT_KEY_LEFT, true);
	setKey(DIRECTION::DOWN, GLUT_KEY_DOWN, true);
	setKey(DIRECTION::UP, GLUT_KEY_UP, true);
}
User::User(float x, float y, float r, float g, float b)
	: Player(x, y, r, g, b), Keys(new Key[4]), ismaking(false)
	, territorycolor(new float[3]) {
	setKey(DIRECTION::RIGHT, GLUT_KEY_RIGHT, true);
	setKey(DIRECTION::LEFT, GLUT_KEY_LEFT, true);
	setKey(DIRECTION::DOWN, GLUT_KEY_DOWN, true);
	setKey(DIRECTION::UP, GLUT_KEY_UP, true);
}
void User::setKey(int dir, char key, bool isSpecial) {
	Keys[dir].key = key;
	Keys[dir].isSpecialKey = isSpecial;
}
User::Key User::getRight() { return Keys[DIRECTION::RIGHT]; }
User::Key User::getLeft() { return Keys[DIRECTION::LEFT]; }
User::Key User::getDown() { return Keys[DIRECTION::DOWN]; }
User::Key User::getUp() { return Keys[DIRECTION::UP]; }

User::Key User::operator[](int dir) { return Keys[dir]; }
void User::setDirection(int dir) { Direction = dir; }
int User::getDirection() { return Direction; }

bool User::getIsmaking() {
	return ismaking;
}
void User::setIsmaking(bool TF) {
	ismaking = TF;
}
void User::setTerritorycolor(float r, float g, float b) {
	territorycolor[0] = r;
	territorycolor[1] = g;
	territorycolor[2] = b;
}
float User::getTR() { return territorycolor[0]; }
float User::getTG() { return territorycolor[1]; }
float User::getTB() { return territorycolor[2]; }