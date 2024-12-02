#include "BossBullet.h"
#include <Novice.h>
#include <math.h>

BossBullet::BossBullet(Vector2 pos, int speed, float angle) 
	: pos_(pos), speed_(speed), angle_(angle) {
	bulletTexture_ = Novice::LoadTexture("./Resources/Boss/bossBullet.png");
}

void BossBullet::Update() {
	// 弾丸の位置を更新（進行方向に基づいて）
	pos_.x += speed_ * cosf(angle_); // X軸方向の移動
	pos_.y += speed_ * sinf(angle_); // Y軸方向の移動
}

void BossBullet::Draw() { 
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, bulletTexture_, 1, 1, 0.0f, 0xffffffff); 

	// ヒットボックスを描画
	if (hitBox_) {
		float spriteWidth = 90;  // スプライトの幅（適宜変更）
		float spriteHeight = 90; // スプライトの高さ（適宜変更）

		float hitBoxX = pos_.x + spriteWidth / 2;  // プレイヤーの中心X
		float hitBoxY = pos_.y + spriteHeight / 2; // プレイヤーの中心Y

		// ヒットボックスの半径を設定（ここでは楕円形）
		float hitBoxRadiusX = spriteWidth * 0.5f;  // スプライト幅の半分をx方向半径に
		float hitBoxRadiusY = spriteHeight * 0.5f; // スプライト高さの1.5倍をy方向半径に（y方向を長く）

		// 楕円形のヒットボックスを描画
		Novice::DrawEllipse((int)hitBoxX, (int)hitBoxY, (int)hitBoxRadiusX, (int)hitBoxRadiusY, 0.0f, WHITE, kFillModeWireFrame);
	}
}
