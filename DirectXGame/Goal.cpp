#include "Goal.h"
#include <cassert>

void Goal::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	assert(model);

	worldTransform_.Initialize();

	// 引数の内容をメンバ変数に記録
	goalModel_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;

}

void Goal::Update() {

	// 行列計算
	worldTransform_.UpdateMatrix();

}

void Goal::Draw() {

	goalModel_->Draw(worldTransform_, *viewProjection_);

}

Vector3 Goal::GetWorldPosition() { 

	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	// ワールド行列のTx
	worldPos.x = worldTransform_.translation_.x;

	// ワールド行列のTy
	worldPos.y = worldTransform_.translation_.y;

	// ワールド行列のTz
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;


}

AABB Goal::GetAABB() {

	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {
	    worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};

	aabb.max = {
	    worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;

}
