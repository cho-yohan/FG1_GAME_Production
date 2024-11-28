#include "Player.h"
#include "Bullet.h"
#include <Novice.h>

Player::Player(Vector2 pos, float speed) {
	pos_ = pos;
	speed_ = speed;

	for (int i = 0; i < 32; i++) {
		bullet_[i] = new Bullet({0, 0}, 15, false, 0);
	}

	playerTexture_ = Novice::LoadTexture("./Resources/Player/player.png");
}

Player::~Player() {
	for (int i = 0; i < 32; i++) {
		delete bullet_[i];
	}
}

void Player::Update(char* keys, char* preKeys) {
	// 移動方向のベクトルを作成
	float moveX = 0.0f;
	float moveY = 0.0f;

	if (keys[DIK_W] && preKeys[DIK_W]) {
		moveY -= 1.0f; // 上に移動
	}
	if (keys[DIK_S] && preKeys[DIK_S]) {
		moveY += 1.0f; // 下に移動
	}
	if (keys[DIK_A] && preKeys[DIK_A]) {
		moveX -= 1.0f; // 左に移動
	}
	if (keys[DIK_D] && preKeys[DIK_D]) {
		moveX += 1.0f; // 右に移動
	}

	// もし移動ベクトルがゼロでなければ（斜め移動している場合）
	if (moveX != 0.0f || moveY != 0.0f) {
		// ベクトルを正規化して、移動速度を一定に保つ
		float length = sqrtf(moveX * moveX + moveY * moveY); // ベクトルの長さ（大きさ）
		moveX /= length;                                     // ベクトルを正規化
		moveY /= length;                                     // ベクトルを正規化
	}

	 // 正規化された移動方向に基づいて移動する
	pos_.x += moveX * speed_;
	pos_.y += moveY * speed_;

	// プレイヤーの移動制限（画面外に出ないように制限）
	if (pos_.x < 0) {
		pos_.x = 0;
	}
	if (pos_.y < 0) {
		pos_.y = 0;
	}
	if (pos_.x > 1290) { // 仮に右端が1290とした場合
		pos_.x = 1290;
	}
	if (pos_.y > 1010) { // 仮に下端が1010とした場合
		pos_.y = 1010;
	}

	// 弾の発射処理
	if (keys[DIK_SPACE]) {
		if (bulletTime_ > 0) {
			bulletTime_--;
		} else {
			bulletTime_ = 10;
		}
		if (bulletTime_ <= 0) {
			for (int i = 0; i < 32; i++) {
				if (!bullet_[i]->isShot_) {
					bullet_[i]->isShot_ = true;
					bullet_[i]->pos_ = {pos_.x - 12, pos_.y}; // 左に12ピクセルずらして発射
					bullet_[i]->speed_ = 15;                  // 速度は一定で、縦方向だけ
					break;
				}
			}

			for (int i = 0; i < 32; i++) {
				if (!bullet_[i]->isShot_) {
					bullet_[i]->isShot_ = true;
					bullet_[i]->pos_ = {pos_.x + 12, pos_.y}; // 右に12ピクセルずらして発射
					bullet_[i]->speed_ = 15;                  // 速度は一定で、縦方向だけ
					break;
				}
			}
		}
	}

	// 弾の更新
	for (int i = 0; i < 32; i++) {
		bullet_[i]->Update();
	}
}

void Player::Draw() {
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, playerTexture_, 1, 1, 0.0f, WHITE);
	for (int i = 0; i < 32; i++) {
		bullet_[i]->Draw();
	}
}