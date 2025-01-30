#pragma once
#include "Boss.h"
#include "Bullet.h"

class Collision {
public:
	Collision(Boss* boss, std::vector<Bullet>* bullets);
	void Update();

private:
	Boss* boss_;
	std::vector<Bullet>* bullets_;
};