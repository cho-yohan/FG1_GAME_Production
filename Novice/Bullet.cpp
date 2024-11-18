#include "Bullet.h"
#include <Novice.h>

Bullet::Bullet(Vector2 pos, int speed, int isShot) {
	pos_ = pos;
	speed_ = speed;
	isShot_ = isShot;

	bulletTexture_ = Novice::LoadTexture("./Resources/Player/bullet.png");
}

void Bullet::Update() {
	if (isShot_) {
		pos_.y -= speed_;

		if (pos_.y <= 0) {
			isShot_ = false;
		}
	}
}

void Bullet::Draw() {
	if (isShot_) {
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, bulletTexture_, 1, 1, 0.0f, WHITE);
		if (hitBox_ == false) {
			Novice::DrawBox((int)pos_.x, (int)pos_.y, (int)hitSize_.x, (int)hitSize_.y, 0.0f, WHITE, kFillModeWireFrame);
		}
	}
}