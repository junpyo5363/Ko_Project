#include "floodfill.h"

void FloodFill(std::vector<Grid**>& map, int n, User& user) {
	//Change all grid's TF
	FloodFill(map[n], user, 0, 0);
	//update the territory & reset all grid's TF into T
	for (int i = 0; i < MAP::ROW; ++i) {
		for (int j = 0; j < MAP::COL; ++j) {
			if (map[n][i][j].getTF() == true) {
				map[n][i][j].setState(STATE::ON);
				for (std::vector<Grid**>::size_type k = 0; k < map.size(); ++k) {
					if (k == n || map[k][i][j].getState() == STATE::ING) continue;
					map[k][i][j].setState(STATE::OFF);
				}
			}
			else map[n][i][j].setTF(true);
		}
	}
}
void FloodFill(Grid**& map, User& user, int row, int col) {
	//check the grid's state
	if (row >= MAP::ROW || col >= MAP::COL
		|| row < 0 || col < 0) return;
	if (map[row][col].getTF() == false) return;
	if (map[row][col].getState() != STATE::OFF) return;
	else map[row][col].setTF(false);

	if (row > 0) FloodFill(map, user, row - 1, col);
	if (row < MAP::ROW - 1) FloodFill(map, user, row + 1, col);
	if (col > 0) FloodFill(map, user, row, col - 1);
	if (col < MAP::COL - 1) FloodFill(map, user, row, col + 1);
}