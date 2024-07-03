#include "Player.h"
#include <cassert>
#include <numbers>
#include <Input.h>

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
	// 左右移動操作
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
	
	// 左右加速
		Vector3 acceleration = {};
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
	
	acceleration.x += kAcceleration;

	} else if (Input::GetInstance()->PushKey(DIK_LEFT)){	
	
	acceleration.x -= kAcceleration;
	
	}
	
	// 加速、減速
	velocity_ += acceleration;

	} else {
	
	// 非入力時は減衰
	velocity_.x *= (1.0f - kAcceleration);
	
	}


	// 移動
	worldTransform_.translation_ += velocity_;

	// 行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}