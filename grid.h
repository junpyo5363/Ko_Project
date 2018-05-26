#pragma once

namespace MAP {//실제 게임에 사용되는 맵
	const unsigned int ROW = 152;
	const unsigned int COL = 152;
};
enum STATE { OFF, ING, ON };

class Grid {
public:
	Grid(int state, bool TF);
	Grid();
	void setState(char state);
	void setTF(bool TF);
	int getState(); 
	bool getTF();//true : ON, ING / false : OFF
private:
	int state;
	bool TF;
};