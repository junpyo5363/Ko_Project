#ifndef __USER_H__
#define __USER_H__
#include "player.h"

class User : public Player {
private:
	class Key {
	public:
		bool isSpecialKey;
		char key;
	};
public:
	User();
	User(float x, float y);
	User(float x, float y, float r, float g, float b);
	void setKey(int dir, char key, bool isSpecial);
	Key operator[](int dir);
	Key getRight();
	Key getLeft();
	Key getDown();
	Key getUp();
	void setDirection(int dir);
	int getDirection();
	bool getIsmaking();
	void setIsmaking(bool TF);
	void setTerritorycolor(float r, float g, float b);
	float getTR();
	float getTG();
	float getTB();
private:
	Key* Keys;
	int Direction = DIRECTION::STOP;
	bool ismaking;
	float* territorycolor;
};

#endif