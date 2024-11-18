#pragma once
#include "IScene.h"
#include "Vector2.h"

class ClearScene : public IScene {
public:
	void Init() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	Vector2 clearScreen_[2]{0, 0, 0, -720};
	int clearScreenSpeed_ = 2;
	int clearScreenTexture_[2];

	Vector2 clearText{390, 310};
	int clearTextTexture_;
};