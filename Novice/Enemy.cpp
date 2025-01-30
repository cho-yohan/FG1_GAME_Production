#include "Enemy.h"
#include <Novice.h>
#include <cmath>

Enemy::Enemy(Vector2 pos, float speed) 
	: pos_(pos), speed_(speed), isAlive_(true) { 
	enemyTexture = Novice::LoadTexture("./Resources/Boss/enemy.png"); 
}

void Enemy::Kill() {
	isAlive_ = false; // 敵を倒す
}

bool Enemy::CheckCollisionWithBullet(const Bullet& bullet) {
	float dx = bullet.pos_.x - pos_.x;
	float dy = bullet.pos_.y - pos_.y;
	float distance = std::sqrt(dx * dx + dy * dy);
	float combinedRadius = bullet.radius_ + hitBoxRadiusX_; // 弾と敵の半径の合成

	// 衝突判定: 弾と敵の距離が半径の合成よりも小さい場合に衝突と判断
	if (distance < combinedRadius) {
		return true; // 衝突
	}
	return false; // 衝突しない
}

void Enemy::StartFalling() { isFalling_ = true; }

void Enemy::Update() {

	if (isAlive_) {
		// 敵の移動処理（仮で下に移動）
		pos_.y += speed_;

		if (!isFalling_) {
			fallTimer_ += 1.0f; // ここではフレームごとに1秒を足していく（60FPSで進むと仮定）
			if (fallTimer_ >= fallDuration_) {
				StartFalling(); // 5秒後に降り始める
			}
		}

		if (isFalling_) {
			pos_.y += speed_; // 降りる動き

			if (pos_.y >= 1080.0f) { // 降り終わったら止める
				pos_.y = 0.0f;
				isFalling_ = false; // 降り終わったので終了
			}
		}
	}
}

void Enemy::Draw() { 
	 if (isAlive_) {
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, enemyTexture, 1, 1, 0.0f, WHITE);

		// ヒットボックスを描画（中心が敵の位置）
		Novice::DrawEllipse((int)(pos_.x), (int)(pos_.y), (int)hitBoxRadiusX_, (int)hitBoxRadiusY_, 0.0f, WHITE, kFillModeWireFrame);
	 }
}