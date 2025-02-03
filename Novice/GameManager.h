#pragma once

#include "IScene.h"
#include "TitleScene.h"
#include "StageScene.h"
#include "GamePlayScene.h"
#include "ClearScene.h"
#include "OverScene.h"
#include <Novice.h>
#include <memory>

class GameManager {
public:
	GameManager();

	~GameManager();

	int Run(char* keys, char* preKeys);

private:
	// keeps track of the scenes
	std::unique_ptr<IScene> sceneArr_[5];

	int currentSceneNo_;
	int prevSceneNo_;
};