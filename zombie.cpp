#include "zombie.h"
#include "grid.h"
Zombie::Zombie() : Player(rand() % 50, rand() % 50, 0.0f, 1.0f, 0.0f) {}

void Zombie::move() {
	int direction = rand() % 4;
	if (direction == DIRECTION::LEFT) {
		if (getX() < MAP::ROW - 2) this->setPos(this->getX() + 1, this->getY());
		else direction = DIRECTION::RIGHT;
	}
	else if (direction == DIRECTION::RIGHT) {
		if (getX() > 1) this->setPos(this->getX() - 1, this->getY());
		else this->setPos(this->getX() + 1, this->getY());
	}
	else if (direction == DIRECTION::DOWN) {
		if (getY() > 1) this->setPos(this->getX(), this->getY() - 1);
		else direction = DIRECTION::UP;
	}
	else {
		if (getY() < MAP::COL - 2)	this->setPos(this->getX(), this->getY() + 1);
		else this->setPos(this->getX(), this->getY() - 1);
	}
}