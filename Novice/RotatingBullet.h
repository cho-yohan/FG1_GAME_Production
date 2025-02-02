#pragma once
#include "Vector2.h"

class RotatingBullet {
public:
    RotatingBullet(Vector2 pos, int speed, float angle);
    void Update();
    void Draw();

public:
    Vector2 pos_;        // 弾の位置
    float radius_ = 40.0f;  // 弾の半径
    int speed_;          // 弾の速度
    float angle_;        // 弾丸の進行方向（ラジアン）
    int bulletTexture_;  // 弾のスプライト画像
    bool hitBox_ = true; // ヒットボックスを描画するかどうか
};
