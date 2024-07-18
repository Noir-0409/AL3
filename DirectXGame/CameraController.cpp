#define NOMINMAX

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
	targetPosition_ = targetWorldTransform.translation_ + targetOffset_;

	// 座標補間によりゆっくり追従
	cameraViewProjection_.translation_ =
	    Lerp(cameraViewProjection_.translation_, targetPosition_, kInterpolationRate_);

	// 移動範囲制限
	cameraViewProjection_.translation_.x =
	    std::max(cameraViewProjection_.translation_.x, movableArea_.left);
	cameraViewProjection_.translation_.x =
	    std::min(cameraViewProjection_.translation_.x, movableArea_.right);
	cameraViewProjection_.translation_.y =
	    std::max(cameraViewProjection_.translation_.x, movableArea_.bottom);
	cameraViewProjection_.translation_.y =
	    std::min(cameraViewProjection_.translation_.x, movableArea_.top);

	// 行列を更新
	cameraViewProjection_.UpdateMatrix();

}

void CameraController::Reset() {

// 追従対象のワールドトランスフォームを参照
const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

// 追従対象とオフセットからカメラの座標を計算
cameraViewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;

}
