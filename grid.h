#pragma once

namespace MAP {
	const unsigned int ROW = 52;
	const unsigned int COL = 52;
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