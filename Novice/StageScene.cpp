#include "StageScene.h"
#include <Novice.h>

void StageScene::Init() { stageTexture = Novice::LoadTexture("./Resources/Scene/title.png"); }

void StageScene::Update(char* keys, char* preKeys) {
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
		sceneNo = GAME;
	}
}

void StageScene::Draw() { Novice::DrawSprite((int)stageScreen.x + 120, (int)stageScreen.y + 400, stageTexture, 1, 1, 0.0f, 0xffffffff); }