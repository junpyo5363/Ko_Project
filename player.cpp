#include "player.h"
Player::Player(float x, float y, float r, float g, float b) {
	pos = new float[2];
	pos[0] = x;
	pos[1] = y;
	color = new float[3];
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

Player::Player(float x, float y) {
	pos = new float[2];
	pos[0] = x;
	pos[1] = y;
	color = new float[3];
	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
}
Player::Player() {
	pos = new float[2];
	pos[0] = 1;
	pos[1] = 1;
	color = new float[3];
	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
}

void Player::draw() const {
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex2f(pos[0], pos[1]);
	glVertex2f(pos[0] + SIZE, pos[1]);
	glVertex2f(pos[0] + SIZE, pos[1] + SIZE);
	glVertex2f(pos[0], pos[1] + SIZE);
	glEnd();
}

void Player::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Player::setPos(float x, float y) {
	pos[0] = x;
	pos[1] = y;
}

float Player::getX() { return pos[0]; }
float Player::getY() { return pos[1]; }
float Player::getR() { return color[0]; }
float Player::getG() { return color[1]; }
float Player::getB() { return color[2]; }
