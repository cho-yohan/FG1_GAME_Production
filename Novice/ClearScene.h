#pragma once
#include "IScene.h"
#include "Vector2.h"

class ClearScene : public IScene {
public:
	void Init() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	int clearScreenTexture_;
};