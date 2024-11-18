#pragma once
#include "IScene.h"
#include "Vector2.h"

class TitleScene : public IScene {
public:
	void Init() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	Vector2 titleScreen_;
	int titleTexture_;
};