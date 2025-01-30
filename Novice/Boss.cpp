#include "Boss.h"
#include <Novice.h>
#include <cstdlib>

Boss::Boss(Vector2 pos, float speed) 
	: moveDirection_(1), isBossActive_(false), spawnTimer_(0.0f), isFalling_(true), fallSpeed_(1.0f), 
	attackTimer_(0.0f), attackInterval_(1.0f), hp_(100), 
	hitBoxX(0), hitBoxY(0), hitBoxWidth(100), hitBoxHeight(100) { // 攻撃間隔は1秒
	pos_ = pos;
	speed_ = speed;
	isMoving_ = false; // 最初は移動しない状態
	moveTimer_ = 0.0f; 

	// ボスのスプライトを読み込む
	bossTexture = Novice::LoadTexture("./Resources/Boss/boss.png"); // ボスのスプライト画像パスを設定
}

Boss::~Boss() {}

void Boss::TakeDamage(int damage) {
	hp_ -= damage; // ダメージを受ける

	// HPが0以下になった場合、ボスを倒す
	if (hp_ <= 0) {
		hp_ = 0;
		isBossActive_ = false; // ボスが倒れたので非アクティブにする
		// 他の死亡処理をここに追加することもできる
	}
}

void Boss::Update() {
	if (isSpawnBoss_) {
		// ゲーム開始から5秒経過したらボスを登場させる
		if (!isBossActive_) {
			spawnTimer_ += 1.0f / 60.0f; // 60fps基準で進める

			if (spawnTimer_ >= 1.0f) { // 5秒経過後にボスを登場
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

			// ボスが止まっている場合に弾を発射
			if (moveDirection_ == 0) {
				attackTimer_ += 1.0f / 60.0f; // 60fps基準で進める

				if (attackTimer_ >= attackInterval_) { // 一定時間ごとに弾を発射
					// 攻撃方法をランダムで選択
					int attackType = rand() % 2; // 0: 通常攻撃, 1: 扇型攻撃
					if (attackType == 0) {
						FireBullets(); // 通常弾発射
					} else {
						//FireBulletSpiral(); // 扇型弾発射
					}
					attackTimer_ = 0.0f; // タイマーをリセット
				}
			}

			// 弾の更新
			for (auto& bullet : bullets) {
				bullet.Update();
			}

			for (auto& bullet : rotatingBullets) {
				bullet.Update();
			}
		}
	}
}

void Boss::Draw() { 
	// 弾丸の描画
	for (auto& bullet : bullets) {
		bullet.Draw();
	}

	// ボスのスプライトを描画（ボスの位置に合わせてスプライトを描画）
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, bossTexture, 1, 1, 0.0f, 0xffffffff);

	hitBoxX = pos_.x + spriteWidth / 2;  // ボスの中心X
	hitBoxY = pos_.y + spriteHeight / 2; // ボスの中心Y
	hitBoxWidth = spriteWidth * 0.48f;   // ヒートボックスの幅
	hitBoxHeight = spriteHeight * 0.4f;  // ヒートボックスの高さ

	// 楕円形でヒートボックスを描画
	Novice::DrawEllipse((int)hitBoxX, (int)hitBoxY, (int)hitBoxWidth, (int)hitBoxHeight, 0.0f, WHITE, kFillModeWireFrame);

	for (auto& bullet : rotatingBullets) {
		bullet.Draw();
	}
}

void Boss::FireBullets() {
	// ボスの中心を基準にして少し位置を調整
	float offsetX = 200.0f; // 発射位置をX方向に50ピクセルオフセット
	float offsetY = 160.0f; // 発射位置をY方向に50ピクセルオフセット

	// ボスの周りに弾を発射
	for (float i = 0; i < 9; ++i) { // 9方向に弾を発射
		float direction = i * 30;   // 0, 30, 60, ..., 300度の方向

		// 発射位置をオフセットを加味して決定
		Vector2 bulletPos = Vector2(pos_.x + offsetX, pos_.y + offsetY);

		// 弾を発射
		BossBullet bullet(bulletPos, 5, direction); // 新しい発射位置で弾を作成
		bullets.push_back(bullet);                  // 弾を管理するリストに追加
	}
}

void Boss::FireBulletSpiral() {
	// ボスの位置を基準にして弾を放射
	int numBullets = 12;                     // 12個の弾を発射
	float angleOffset = 360.0f / numBullets; // 弾の間隔角度

	// ボスの中心を基準にして少し位置を調整
	float offsetX = 220.0f; // 発射位置をX方向に50ピクセルオフセット
	float offsetY = 190.0f; // 発射位置をY方向に50ピクセルオフセット

	// 各弾を発射
	for (int i = 0; i < numBullets; ++i) {
		// 弾の放射角度を決定
		float angle = i * angleOffset;

		// 発射された弾の初期位置を計算（ボスから放射される位置）
		Vector2 bulletPos = Vector2(pos_.x + offsetX, pos_.y + offsetY);

		// 弾の進行方向（放射方向）
		Vector2 bulletDirection = Vector2(cosf(angle), sinf(angle));

		// 弾の速度
		float speed = 5.0f;

		// 回転の速度（時計回り）
		float rotationSpeed = 0.05f; // 回転の速さ

		// 発射された弾を回転させるためのオブジェクトを作成
		RotatingBullet bullet(bulletPos, bulletDirection, speed, rotationSpeed);
		rotatingBullets.push_back(bullet);
	}
}