#pragma once
#include "Enemy.h"
#include "IScene.h"
#include "Player.h"
#include "Vector2.h"

class StageScene : public IScene {
public:
	void Init() override;
	~StageScene();
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

public:
	Player* player_;
	Enemy* enemy_;

	Vector2 backGround_[2]{0, 0, 0, -720};
	Vector2 backGroundWall_[2]{0, 0, 1310, 0};
	int backGroundSpeed_ = 3;
	int backGroundTexture_[2];
	int backGroundWallTexture_[2];
};