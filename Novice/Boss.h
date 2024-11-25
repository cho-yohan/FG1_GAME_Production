#pragma once
#include "Vector2.h"

class Boss {
public:
	Boss(Vector2 pos, float speed, float radius);
	~Boss();
	void Update();
	void Draw();

private:
	Vector2 pos_; // ボスの位置
	float radius_;  // ボスの半径
	float speed_;   // ボスの移動速度

	int moveDirection_; // 移動方向：1 = 右、-1 = 左、2 = 下、-2 = 上
	bool isMoving_;   // ボスが動くか止まるかのフラグ
	float moveTimer_; // ボスが止まるか動くかを切り替えるためのタイマー
};