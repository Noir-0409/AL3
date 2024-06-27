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
	// 左右移動
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
	
	// 左右加速
		Vector3 acceleration = {};
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
	
		acceleration.x += kAcceleration;
	
	} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
	
		acceleration.x -= kAcceleration;
	
	}

	// 加速、減速
	velocity_.x += acceleration.x;
	velocity_.y += acceleration.y;
	velocity_.z += acceleration.z;

	}

	// 移動
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

	// 行列計算
	worldTransform_.UpdateMatrix();

}

void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, playerHandle_);

}