#include "ClearScene.h"
#include <Novice.h>

void ClearScene::Init() {
	clearScreenTexture_ = Novice::LoadTexture("./Resources/Scene/gameClear.png");
}

void ClearScene::Update(char* keys, char* preKeys) {
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
		sceneNo = TITLE;
	}
}

void ClearScene::Draw() { Novice::DrawSprite(0, 0, clearScreenTexture_, 1, 1, 0.0f, 0xffffffff); }