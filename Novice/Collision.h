#pragma once
#include "Boss.h"
#include "Player.h"

class Collision {
public:
	Collision(Boss* boss, Player* player);
	void Update();

private:
	Boss* boss_;
	Player* player_;

	bool isCollision = false;
};