#include "Player.h"
#include "Bullet.h"
#include <Novice.h>

Player::Player(Vector2 pos, int speed) {
	pos_ = pos;
	speed_ = speed;

	for (int i = 0; i < 32; i++) {
		bullet_[i] = new Bullet({0, 0}, 13, false);
	}

	playerTexture_ = Novice::LoadTexture("./Resources/Player/player.png");
}

Player::~Player() {
	for (int i = 0; i < 32; i++) {
		delete bullet_[i];
	}
}

void Player::Update(char* keys, char* preKeys) {
	if (keys[DIK_W] && preKeys[DIK_W]) {
		pos_.y -= speed_;
	}

	if (keys[DIK_S] && preKeys[DIK_S]) {
		pos_.y += speed_;
	}

	if (keys[DIK_A] && preKeys[DIK_A]) {
		pos_.x -= speed_;
	}

	if (keys[DIK_D] && preKeys[DIK_D]) {
		pos_.x += speed_;
	}

	if (keys[DIK_SPACE]) {
		if (bulletTime_ > 0) {
			bulletTime_--;
		} else {
			bulletTime_ = 7;
		}
		if (bulletTime_ <= 0) {
			for (int i = 0; i < 32; i++) {
				if (!bullet_[i]->isShot_) {
					bullet_[i]->isShot_ = true;
					bullet_[i]->pos_ = pos_;
					break;
				}
			}
		}
	}

	for (int i = 0; i < 32; i++) {
		bullet_[i]->Update();
	}
}

void Player::Draw() {
	Novice::DrawSprite((int)pos_.x - 45, (int)pos_.y, playerTexture_, 1, 1, 0.0f, WHITE);
	for (int i = 0; i < 32; i++) {
		bullet_[i]->Draw();
	}
}