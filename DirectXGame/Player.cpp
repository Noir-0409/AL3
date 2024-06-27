#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	// NULLチェック
	assert(model);

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// 引数の内容をメンバ変数に記録
	model_ = model;
	//textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

}

void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}