#include "StageScene.h"
#include <Novice.h>

void StageScene::Init() {
	stageBackgroundTexture_ = Novice::LoadTexture("./Resources/Scene/StageBackground.png"); 
	backGroundWallTexture_[0] = Novice::LoadTexture("./Resources/Scene/wall.png");
	backGroundWallTexture_[1] = Novice::LoadTexture("./Resources/Scene/wall.png");
	bottonTexture_[0] = Novice::LoadTexture("./Resources/Scene/Wbotton.png");
	bottonTexture_[1] = Novice::LoadTexture("./Resources/Scene/Abotton.png");
	bottonTexture_[2] = Novice::LoadTexture("./Resources/Scene/Sbotton.png");
	bottonTexture_[3] = Novice::LoadTexture("./Resources/Scene/Dbotton.png");
}

void StageScene::Update(char* keys, char* preKeys) {
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
		sceneNo = GAME;
	}
}

void StageScene::Draw() { 
	Novice::DrawSprite((int)stageBackground_.x, (int)stageBackground_.y, stageBackgroundTexture_, 1, 1, 0.0f, 0xffffffff); 
	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite((int)backGroundWall_[i].x, (int)backGroundWall_[i].y, backGroundWallTexture_[i], 1, 1, 0.0f, 0xffffffff);
	}
	for (int i = 0; i < 4; i++) {
		Novice::DrawSprite((int)botton_[i].x, (int)botton_[i].y, bottonTexture_[i], 1, 1, 0.0f, 0xffffffff);
	}
}