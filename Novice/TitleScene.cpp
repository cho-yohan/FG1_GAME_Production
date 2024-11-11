#include "TitleScene.h"
#include <Novice.h>

void TitleScene::Init() { 
	titleSprite_ = Novice::LoadTexture("./Resources/TitleSceneSprite.png"); 
}

void TitleScene::Update(char* keys, char* preKeys) {
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
		sceneNo = STAGE;
	}
}

void TitleScene::Draw() { Novice::DrawSprite(0, 0, titleSprite_, 1.0f, 1.0f, 0.0f, WHITE); }