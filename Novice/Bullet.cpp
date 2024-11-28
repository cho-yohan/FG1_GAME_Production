#include "Bullet.h"
#include <Novice.h>

Bullet::Bullet(Vector2 pos, int speed, int isShot, int direction) {
	pos_ = pos;
	speed_ = speed;
	isShot_ = isShot;
	direction_ = direction;

	bulletTexture_ = Novice::LoadTexture("./Resources/Player/bullet-copy.png");
}

void Bullet::Update() {
	if (isShot_) {
		// directionに基づいて弾が発射される方向を決定
		pos_.x += direction_ * speed_; // 左右に移動
		pos_.y -= speed_;              // 上方向に移動

		if (pos_.y <= 0) {
			isShot_ = false;
		}
	}
}

void Bullet::Draw() {
	if (isShot_) {
		Novice::DrawSprite((int)pos_.x + 30, (int)pos_.y, bulletTexture_, 1, 1, 0.0f, WHITE);
		if (hitBox_ == false) {
			Novice::DrawBox((int)pos_.x, (int)pos_.y, (int)hitSize_.x, (int)hitSize_.y, 0.0f, WHITE, kFillModeWireFrame);
		}
	}
}