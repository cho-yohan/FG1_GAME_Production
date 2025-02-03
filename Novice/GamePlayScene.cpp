#include "GamePlayScene.h"
#include <Novice.h>
#include <math.h>
#include <string>

GamePlayScene::~GamePlayScene() {
	delete player_;
	delete boss_;
	delete collision_;
}

void GamePlayScene::Init() {
	player_ = new Player({1920 / 2 - 30, 900}, 4.0f);
	boss_ = new Boss({710, -340}, 1.0f);
	
	backGroundTexture_[0] = Novice::LoadTexture("./Resources/Scene/background0.png");
	backGroundTexture_[1] = Novice::LoadTexture("./Resources/Scene/background1.png");
	backGroundWallTexture_[0] = Novice::LoadTexture("./Resources/Scene/wall.png");
	backGroundWallTexture_[1] = Novice::LoadTexture("./Resources/Scene/wall.png");

	collision_ = new Collision(boss_, player_);
}

void GamePlayScene::Update(char* keys, char* preKeys) {
	player_->Update(keys, preKeys);
	boss_->Update();
	collision_->playerBulletCollision();
	collision_->bossBulletCollision();
	collision_->bossRotatingBulletCollision();

	if (boss_->hpSizeX <= 0) {
		boss_->hpSizeX = 0;
		sceneNo = CLEAR;
	}

	backGround_[0].y += backGroundSpeed_;
	backGround_[1].y += backGroundSpeed_;

	if (backGround_[0].y >= 1080) {
		backGround_[0].y = -1080;
	}
	if (backGround_[1].y >= 1080) {
		backGround_[1].y = -1080;
	}
}

void GamePlayScene::Draw() {
	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite((int)backGround_[i].x, (int)backGround_[i].y, backGroundTexture_[i], 1, 1, 0.0f, 0xffffffff);
	}
	player_->Draw();
	boss_->Draw();

	// 弾の描画
	for (Bullet& bullet : bullets_) {
		bullet.Draw();
	}

	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite((int)backGroundWall_[i].x, (int)backGroundWall_[i].y, backGroundWallTexture_[i], 1, 1, 0.0f, 0xffffffff);
	}
}
