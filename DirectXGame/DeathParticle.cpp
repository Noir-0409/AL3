#include "DeathParticle.h"

void DeathParticle::Initialize(
    Model* model, ViewProjection* viewProjection, const Vector3& position) {

    particleModel_ = model;

	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	for (auto& worldTransform : worldTransforms_) {

		worldTransform.Initialize();

		worldTransform.translation_ = position;
	}

}

void DeathParticle::Update() {

	// ワールド座標の更新
	for (auto& worldTransform : worldTransforms_) {

		worldTransform.UpdateMatrix();
	}

}

void DeathParticle::Draw() {

	for (const auto& worldTransform : worldTransforms_) {

		particleModel_->Draw(worldTransform, *viewProjection_);
	}

}
