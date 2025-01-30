#include "Collision.h"
#include <math.h>

Collision::Collision(Boss* boss, std::vector<Bullet>* bullets) 
	: boss_(boss), bullets_(bullets) {}

void Collision::Update() { 
	if (this == nullptr) {
		// this が nullptr ならばエラーログを出力
		return;
	}

	if (boss_ == nullptr || bullets_ == nullptr) {
		// boss_ や bullet_ が nullptr ならばエラーログを出力
		return;
	}

	// ボスと弾の当たり判定
	for (auto& bullet : *bullets_) {
		float distance = sqrtf(static_cast<float>(pow(boss_->hitBoxX - bullet.pos_.x, 2)) + 
			                   static_cast<float>(pow(boss_->hitBoxY - bullet.pos_.y, 2)));

		if (distance <= boss_->hitBoxWidth + bullet.radius_ && 
			distance <= boss_->hitBoxHeight + bullet.radius_) {
			// 当たり判定が成功した場合の処理
			boss_->pos_.x = 10000; // ボスにダメージを与える（ダメージ量は適宜調整）
			bullet.SetShot(false); // 弾を消す
		}
	}
}
