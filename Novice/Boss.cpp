#include "Boss.h"
#include <Novice.h>
#include <cstdlib>

Boss::Boss(Vector2 pos, float speed, float radius) : moveDirection_(1) {
	pos_ = pos;
	speed_ = speed;
	radius_ = radius;

	isMoving_ = true;  // 最初は動く状態
	moveTimer_ = 0.0f; // タイマーを初期化
}

Boss::~Boss() {}

void Boss::Update() {
	// タイマーを進める
	moveTimer_ += 1.0f / 60.0f; // 60fps基準で進める

	// 一定時間ごとに動く方向をランダムに切り替える
	if (moveTimer_ >= 3.0f) { // 例えば3秒ごとに切り替え
		isMoving_ = true;     // 動かす

		// ランダムに動く方向を設定（-2から2の間でランダム、斜め方向を含む）
		moveDirection_ = rand() % 8 - 4; // -4, -3, -2, -1, 0, 1, 2, 3, 4 の範囲でランダム
		moveTimer_ = 0.0f;               // タイマーをリセット
	}

	// ボスが動いている場合
	if (isMoving_) {
		// ボスの移動処理
		if (moveDirection_ == 1) { // 右に移動
			pos_.x += speed_;
		} else if (moveDirection_ == -1) { // 左に移動
			pos_.x -= speed_;
		} else if (moveDirection_ == 2) { // 下に移動
			pos_.y += speed_;
		} else if (moveDirection_ == -2) { // 上に移動
			pos_.y -= speed_;
		} else if (moveDirection_ == 3) { // 右下に移動
			pos_.x += speed_;
			pos_.y += speed_;
		} else if (moveDirection_ == -3) { // 左下に移動
			pos_.x -= speed_;
			pos_.y += speed_;
		} else if (moveDirection_ == 4) { // 右上に移動
			pos_.x += speed_;
			pos_.y -= speed_;
		} else if (moveDirection_ == -4) { // 左上に移動
			pos_.x -= speed_;
			pos_.y -= speed_;
		}

		// x座標の範囲制限（630から1290まで）
		// 画面内に収めるためにボスの中心を考慮して調整
		if (pos_.x + radius_ > 1290) {                 // 右端
			pos_.x = 1290 - radius_;                   // 画面端で止める
			moveDirection_ = rand() % 2 == 0 ? -1 : 1; // ランダムで左右に動かす
		}
		if (pos_.x < 630) {                            // 左端
			pos_.x = 630;                              // 画面端で止める
			moveDirection_ = rand() % 2 == 0 ? -1 : 1; // ランダムで左右に動かす
		}

		// y座標の範囲制限（50から500まで）
		// ボスの中心を基準に制限
		if (pos_.y + radius_ > 500) {                  // 下端
			pos_.y = 500 - radius_;                    // 画面端で止める
			moveDirection_ = rand() % 2 == 0 ? -2 : 2; // ランダムで上下に動かす
		}
		if (pos_.y < 50) {                             // 上端
			pos_.y = 50;                               // 画面端で止める
			moveDirection_ = rand() % 2 == 0 ? -2 : 2; // ランダムで上下に動かす
		}
	}
}

void Boss::Draw() { 
	Novice::DrawBox((int)pos_.x, (int)pos_.y, (int)radius_, (int)radius_, 0.0f, WHITE, kFillModeSolid); 
}
