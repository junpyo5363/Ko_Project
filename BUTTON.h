#pragma once
#include "grid.h"
/* Define Shape class */
class BUTTON{
public:
	BUTTON(float x, float y) {
		center_pos[0] = x;
		center_pos[1] = y;

	}
	bool check(float x, float y) {
		float a = (center_pos[0] < x) ? x - center_pos[0] : center_pos[0] - x;
		float b = (center_pos[1] < y) ? y - center_pos[1] : center_pos[1] - y;
		if ((a < (MAP::COL*0.05))&&(b < (MAP::COL*0.05))) return 1;
		return 0;
	}


protected:
	float center_pos[2];
	};