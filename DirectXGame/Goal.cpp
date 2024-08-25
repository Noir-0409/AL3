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
