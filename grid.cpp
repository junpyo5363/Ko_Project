#include "grid.h"


Grid::Grid(int state, bool TF) {
	this->state = state;
	this->TF = TF;
}
Grid::Grid() {
	state = STATE::OFF;
	TF = true;
}

void Grid::setState(char state) {
	this->state = state;
}

void Grid::setTF(bool TF) {
	this->TF = TF;

}

int Grid::getState() { return state; }
bool Grid::getTF() { return TF; }