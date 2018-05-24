#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__
#include "player.h"

class Zombie : public Player {
public:
	Zombie();
	void move();
};

#endif
