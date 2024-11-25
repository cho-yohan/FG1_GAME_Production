#include "GameManager.h"

GameManager::GameManager() {
	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[STAGE] = std::make_unique<StageScene>();
	sceneArr_[GAME] = std::make_unique<GamePlayScene>();
	sceneArr_[CLEAR] = std::make_unique<ClearScene>();

	currentSceneNo_ = TITLE;
}

GameManager::~GameManager() {}

int GameManager::Run(char* keys, char* preKeys) {

	sceneArr_[currentSceneNo_]->Init();

	while (Novice::ProcessMessage() == 0) {

		Novice::BeginFrame();
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		prevSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

		if (prevSceneNo_ != currentSceneNo_) {
			sceneArr_[currentSceneNo_]->Init();
		}

		sceneArr_[currentSceneNo_]->Update(keys, preKeys);
		sceneArr_[currentSceneNo_]->Draw();
		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
	return 0;
}