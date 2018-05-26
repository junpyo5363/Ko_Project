#pragma once
#include "grid.h"
#include <iostream>
class Switch {
	Switch(float x, float y);
	bool Click(float x, float y);

private:
	float X;
	float Y;

};