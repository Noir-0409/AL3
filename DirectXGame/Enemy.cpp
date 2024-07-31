#include "Enemy.h"
#include <cassert>
#include <numbers>

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	assert(model);

	worldTransform_.Initialize();

	// 引数の内容をメンバ変数に記録
	enemyModel_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;
	

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.0f;
}

void Enemy::Update() {

	// 行列計算
	worldTransform_.UpdateMatrix();

}

void Enemy::Draw() {

	enemyModel_->Draw(worldTransform_, *viewProjection_);

}
