#include "Enemy.h"
#include <Novice.h>

Enemy::Enemy(Vector2 pos, int s, int r, int isAlive) {
	pos_ = pos;
	radius_ = r;
	speed_ = s;
	isAlive_ = isAlive;
}

void Enemy::Update() {
	pos_.x += speed_;

	if (pos_.x - radius_ <= 50 || pos_.x + radius_ >= 980) {
		speed_ *= -1;
	}
}

void Enemy::Draw() {
}