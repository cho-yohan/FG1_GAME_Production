#pragma once

#pragma once
#include "IScene.h"
#include "Vector2.h"

class StageScene : public IScene {
public:
	void Init() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	Vector2 stageBackground_{610, 0};
	Vector2 backGroundWall_[2]{0, 0, 1310, 0};
	Vector2 botton_[4]{656, 848, 620, 892, 656, 892, 692, 892};

	int stageBackgroundTexture_;
	int backGroundWallTexture_[2];
	int bottonTexture_[4];
};