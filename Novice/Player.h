#pragma once
#include "Bullet.h"
#include "Vector2.h"

class Player {
public:
	Player(Vector2 pos, float speed);
	~Player();
	void Update(char* keys, char* preKeys);
	void Draw();

public:
	Bullet* bullet_[32];
	Vector2 pos_;

	float speed_;
	int bulletTime_ = 10;
	int playerTexture_;
	bool hitBox_ = true;
};