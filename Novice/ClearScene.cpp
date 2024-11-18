#include "ClearScene.h"
#include <Novice.h>

void ClearScene::Init() {
	clearScreenTexture_[0] = Novice::LoadTexture("./Resources/Scene/clear0.png");
	clearScreenTexture_[1] = Novice::LoadTexture("./Resources/Scene/clear1.png");
	clearTextTexture_ = Novice::LoadTexture("./Resources/Scene/clearText.png");
}

void ClearScene::Update(char* keys, char* preKeys) {
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
		sceneNo = TITLE;
	}

	clearScreen_[0].y += clearScreenSpeed_;
	clearScreen_[1].y += clearScreenSpeed_;

	if (clearScreen_[0].y >= 720) {
		clearScreen_[0].y = -720;
	}
	if (clearScreen_[1].y >= 720) {
		clearScreen_[1].y = -720;
	}
}

void ClearScene::Draw() {
	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite((int)clearScreen_[i].x, (int)clearScreen_[i].y, clearScreenTexture_[i], 1, 1, 0.0f, 0xffffffff);
	}
	Novice::DrawSprite((int)clearText.x, (int)clearText.y, clearTextTexture_, 1, 1, 0.0f, WHITE);
}