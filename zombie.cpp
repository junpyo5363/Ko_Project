#include "zombie.h"
Zombie::Zombie() : Player(rand() % (MAP::ROW - 2) + 1, rand() % (MAP::COL - 2) + 1, 0.0f, 1.0f, 0.0f) {}

void Zombie::move(std::vector<Grid**>& maps) {
	int direction = rand() % 4;
	int x = static_cast<int>(getX()); int y = static_cast<int>(getY());
	bool canmove = true;
	if (direction == DIRECTION::RIGHT) {
		for (std::vector<Grid**>::size_type i = 0; i < maps.size(); ++i) {
			if (maps[i][x + 1][y].getState() == STATE::ON || (x >= MAP::ROW - 2)) {
				canmove = false;	break;
			}
		}
		if (canmove) this->setPos(this->getX() + 1, this->getY());
	}
	else if (direction == DIRECTION::LEFT) {
		for (std::vector<Grid**>::size_type i = 0; i < maps.size(); ++i) {
			if (maps[i][x - 1][y].getState() == STATE::ON || x <= 1) {
				canmove = false; break;
			}
		}
		if (canmove)	 this->setPos(this->getX() - 1, this->getY());
	}
	else if (direction == DIRECTION::DOWN) {
		for (std::vector<Grid**>::size_type i = 0; i < maps.size(); ++i) {
			if (maps[i][x][y - 1].getState() == STATE::ON || y <= 1) {
				canmove = false; break;
			}
		}
		if (canmove) this->setPos(this->getX(), this->getY() - 1);
	}
	else if (direction == DIRECTION::UP) {
		for (std::vector<Grid**>::size_type i = 0; i < maps.size(); ++i) {
			if (maps[i][x][y + 1].getState() == STATE::ON || y >= MAP::COL - 2) {
				canmove = false; break;
			}
		}
		if (canmove) this->setPos(this->getX(), this->getY() + 1);
	}
}