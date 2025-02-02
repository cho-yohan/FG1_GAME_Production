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

	float spriteWidth = 76;
	float spriteHeight = 60;
	float radius = 25;
	float hitBoxX;  // プレイヤーの中心X
	float hitBoxY; // プレイヤーの中心Y

	bool isAlive = true;
	bool life_1 = true;
	bool life_2 = true;
	bool life_3 = true;

	int life[3];
	Vector2 lifePos[3] = { 620, 1020, 670, 1020, 720, 1020 };
};