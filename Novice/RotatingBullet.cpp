#include "RotatingBullet.h"
#include <Novice.h>
#include <math.h>

RotatingBullet::RotatingBullet(Vector2 pos, int speed, float angle)
    : pos_(pos), speed_(speed), angle_(angle) {
    bulletTexture_ = Novice::LoadTexture("./Resources/Boss/bossBullet2.png");
}

void RotatingBullet::Update() {
    // 弾丸の位置を更新（進行方向に基づいて）
    pos_.x += speed_ * cosf(angle_); // X軸方向の移動
    pos_.y += speed_ * sinf(angle_); // Y軸方向の移動

    // 弾が画面外に出たかどうかを判定（1920x1080画面）
    if (pos_.x < 0 || pos_.x > 1920 || pos_.y < 0 || pos_.y > 1080) {
        hitBox_ = false; // ヒットボックスの描画をしなくする
    }
}

void RotatingBullet::Draw() {
    Novice::DrawSprite((int)pos_.x, (int)pos_.y, bulletTexture_, 1, 1, 0.0f, 0xffffffff);

    // ヒットボックスを描画
    if (hitBox_ == true) {
        Novice::DrawEllipse((int)pos_.x + 40, (int)pos_.y + 40, (int)radius_, (int)radius_, 0.0f, WHITE, kFillModeWireFrame);
    }
}
