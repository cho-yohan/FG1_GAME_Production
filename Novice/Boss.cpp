#include "Boss.h"
#include <Novice.h>
#include <cstdlib>

Boss::Boss(Vector2 pos, float speed) 
	: moveDirection_(1), isBossActive_(false), spawnTimer_(0.0f), isFalling_(true), fallSpeed_(1.0f) {
	pos_ = pos;
	speed_ = speed;
	isMoving_ = false; // 最初は移動しない状態
	moveTimer_ = 0.0f; 

	// ボスのスプライトを読み込む
	bossTexture = Novice::LoadTexture("./Resources/Boss/boss.png"); // ボスのスプライト画像パスを設定
}

Boss::~Boss() {}

void Boss::Update() {
	// ゲーム開始から5秒経過したらボスを登場させる
	if (!isBossActive_) {
		spawnTimer_ += 1.0f / 60.0f; // 60fps基準で進める

		if (spawnTimer_ >= 5.0f) { // 5秒経過後にボスを登場
			isBossActive_ = true;  // ボスを登場させる
		}
	}

	// ボスが登場している場合のみ動作を開始
	if (isBossActive_) {
		if (isFalling_) {
			// ボスが降りてくる処理
			pos_.y += fallSpeed_; // ボスが上から下に降りる

			// ボスが一定の位置に降りたら座る
			if (pos_.y >= 100.0f) { // 例えばy = 200で「座る」
				pos_.y = 100.0f;    // 座る位置に調整

				isFalling_ = false; // 降りるのを終了
				isMoving_ = true;   // ボスが動き出す
			}
		} else {
			// ボスが降り終わった後、移動処理
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

				// スプライトサイズを考慮して、ボスの中心を画面内に収めるための制限
				float spriteWidth = 495;  // ボススプライトの幅
				float spriteHeight = 325; // ボススプライトの高さ

				// x座標の範囲制限（630から1290まで）
				if (pos_.x + spriteWidth > 1290) {             // 右端
					pos_.x = 1290 - spriteWidth;               // ボスの左上が画面外に出ないように調整
					moveDirection_ = rand() % 2 == 0 ? -1 : 1; // ランダムで左右に動かす
				}
				if (pos_.x < 630) {                            // 左端
					pos_.x = 630;                              // ボスの左上が画面外に出ないように調整
					moveDirection_ = rand() % 2 == 0 ? -1 : 1; // ランダムで左右に動かす
				}

				// y座標の範囲制限（50から500まで）
				if (pos_.y + spriteHeight > 500) {             // 下端
					pos_.y = 500 - spriteHeight;               // ボスの左上が画面外に出ないように調整
					moveDirection_ = rand() % 2 == 0 ? -2 : 2; // ランダムで上下に動かす
				}
				if (pos_.y < 50) {                             // 上端
					pos_.y = 50;                               // ボスの左上が画面外に出ないように調整
					moveDirection_ = rand() % 2 == 0 ? -2 : 2; // ランダムで上下に動かす
				}
			}
		}
	}
}

void Boss::Draw() { 
	// ボスのスプライトを描画（ボスの位置に合わせてスプライトを描画）
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, bossTexture, 1, 1, 0.0f, 0xffffffff);

	// ヒートボックス（楕円形）を描画
	float spriteWidth = 495;                   // ボススプライトの幅
	float spriteHeight = 325;                  // ボススプライトの高さ
	float hitBoxX = pos_.x + spriteWidth / 2;  // ボスの中心X
	float hitBoxY = pos_.y + spriteHeight / 2; // ボスの中心Y
	float hitBoxWidth = spriteWidth * 0.5f;    // ヒートボックスの幅（ボススプライトの80%）
	float hitBoxHeight = spriteHeight * 0.4f;  // ヒートボックスの高さ（ボススプライトの50%）

	// 楕円形でヒートボックスを描画
	Novice::DrawEllipse((int)hitBoxX, (int)hitBoxY, (int)hitBoxWidth, (int)hitBoxHeight, 0.0f, WHITE, kFillModeWireFrame);
}
