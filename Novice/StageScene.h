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
	Vector2 StageBackground{610, 0};
	Vector2 backGroundWall_[2]{0, 0, 1310, 0};
	int StageBackgroundTexture;
	int backGroundWallTexture_[2];
};