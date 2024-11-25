#include "StageScene.h"
#include <Novice.h>

void StageScene::Init() {
	StageBackgroundTexture = Novice::LoadTexture("./Resources/Scene/StageBackground.png"); 
	backGroundWallTexture_[0] = Novice::LoadTexture("./Resources/Scene/wall.png");
	backGroundWallTexture_[1] = Novice::LoadTexture("./Resources/Scene/wall.png");
}

void StageScene::Update(char* keys, char* preKeys) {
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
		sceneNo = GAME;
	}
}

void StageScene::Draw() { 
	Novice::DrawSprite((int)StageBackground.x, (int)StageBackground.y, StageBackgroundTexture, 1, 1, 0.0f, 0xffffffff); 
	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite((int)backGroundWall_[i].x, (int)backGroundWall_[i].y, backGroundWallTexture_[i], 1, 1, 0.0f, 0xffffffff);
	}
}