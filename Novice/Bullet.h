#pragma once
#include "Enemy.h"
#include "Vector2.h"

class Bullet {
public:
	Bullet(Vector2 pos, int speed, int isShot, int direction);
	void Update();
	void Draw();

public:
	Vector2 pos_;
	Vector2 hitSize_{5, 22};

	int speed_;
	int radius_;
	int isShot_ = false;
	int bulletTexture_;
	bool hitBox_ = true;

	int direction_; // 追加: 1で右、-1で左、0で無効
};