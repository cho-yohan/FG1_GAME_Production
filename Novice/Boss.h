#pragma once
#include "BossBullet.h"
#include "RotatingBullet.h"
#include "Vector2.h"
#include <vector>

class Boss {
public:
	Boss(Vector2 pos, float speed);
	~Boss();
	void Update();
	void Draw();
	void TakeDamage(); // ダメージを受ける関数を追加

	// ヒートボックス（楕円形）を描画
	float spriteWidth = 495;  // ボススプライトの幅
	float spriteHeight = 325; // ボススプライトの高さ

	float hitBoxX; // ボスの中心X
	float hitBoxY; // ボスの中心Y
	float radius_ = 220;

	int isSpawnBoss_ = true;
	bool isMoving_; // ボスが動くか止まるかのフラグ

	Vector2 pos_;                    // ボスの位置
	std::vector<BossBullet> bullets; // ボスの弾丸
	std::vector<RotatingBullet> rotatingBullets;

	int hpSizeX, hpSizeY;

private:
	float speed_;          // ボスの移動速度
	int moveDirection_;    // 移動方向：1 = 右、-1 = 左、2 = 下、-2 = 上
	float moveTimer_;      // ボスが止まるか動くかを切り替えるためのタイマー
	bool isBossActive_;    // ボスが登場したかどうかのフラグ
	float spawnTimer_;     // ボスが登場するまでの待機タイマー
	bool isFalling_;       // ボスが降りているかどうかのフラグ
	float fallSpeed_;      // ボスが降りる速さ
	bool hitBox_ = true;   // ヒットボックスを描画するかどうかのフラグ
	int bossTexture;       // ボスのスプライト
	float attackTimer_;    // 攻撃のタイマー
	float attackInterval_; // 攻撃の間隔

	int hp;
	int hpPosX, hpPosY;

	int hpTexture;
	int hpTexturePosX, hpTexturePosY;

	int hpIcon;
	int hpIconPosX, hpIconPosY;

	bool isRotating_ = false;            // 回転する弾丸が発射中かどうか
	float rotateBulletTimer_ = 0.0f;     // 回転弾発射時間
	float rotateBulletDuration_ = 10.0f; // 回転弾の発射時間（秒）

	float bulletAngle_ = 90.0f;    // 発射角度：90度から開始（0度から180度の範囲）
	float angleChangeRate_ = 3.0f; // 角度変化速度調整

	// 発射間隔を設定するためのタイマー追加
	float fireRate_ = 0.1f; // 発射間隔（0.1秒）
	float fireTimer_ = 0.0f;

	void FireBullets();         // 弾丸を発射する関数
	void FireRotatingBullets(); // 周囲に散らばる弾丸を発射する関数
};