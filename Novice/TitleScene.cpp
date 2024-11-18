#include "TitleScene.h"
#include <Novice.h>

void TitleScene::Init() { titleTexture_ = Novice::LoadTexture("./Resources/Scene/title.png"); }

void TitleScene::Update(char* keys, char* preKeys) {
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
		sceneNo = STAGE;
	}
}

void TitleScene::Draw() { Novice::DrawSprite((int)titleScreen_.x, (int)titleScreen_.y, titleTexture_, 1, 1, 0.0f, 0xffffffff); }