#include "StageScene.h"
#include <Novice.h>
#include <math.h>

StageScene::~StageScene() {
	delete player_;
	delete enemy_;
}

void StageScene::Init() {
	player_ = new Player({1920 / 2, 800}, 6);
	enemy_ = new Enemy({400, 50}, 3, 16, true);

	backGroundTexture_[0] = Novice::LoadTexture("./Resources/Scene/background0.png");
	backGroundTexture_[1] = Novice::LoadTexture("./Resources/Scene/background1.png");
	backGroundWallTexture_[0] = Novice::LoadTexture("./Resources/Scene/wall.png");
	backGroundWallTexture_[1] = Novice::LoadTexture("./Resources/Scene/wall.png");
}

void StageScene::Update(char* keys, char* preKeys) {
	player_->Update(keys, preKeys);
	enemy_->Update();

	backGround_[0].y += backGroundSpeed_;
	backGround_[1].y += backGroundSpeed_;

	if (backGround_[0].y >= 1080) {
		backGround_[0].y = -1080;
	}
	if (backGround_[1].y >= 1080) {
		backGround_[1].y = -1080;
	}
}

void StageScene::Draw() {
	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite((int)backGround_[i].x, (int)backGround_[i].y, backGroundTexture_[i], 1, 1, 0.0f, 0xffffffff);
	}
	player_->Draw();

	if (enemy_->isAlive_ == true) {
		//enemy_->Draw();
	}

	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite((int)backGroundWall_[i].x, (int)backGroundWall_[i].y, backGroundWallTexture_[i], 1, 1, 0.0f, 0xffffffff);
	}
}