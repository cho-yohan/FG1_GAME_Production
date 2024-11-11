#pragma once
#include "Vector2.h"

class Enemy {
public:
	Vector2 pos_;
	int radius_;
	int speed_;
	int isAlive_;

public:
	Enemy(Vector2 pos, int radius, int speed, int isAlive);
	~Enemy();
	void Update();
	void Draw();
};