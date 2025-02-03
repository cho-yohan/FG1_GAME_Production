#include "OverScene.h"
#include <Novice.h>

void OverScene::Init() {
	overScreenTexture_ = Novice::LoadTexture("./Resources/Scene/gameOver.png");
}

void OverScene::Update(char* keys, char* preKeys) {
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
		sceneNo = TITLE;
	}
}

void OverScene::Draw() { Novice::DrawSprite(0, 0, overScreenTexture_, 1, 1, 0.0f, 0xffffffff); }