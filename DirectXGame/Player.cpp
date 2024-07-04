#define NOMINMAX

#include "Player.h"
#include <cassert>
#include <numbers>
#include <Input.h>
#include <algorithm>

void Player::Initialize( Model* model, uint32_t textureHandle, ViewProjection* viewProjection,const Vector3& position) {

	// NULLチェック
	assert(model);

	worldTransform_.Initialize();

	// 引数の内容をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;


}

void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// 移動入力
	
	// 接地状態
	if (onGround_) {

		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

				// 左移動中の右入力
				if (velocity_.x < 0.0f) {

					// 速度と逆方向に入力中はブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x += kAcceleration;

				if (lrDirection_ != LRDirection::kRight) {

					lrDirection_ = LRDirection::kRight;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーに時間を設定
					turnTimer_ = kTimeTurn;
				}

			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {

				// 右移動中の左入力
				if (velocity_.x > 0.0f) {

					// 速度と逆方向に入力中はブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x -= kAcceleration;

				if (lrDirection_ != LRDirection::kLeft) {

					lrDirection_ = LRDirection::kLeft;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーに時間を設定
					turnTimer_ = kTimeTurn;
				}
			}

			// 加速、減速
			velocity_ += acceleration;

			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {

			// 非入力時は減衰
			velocity_.x *= (1.0f - kAcceleration);
		}

		// 旋回制御
		if (turnTimer_ > 0.0f) {

			// 旋回タイマーをカウントダウン
			turnTimer_ -= 1.0f / 60.0f;

			// 左右の自キャラの角度テーブル
			float destinationRotationYTable[] = {

			    std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f

			};

			// 状態に応じた角度を取得
			float destinationRotationY =
			    destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

			// 自キャラの角度を設定
			worldTransform_.rotation_.y = destinationRotationY;

			float t = 1.0f - (turnTimer_ / kTimeTurn);

			worldTransform_.rotation_.y = std::lerp(turnFirstRotationY_, destinationRotationY, t);

		} else {

			float destinationRotationYTable[] = {

			    std::numbers::pi_v<float> / 2.0f,       // 右方向
			    std::numbers::pi_v<float> * 3.0f / 2.0f // 左方向

			};

			float destinationRotationY =
			    destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

			worldTransform_.rotation_.y = destinationRotationY;
		}

		// 移動
		worldTransform_.translation_ += velocity_;
	
		if (Input::GetInstance()->PushKey(DIK_UP)) {
		
		// ジャンプ初速
			velocity_ += Vector3(0, kJumpAcceleration, 0);
	
		}

		// ジャンプ開始
		if (velocity_.y > 0.0f) {

			onGround_ = false;

		}
	
// 空中
	} else {

			// 落下速度
			velocity_ += Vector3(0, -kGravityAcceleration, 0);

		worldTransform_.translation_ += Vector3(velocity_);

		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

		// 着地フラグ
		bool landing = false;

		// 地面との当たり判定
		// 下降中
		if (velocity_.y < 0) {

			// Y座標が地面以下になったら着地
			if (worldTransform_.translation_.y <= 1.0f) {

				landing = true;
			}
		}

		// 着地
		if (landing) {
		
		// めり込み排除
			worldTransform_.translation_.y = 1.0f;

			// 摩擦で横方向速度が減衰
			velocity_.x *= (1.0f - kAttenuation);

			// 下方向速度をリセット
			velocity_.y = 0.0f;

			// 接地状態に移行
			onGround_ = true;
		
		}
	
	}

	// 行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);

}