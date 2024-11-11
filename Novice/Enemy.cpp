#include "Novice.h"
#include "Enemy.h"

Enemy::Enemy(Vector2 pos, int radius, int speed, int isAlive) {
	pos_ = pos;
	radius_ = radius;
	speed_ = speed;
	isAlive_ = isAlive;
}

Enemy::~Enemy() {}

void Enemy::Update() {
	
}

void Enemy::Draw() { Novice::DrawEllipse((int)pos_.x, (int)pos_.y, radius_, radius_, 0.0f, RED, kFillModeSolid); }