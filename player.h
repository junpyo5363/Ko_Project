#pragma once
#include <iostream>
#include <GL/glut.h>
#include "grid.h"
#include <vector>

#define SIZE 1.0
enum DIRECTION { RIGHT, LEFT, DOWN, UP, STOP };//동서남북 순서

class Player {
public:
	Player(float x, float y, float r, float g, float b);
	Player();
	Player(float x, float y);
	void setPos(float x, float y);
	void setColor(float r, float g, float b);
	float getX();
	float getY();
	float getR();
	float getG();
	float getB();
	void draw() const;
protected:
	float* pos;
	float* color;
};