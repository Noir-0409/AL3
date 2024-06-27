#include "Player.h"
#include <cassert>

void Player::Initialize( Model* model, uint32_t playerHandle, ViewProjection* viewProjection, const Vector3& position) {

	// NULLチェック
	assert(model);

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// 引数の内容をメンバ変数に記録
	model_ = model;
	playerHandle_ = playerHandle;
	viewProjection_ = viewProjection;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

}

void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	
    // 移動入力
	Vector3 acceleration = {};

	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

		// 左移動中の右入力
		if (velocity_.x < 0.0f) {
		
			// 速度と逆方向に入力中は急ブレーキ
			velocity_.x *= (1.0f - kAttenuation);
		
		}

		acceleration.x += kAcceleration;

		if (lrDirection_ != LRDirection::kRight) {
		
			lrDirection_ = LRDirection::kRight;
		
		}

	}
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {

		// 右移動中の左入力
		if (velocity_.x > 0.0f) {

			// 速度と逆方向に入力中は急ブレーキ
			velocity_.x *= (1.0f - kAttenuation);
		}

		acceleration.x -= kAcceleration;

		if (lrDirection_ != LRDirection::kLeft) {

			lrDirection_ = LRDirection::kLeft;
		}

	}

	// 加速、減速
	velocity_.x += acceleration.x;

	// 最大速度制限
	velocity_.x = std::clamp(velocity_.x, - kLimitRunSpeed, kLimitRunSpeed);

	// 非入力時は移動減衰をかける
	if (!Input::GetInstance()->PushKey(DIK_RIGHT) && !Input::GetInstance()->PushKey(DIK_LEFT)) {
		velocity_.x *= kAttenuation; // 速度に減速率を適用
	}

	// 移動
	worldTransform_.translation_.x += velocity_.x;

	// 行列計算
	worldTransform_.UpdateMatrix();

	// 旋回制御
	{
		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {

		    std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f

		};

		// 状態に応じた角度を取得
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		// 自キャラの角度を設定
		worldTransform_.rotation_.y = destinationRotationY;
	}

}

void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, playerHandle_);

}