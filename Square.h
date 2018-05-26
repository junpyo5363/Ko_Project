#pragma once
#include <GL/glut.h>

/* Define Square class */

class Square {
public:
	Square(float x, float y, float r, float g, float b, float h, float l);
	void draw(bool x);

private:
	float height;
	float length;
	float center_pos[2];
	float color[3];
};