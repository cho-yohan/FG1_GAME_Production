#include "Collision.h"
#include <math.h>

Collision::Collision(Boss* boss, Player* player) 
	: boss_(boss), player_(player) {}

void Collision::Update() { 
	if (boss_->isMoving_ == true) {
		isCollision = true;
	}
	if (isCollision == true) {
		for (int i = 0; i < 32; i++) {
			// ボスと弾の当たり判定
			float distance = sqrtf(static_cast<float>(pow(boss_->hitBoxX - player_->bullet_[i]->pos_.x, 2)) + 
				                   static_cast<float>(pow(boss_->hitBoxY - player_->bullet_[i]->pos_.y, 2)));

			if (distance <= boss_->hitBoxWidth + player_->bullet_[i]->radius_ && 
				distance <= boss_->hitBoxHeight + player_->bullet_[i]->radius_) {
				// 当たり判定が成功した場合の処理
				boss_->isSpawnBoss_ = false;          // ボスにダメージを与える（ダメージ量は適宜調整）
				player_->bullet_[i]->isShot_ = false; // 弾を消す
			}
		}
	}
}
