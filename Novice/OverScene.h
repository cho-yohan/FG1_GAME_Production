#pragma once
#include "IScene.h"
#include "Vector2.h"

class OverScene : public IScene {
public:
	void Init() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	int overScreenTexture_;
};