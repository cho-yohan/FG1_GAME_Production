#pragma once
#include "Vector2.h"
#include "Bullet.h"

class Enemy {
public:
	Enemy(Vector2 pos, float speed);
	void Update();
	void Draw();
	void Kill();   // 敵を倒す
	bool IsAlive() const { return isAlive_; }
	bool CheckCollisionWithBullet(const Bullet& bullet); // 衝突判定

	Vector2 pos_; // 敵の位置
	float hitBoxRadiusX_ = 15.0f; // X方向半径
	float hitBoxRadiusY_ = 30.0f; // Y方向半径

private:
	float speed_;                     // 敵の移動速度
	bool isFalling_;                  // 敵が落ちているかどうか
	float fallTimer_;                 // 敵が降り始めてからの経過時間
	const float fallDuration_ = 5.0f; // 敵が降りるのにかかる時間（例：5秒）
	int enemyTexture;                 // 敵のスプライトのテクスチャ

	// 敵が降りる処理
	void StartFalling();

	bool isAlive_ = true; // 敵が生きているか
};