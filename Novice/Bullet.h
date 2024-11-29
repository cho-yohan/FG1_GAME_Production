#pragma once
#include "Enemy.h"
#include "Vector2.h"

class Bullet {
public:
	Bullet(Vector2 pos, int speed, int isShot, int direction);
	void Update();
	void Draw();

public:
	Vector2 pos_;
	float radius_ = 10.0f; // 弾のヒットボックスの半径（円形）

	int speed_;          // 弾の速度
	int isShot_ = false; // 弾が発射されているか
	int bulletTexture_;  // 弾のスプライト画像
	bool hitBox_ = true; // ヒットボックスを描画するかどうかのフラグ

	int direction_; // 追加: 1で右、-1で左、0で無効
};