#include "Bullet.h"
#include <Novice.h>

Bullet::Bullet(Vector2 pos, int speed, int isShot, int direction) {
	pos_ = pos;
	speed_ = speed;
	isShot_ = isShot;
	direction_ = direction;

	bulletTexture_ = Novice::LoadTexture("./Resources/Player/bullet.png");
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
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, bulletTexture_, 1, 1, 0.0f, WHITE);
		
		// ヒットボックスを描画
		if (hitBox_) {
			float spriteWidth = 30;  // スプライトの幅（適宜変更）
			float spriteHeight = 30; // スプライトの高さ（適宜変更）

			float hitBoxX = pos_.x + spriteWidth / 2 + 2;  // プレイヤーの中心X
			float hitBoxY = pos_.y + spriteHeight / 2 - 5; // プレイヤーの中心Y

			// ヒットボックスの半径を設定（ここでは楕円形）
			float hitBoxRadiusX = spriteWidth * 0.2f;  // スプライト幅の半分をx方向半径に
			float hitBoxRadiusY = spriteHeight * 0.3f; // スプライト高さの1.5倍をy方向半径に（y方向を長く）

			// 楕円形のヒットボックスを描画
			Novice::DrawEllipse((int)hitBoxX, (int)hitBoxY, (int)hitBoxRadiusX, (int)hitBoxRadiusY, 0.0f, WHITE, kFillModeWireFrame);
		}
	}
}