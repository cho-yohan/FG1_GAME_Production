#pragma once
#include "Boss.h"
#include "Enemy.h"
#include "IScene.h"
#include "Player.h"
#include "Vector2.h"
#include "Bullet.h"
#include "Collision.h"

class GamePlayScene : public IScene {
public:
	void Init() override;
	~GamePlayScene();
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

public:
	Player* player_;
	Enemy* enemy_;
	Boss* boss_;
	Collision* collision_;

	Vector2 backGround_[2]{0, 0, 0, -1080};
	Vector2 backGroundWall_[2]{-10, 0, 1320, 0};
	int backGroundSpeed_ = 3;
	int backGroundTexture_[2];
	int backGroundWallTexture_[2];

	std::vector<Bullet> bullets_; // 弾のリスト
};