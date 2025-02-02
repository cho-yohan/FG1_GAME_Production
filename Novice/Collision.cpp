#include "Collision.h"
#include <math.h>

Collision::Collision(Boss* boss, Player* player) 
	: boss_(boss), player_(player) {}

void Collision::playerBulletCollision() { 
	if (boss_->isMoving_ == true) {
		isCollision = true;
	}
	if (isCollision == true) {
		for (int i = 0; i < 32; i++) {
			// プレイヤーの弾とボスのヒットボックス（円形）の衝突判定
			float distance = sqrtf(static_cast<float>(pow(boss_->hitBoxX - player_->bullet_[i]->pos_.x, 2)) + 
				                   static_cast<float>(pow(boss_->hitBoxY - player_->bullet_[i]->pos_.y, 2)));

			// 衝突判定: ボスのヒットボックスが円形の場合、ボスの半径 + 弾の半径を使って距離を計算
			if (boss_->hpSizeX > 0 && distance <= (boss_->radius_ + player_->bullet_[i]->radius_)) {
				// 弾がボスに当たっている場合
				if (player_->bullet_[i]->isShot_) {
					player_->bullet_[i]->SetShot(false);  // 弾を消す
					boss_->hpSizeX -= 1;                  // ボスにダメージを与える
					player_->bullet_[i]->isShot_ = false; // 弾を消したことを記録
				}
			}
		}
	}
}

void Collision::bossBulletCollision() {
	// ボスが移動中の場合、衝突が発生したと見なす
	if (boss_->isMoving_ == true) {
		isCollision = true;
	}

	// 衝突判定が有効な場合、ボスの弾とプレイヤーの衝突を確認
	if (isCollision == true) {
		// ボスの弾を1つずつ確認
		for (int i = 0; i < boss_->bullets.size(); i++) {
			// ボスの弾とプレイヤーのヒットボックスの中心間の距離を計算
			float distance = sqrtf(static_cast<float>(pow(boss_->bullets[i].pos_.x - player_->hitBoxX, 2)) + 
				                   static_cast<float>(pow(boss_->bullets[i].pos_.y - player_->hitBoxY, 2)));

			// 衝突判定: ボスの弾とプレイヤーのヒットボックスの中心間の距離が、両者の半径の合計より小さい場合に衝突とみなす
			if (distance <= (boss_->bullets[i].radius_ + player_->radius)) {
				// 衝突が発生した場合、プレイヤーのx座標を10000に設定して画面外に移動
				player_->pos_.x = 10000;
			}
		}
	}
}

void Collision::bossRotatingBulletCollision() {// ボスが移動中の場合、衝突が発生したと見なす
	if (boss_->isMoving_ == true) {
		isCollision = true;
	}

	// 衝突判定が有効な場合、ボスの弾とプレイヤーの衝突を確認
	if (isCollision == true) {
		// ボスの弾を1つずつ確認
		for (int i = 0; i < boss_->rotatingBullets.size(); i++) {
			// ボスの弾とプレイヤーのヒットボックスの中心間の距離を計算
			float distance = sqrtf(static_cast<float>(pow(boss_->rotatingBullets[i].pos_.x - player_->hitBoxX, 2)) + 
				                   static_cast<float>(pow(boss_->rotatingBullets[i].pos_.y - player_->hitBoxY, 2)));

			// 衝突判定: ボスの弾とプレイヤーのヒットボックスの中心間の距離が、両者の半径の合計より小さい場合に衝突とみなす
			if (distance <= (boss_->rotatingBullets[i].radius_ + player_->radius)) {
				// 衝突が発生した場合、プレイヤーのx座標を10000に設定して画面外に移動
				player_->pos_.x = 10000;
			}
		}
	}
}
