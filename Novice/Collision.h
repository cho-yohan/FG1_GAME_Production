#pragma once
#include "Boss.h"
#include "Bullet.h"

class Collision {
public:
	Collision(Boss* boss, Bullet* bullets);
	void Update();

private:
	Boss* boss_;
	Bullet* bullets_;
};