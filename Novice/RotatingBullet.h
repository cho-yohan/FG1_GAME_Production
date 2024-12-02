#pragma once
#include "Vector2.h"

class RotatingBullet {
public:
	RotatingBullet(Vector2 pos, Vector2 direction, float speed, float rotationSpeed);
	void Update();
	void Draw();

public:
	Vector2 pos_;         // 弾の位置
	Vector2 direction_;   // 弾の進行方向
	float speed_;         // 弾の速度
	float rotationSpeed_; // 回転の速さ（時計回り）
	float rotationAngle_; // 現在の回転角度
	int bulletTexture_;  // 弾のスプライト画像
	bool hitBox_ = true; // ヒットボックスを描画するかどうかのフラグ
};