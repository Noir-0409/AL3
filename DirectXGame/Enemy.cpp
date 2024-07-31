#include "Enemy.h"
#include <cassert>
#include <numbers>
#include "MathUtilityForText.h"

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	assert(model);

	worldTransform_.Initialize();

	// 引数の内容をメンバ変数に記録
	enemyModel_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;
	
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.0f;

	// 速度を設定
	velocity_ = {-kWalkSpeed, 0, 0};

	walkTimer_ = 0.0f;

}

void Enemy::Update() {

	 // 移動
	worldTransform_.translation_ += velocity_;

	// タイマーを加算
	walkTimer_ += 1.0f / 60.0f; 

	float t = std::fmod(walkTimer_, kWalkMotionTime) / kWalkMotionTime;

	// 回転アニメーション
	float param = std::sin(t * 2.0f * std::numbers::pi_v<float>);

	// 回転角度を計算
	float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	
	worldTransform_.rotation_.x = radian;

	// 行列計算
	worldTransform_.UpdateMatrix();

}

void Enemy::Draw() {

	enemyModel_->Draw(worldTransform_, *viewProjection_);

}
