#include "CameraController.h"
#include "Player.h"

void CameraController::Initialize() {

	// カメラビュープロジェクションの初期化
	cameraViewProjection_.Initialize();

}

void CameraController::Update() {

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	// 追従対象とオフセットからカメラの座標を計算
	cameraViewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;

	// 行列を更新
	cameraViewProjection_.UpdateMatrix();

}

void CameraController::Reset() {

// 追従対象のワールドトランスフォームを参照
const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

// 追従対象とオフセットからカメラの座標を計算
cameraViewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;

}
