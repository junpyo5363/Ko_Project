#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__
#include "player.h"
#include "grid.h"

class Zombie : public Player {
public:
	Zombie();
	void move(std::vector<Grid**>& maps);
};

#endif
