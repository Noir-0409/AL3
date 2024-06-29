#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <algorithm>
#include <cassert>
#include <numbers>

class Player {
public:
	void Initialize(
	    Model* model, uint32_t playerHandle, ViewProjection* viewProjection,
	    const Vector3& position);
	void Update();
	void Draw();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t playerHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.05f;
	static inline const float kAttenuation = 0.95f;
	static inline const float kLimitRunSpeed = 1.0f;
	static inline const float kTimeTurn = 0.3f;

	enum class LRDirection {
		kRight,
		kLeft,
	};

	LRDirection lrDirection_ = LRDirection::kRight;
	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;
};

void Player::Initialize(
    Model* model, uint32_t playerHandle, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	model_ = model;
	playerHandle_ = playerHandle;
	viewProjection_ = viewProjection;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() {
	worldTransform_.TransferMatrix();

	Vector3 acceleration = {};

	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		if (velocity_.x < 0.0f) {
			velocity_.x *= (1.0f - kAttenuation);
		}
		acceleration.x += kAcceleration;

		if (lrDirection_ != LRDirection::kRight) {
			lrDirection_ = LRDirection::kRight;
			turnFirstRotationY_ = worldTransform_.rotation_.y;
			turnTimer_ = kTimeTurn;
		}
	}

	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		if (velocity_.x > 0.0f) {
			velocity_.x *= (1.0f - kAttenuation);
		}
		acceleration.x -= kAcceleration;

		if (lrDirection_ != LRDirection::kLeft) {
			lrDirection_ = LRDirection::kLeft;
			turnFirstRotationY_ = worldTransform_.rotation_.y;
			turnTimer_ = kTimeTurn;
		}
	}

	velocity_.x += acceleration.x;
	velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

	if (!Input::GetInstance()->PushKey(DIK_RIGHT) && !Input::GetInstance()->PushKey(DIK_LEFT)) {
		velocity_.x *= kAttenuation;
	}

	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.UpdateMatrix();

	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;

		float destinationRotationYTable[] = {
		    std::numbers::pi_v<float> / 2.0f,       // 右方向
		    std::numbers::pi_v<float> * 3.0f / 2.0f // 左方向
		};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		float t = 1.0f - (turnTimer_ / kTimeTurn);
		worldTransform_.rotation_.y = std::lerp(turnFirstRotationY_, destinationRotationY, t);
	} else {
		float destinationRotationYTable[] = {
		    std::numbers::pi_v<float> / 2.0f,       // 右方向
		    std::numbers::pi_v<float> * 3.0f / 2.0f // 左方向
		};
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		worldTransform_.rotation_.y = destinationRotationY;
	}
}

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_, playerHandle_); }
