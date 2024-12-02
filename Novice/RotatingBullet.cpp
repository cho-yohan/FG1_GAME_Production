#include "RotatingBullet.h"
#include <Novice.h>
#include <math.h>

RotatingBullet::RotatingBullet(Vector2 pos, Vector2 direction, float speed, float rotationSpeed)
    : pos_(pos), direction_(direction), speed_(speed), rotationSpeed_(rotationSpeed), rotationAngle_(0.0f) {
	bulletTexture_ = Novice::LoadTexture("./Resources/Boss/bossBullet2.png"); // 弾のスプライト画像
}

void RotatingBullet::Update() {
	// 弾の位置を更新（進行方向に速度分移動）
	pos_.x += direction_.x * speed_;
	pos_.y += direction_.y * speed_;

	// 弾が回転する処理（時計回り）
	rotationAngle_ -= rotationSpeed_; // 時計回りなので減算

	// 回転後の進行方向を計算
	direction_.x = cosf(rotationAngle_);
	direction_.y = sinf(rotationAngle_);
}

void RotatingBullet::Draw() {
	// 弾を描画
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, bulletTexture_, 1, 1, rotationAngle_, 0xffffffff);
}