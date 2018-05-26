#ifndef __FLOODFILL_H__
#define __FLOODFILL_H__
#include "grid.h"
#include "user.h"

void FloodFill(std::vector<Grid**>& map, int n, User& user);
void FloodFill(Grid**& map, User& user, int row, int col);

#endif
