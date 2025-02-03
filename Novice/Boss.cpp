#include "Boss.h"
#include <Novice.h>
#include <cstdlib>

Boss::Boss(Vector2 pos, float speed)
    : moveDirection_(1), isBossActive_(false), spawnTimer_(0.0f), isFalling_(true), fallSpeed_(1.0f), attackTimer_(0.0f), attackInterval_(1.0f), hpSizeX(680), hpSizeY(58), rotateBulletTimer_(0.0f),
      isRotating_(false) { // 攻撃間隔は1秒
	pos_ = pos;
	speed_ = speed;
	isMoving_ = false; // 最初は移動しない状態
	moveTimer_ = 0.0f;

	// ボスのスプライトを読み込む
	bossTexture = Novice::LoadTexture("./Resources/Boss/boss.png"); // ボスのスプライト画像パスを設定
	hpTexture = Novice::LoadTexture("./Resources/Boss/HPbar.png");
	hpIcon = Novice::LoadTexture("./Resources/Boss/bossIcon.png");
}

Boss::~Boss() {}

void Boss::TakeDamage() {
	// HPが0以下になった場合、ボスを倒す
	if (hpSizeX <= 0) {
		hpSizeX = 0;
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

					return;
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

				// 回転する弾丸が発射されている場合
				if (isRotating_) {
					rotateBulletTimer_ += 1.0f / 60.0f; // 60fps基準でタイマー進行

					if (rotateBulletTimer_ >= rotateBulletDuration_) {
						isRotating_ = false;       // 回転する弾幕発射終了
						isMoving_ = true;          // ボスを再び移動
						rotateBulletTimer_ = 0.0f; // タイマーリセット
					} else {
						fireTimer_ += 1.0f / 60.0f; // 60fps基準で発射タイマー進行
						if (fireTimer_ >= fireRate_) {
							FireRotatingBullets();
							fireTimer_ = 0.0f; // タイマーリセット
						}
					}
				}

				// ボスが移動している場合
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

			// 回転する弾丸が発射されていない場合にボスを移動させる部分
			if (!isRotating_) {
				// 通常の攻撃処理と移動関連のコード
				if (moveDirection_ == 0) {
					attackTimer_ += 1.0f / 60.0f; // 60fps基準でタイマーを増加

					if (attackTimer_ >= attackInterval_) {
						int attackType = rand() % 2; // 3種類の攻撃タイプからランダムで選択
						if (attackType == 0) {
							FireBullets(); // 通常の弾丸を発射
						} else if (attackType == 1) {
							FireRotatingBullets(); // 回転する弾丸を発射
							isRotating_ = true;    // 回転する弾丸発射中フラグを立てる
							isMoving_ = false;     // 回転する弾丸発射中はボスを停止させる
						}
						attackTimer_ = 0.0f; // タイマーをリセット
					}
				}
			}

			// 弾の更新と削除
			for (auto it = bullets.begin(); it != bullets.end();) {
				it->Update();

				// 弾が画面外に出た場合は削除
				if (!it->hitBox_) {
					it = bullets.erase(it); // 弾を削除
				} else {
					++it;
				}
			}
			for (auto it = rotatingBullets.begin(); it != rotatingBullets.end();) {
				it->Update();

				// 画面外に出た回転弾を削除
				if (!it->hitBox_) {
					it = rotatingBullets.erase(it); // 弾を削除
				} else {
					++it;
				}
			}
		}
	}
}

void Boss::Draw() {
	// 弾丸の描画
	for (auto& bullet : bullets) {
		bullet.Draw();
	}
	for (auto& bullet : rotatingBullets) {
		bullet.Draw();
	}

	// ボスのスプライトを描画（ボスの位置に合わせてスプライトを描画）
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, bossTexture, 1, 1, 0.0f, 0xffffffff);

	hitBoxX = pos_.x + spriteWidth / 2;       // ボスの中心X
	hitBoxY = pos_.y + spriteHeight / 2 - 75; // ボスの中心Y

	if (hitBox_ == false) {
		// 楕円形でヒートボックスを描画
		Novice::DrawEllipse((int)hitBoxX, (int)hitBoxY, (int)radius_, (int)radius_, 0.0f, WHITE, kFillModeWireFrame);
	}

	if (isFalling_ == false) {
		Novice::DrawBox(hpPosX + 620, hpPosY + 22, hpSizeX, hpSizeY, 0.0f, RED, kFillModeSolid);
		Novice::DrawSprite(hpTexturePosX + 610, hpTexturePosY + 20, hpTexture, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(hpIconPosX + 930, hpIconPosY + 3, hpIcon, 1, 1, 0.0f, WHITE);
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

void Boss::FireRotatingBullets() {
	float offsetX = 200.0f; // 発射位置Xオフセット
	float offsetY = 160.0f; // 発射位置Yオフセット

	// 発射される角度を計算（90度から270度の間）
	float angle = bulletAngle_; // 現在の角度

	// 発射位置計算
	Vector2 bulletPos = Vector2(pos_.x + offsetX, pos_.y + offsetY);

	// 回転する弾幕を発射
	RotatingBullet bullet(bulletPos, 5, angle);
	rotatingBullets.push_back(bullet); // 回転する弾幕リストに追加

	// 角度を徐々に増加させて回転
	bulletAngle_ += angleChangeRate_; // 角度変化速度調整（90度から270度まで）
}