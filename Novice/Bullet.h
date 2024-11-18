#pragma once
#include "Enemy.h"
#include "Vector2.h"

class Bullet {
public:
	int speed_;
	int radius_;
	int isShot_ = false;
	int bulletTexture_;
	bool hitBox_ = true;

	Vector2 pos_;
	Vector2 hitSize_{5, 22};

public:
	Bullet(Vector2 pos, int speed, int isShot);
	void Update();
	void Draw();
};