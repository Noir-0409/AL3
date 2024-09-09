#include "Bullet.h"

void Bullet::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	
    bulletModel_ = model;

	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	for (auto& worldTransform : worldTransforms_) {

		worldTransform.Initialize();

		worldTransform.translation_ = position;
	}

}

void Bullet::Update() {}

void Bullet::Draw() {}
