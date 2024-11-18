#pragma once
#include "Bullet.h"
#include "Vector2.h"

class Player {
public:
	Bullet* bullet_[32];
	Vector2 pos_;

	int radius_;
	int speed_;
	int bulletTime_ = 7;
	int playerTexture_;
	bool hitBox_ = true;

public:
	Player(Vector2 pos, int speed);
	~Player();
	void Update(char* keys, char* preKeys);
	void Draw();
};