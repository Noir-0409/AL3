#define NOMINMAX

#include "Player.h"
#include "MapChipField.h"
#include <DebugText.h>
#include <Input.h>
#include <algorithm>
#include <cassert>
#include <numbers>
#include "ImGuiManager.h"

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	// NULLチェック
	assert(model);

	worldTransform_.Initialize();

	// 引数の内容をメンバ変数に記録
	model_ = model;
	// textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() {

	InpuMove();

	// 衝突情報を初期化
	CollisionMapInfo collisionMapInfo;

	// 移動量に速度を値をコピー
	collisionMapInfo.move = velocity_;
	collisionMapInfo.landing = false;
	collisionMapInfo.hitwall = false;

	// マップ衝突チェック
	CheckMapCollision(collisionMapInfo);

	CollisionMove(collisionMapInfo);

	UpdateOnGround(collisionMapInfo);

	UpdateHitWall(collisionMapInfo);

	// 行列計算
	worldTransform_.UpdateMatrix();

	ImGui::Begin("onGround");
	ImGui::Checkbox("onGround_", &onGround_);
	ImGui::End();

}

void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}

void Player::InpuMove() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// 移動入力

	// 接地状態
	if (onGround_) {

		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

				// 左移動中の右入力
				if (velocity_.x < 0.0f) {

					// 速度と逆方向に入力中はブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x += kAcceleration;

				if (lrDirection_ != LRDirection::kRight) {

					lrDirection_ = LRDirection::kRight;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーに時間を設定
					turnTimer_ = kTimeTurn;
				}

			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {

				// 右移動中の左入力
				if (velocity_.x > 0.0f) {

					// 速度と逆方向に入力中はブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x -= kAcceleration;

				if (lrDirection_ != LRDirection::kLeft) {

					lrDirection_ = LRDirection::kLeft;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーに時間を設定
					turnTimer_ = kTimeTurn;
				}
			}

			// 加速、減速
			velocity_ += acceleration;

			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {

			// 非入力時は減衰
			velocity_.x *= (1.0f - kAcceleration);
		}

		// 旋回制御
		if (turnTimer_ > 0.0f) {

			// 旋回タイマーをカウントダウン
			turnTimer_ -= 1.0f / 60.0f;

			// 左右の自キャラの角度テーブル
			float destinationRotationYTable[] = {

			    std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f

			};

			// 状態に応じた角度を取得
			float destinationRotationY =
			    destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

			// 自キャラの角度を設定
			worldTransform_.rotation_.y = destinationRotationY;

			float t = 1.0f - (turnTimer_ / kTimeTurn);

			worldTransform_.rotation_.y = std::lerp(turnFirstRotationY_, destinationRotationY, t);

		} else {

			float destinationRotationYTable[] = {

			    std::numbers::pi_v<float> / 2.0f,       // 右方向
			    std::numbers::pi_v<float> * 3.0f / 2.0f // 左方向

			};

			float destinationRotationY =
			    destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

			worldTransform_.rotation_.y = destinationRotationY;
		}

		// 移動
		worldTransform_.translation_ += velocity_;

		if (Input::GetInstance()->PushKey(DIK_UP)) {

			// ジャンプ初速
			velocity_ += Vector3(0, kJumpAcceleration / 60.0f, 0);
		}

		// ジャンプ開始
		if (velocity_.y > 0.0f) {

			onGround_ = false;
		}

		// 空中
	} else {

		// 落下速度
		velocity_ += Vector3(0, -kGravityAcceleration / 60, 0);

		worldTransform_.translation_ += Vector3(velocity_);

		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

	}

}

void Player::CheckMapCollision(CollisionMapInfo& info) {

	CheckMapCollisionUp(info);
	CheckMapCollisionDown(info);
	CheckMapCollisionLeft(info);
	CheckMapCollisionRight(info);

	 ImGui::Begin("hit");
	 ImGui::Checkbox("hitwall", &info.hitwall);
	 ImGui::Checkbox("landing", &info.landing);
	 ImGui::Checkbox("ceiling", &info.ceiling);
	 ImGui::End();

}

void Player::CheckMapCollisionUp(CollisionMapInfo& info) {

	// 上昇あり？
	if (info.move.y <= 0) {

		return;
	}

	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {

		positionsNew[i] =
		    CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipType mapChipType;

	// 真上の判定
	bool hit = false;

	// 左上の判定
	MapChipField::IndexSet indexSet;

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);

	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {

		hit = true;
	}

	// 右上の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);

	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {

		hit = true;
	}

	// ブロックにヒット？
	if (hit) {

		// めり込みを排除する方向に移動量を設定
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(
		    worldTransform_.translation_ + Vector3(0, kHeight / 2.0f, 0));

		// めり込み先ブロックの範囲矩形
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);

		// 移動量
		info.move.y = std::max(
		    0.0f, rect.bottom - worldTransform_.translation_.y - (kHeight / 2.0f + kBlank));

		info.ceiling = true;
	}

	// 天井に当たった？
	if (info.ceiling) {

		velocity_.y = 0;
	}
}

void Player::CheckMapCollisionDown(CollisionMapInfo& info) {

	// 下降あり？
	if (info.move.y >= 0) {

		return;
	}

	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {

		positionsNew[i] =
		    CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipType mapChipType;

	// 真下の判定
	bool hit = false;

	// 左下の判定
	MapChipField::IndexSet indexSet;

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);

	mapChipType =
	    mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex );

	if (mapChipType == MapChipType::kBlock) {

		hit = true;
	}

	// 右下の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);

	mapChipType =
	    mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex );

	if (mapChipType == MapChipType::kBlock) {

		hit = true;
	}

	// ブロックにヒット？
	if (hit) {

		// めり込みを排除
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(
		    worldTransform_.translation_ + Vector3(0, kHeight / 2.0f, 0));

		// めり込み先ブロックの範囲矩形
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);

		info.move.y =
		    std::min(0.0f, rect.top - worldTransform_.translation_.y - (kHeight / 2.0f + kBlank));

		info.landing = true;
	}

}

 void Player::CheckMapCollisionLeft(CollisionMapInfo& info) {
	 
	  // 左移動あり？
	if (info.move.x >= 0.0f) {

		return;
	}

	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {

		positionsNew[i] =
		    CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipType mapChipType;

	MapChipType mapChipTypeNext;

	// 左の判定
	bool hit = false;

	MapChipField::IndexSet indexSet;

	// 左上の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);

	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex + 1, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {

		hit = true;
	}

	// 左下の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);

	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex + 1, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {

		hit = true;
	}

	// ブロックにヒット？
	if (hit) {

		// 現在座標が壁の外か判定
		MapChipField::IndexSet indexSetNow;

		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(
		    worldTransform_.translation_ + Vector3(kWidth / 2.0f, 0, 0));

		if (indexSetNow.xIndex != indexSet.xIndex) {

			// めり込みを排除
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(
			    worldTransform_.translation_ + info.move + Vector3(kWidth / 2.0f, 0, 0));

			MapChipField::Rect rect =
			    mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);

			info.move.x = std::min(
			    0.0f, rect.right - worldTransform_.translation_.x + (kWidth / 2.0f + kBlank));

			info.hitwall = true;

		} else {

			info.hitwall = false;
		}
	}
	
	  }

void Player::CheckMapCollisionRight(CollisionMapInfo& info) {

	// 右移動あり？
	if (info.move.x <= 0.0f) {

		return;
	}

	// 移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {

		positionsNew[i] =
		    CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipType mapChipType;

	MapChipType mapChipTypeNext;

	// 右の判定
	bool hit = false;

	MapChipField::IndexSet indexSet;

	// 右上の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);

	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex - 1, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {

		hit = true;
	}

	// 右下の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);

	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex - 1, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {

		hit = true;
	}

	// ブロックにヒット？
	if (hit) {

		// 現在座標が壁の外か判定
		MapChipField::IndexSet indexSetNow;

		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(
		    worldTransform_.translation_ + Vector3(-kWidth / 2.0f, 0, 0));

		if (indexSetNow.xIndex != indexSet.xIndex) {

			// めり込みを排除
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(
			    worldTransform_.translation_ + info.move + Vector3(-kWidth / 2.0f, 0, 0));

			MapChipField::Rect rect =
			    mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);

			info.move.x = std::max(
			    0.0f, rect.left - worldTransform_.translation_.x - (-kWidth / 2.0f + kBlank));

			info.hitwall = true;

		} else {

			info.hitwall = false;
		}
	}

}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {

	Vector3 offsetTable[kNumCorner] = {

	    {+kWidth / 2.0f, -kHeight / 2.0f, 0},
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0},
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0},
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0},
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}

void Player::CollisionMove(const CollisionMapInfo& info) {

	// 移動
	worldTransform_.translation_ += info.move;
}

void Player::UpdateOnGround(const CollisionMapInfo& info) {

	// 自キャラが接地状態？
	if (onGround_) {

		// ジャンプ開始
		if (velocity_.y > 0.0f) {

			onGround_ = false;
		} else {

			// 移動後の4つの角の座標
			std::array<Vector3, kNumCorner> positionsNew;

			for (uint32_t i = 0; i < positionsNew.size(); ++i) {

				positionsNew[i] = CornerPosition(
				    worldTransform_.translation_ + info.move, static_cast<Corner>(i));
			}

			MapChipType mapChipType;

			// 真下の判定
			bool hit = false;

			// 左下の判定
			MapChipField::IndexSet indexSet;

			indexSet = mapChipField_->GetMapChipIndexSetByPosition(
			    positionsNew[kLeftBottom] + Vector3(0, -kGroundSearchHeight, 0));

			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

			if (mapChipType == MapChipType::kBlock) {

				hit = true;
			}

			// 右下の判定
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(
			    positionsNew[kRightBottom] + Vector3(0, -kGroundSearchHeight, 0));

			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

			if (mapChipType == MapChipType::kBlock) {

				hit = true;
			}

			// 落下開始
			if (!hit) {

				onGround_ = false;
			}
		}

	} else {

		// 着地フラグ
		if (info.landing) {

			// 着地状態に切り替える
			onGround_ = true;

			// 着地時にX速度を減衰
			velocity_.x *= (1.0f - kAttenuationLanding);

			// Y速度を0にする
			velocity_.y = 0.0f;
		}
	}
}

void Player::UpdateHitWall(const CollisionMapInfo& info) {

// 壁接触による減速
	if (info.hitwall) {

	//velocity_.x *= 0.0f;
	
	velocity_.x *= (1.0f - kAttenuationWall);

	}

}

Vector3 Player::GetWorldPosition() { 

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

AABB Player::GetAABB() {

Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {
	    worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};

	aabb.max = {
	    worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;

}
