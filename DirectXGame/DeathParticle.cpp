#include "DeathParticle.h"
#include <imgui.h>

void DeathParticle::Initialize(
    Model* model, ViewProjection* viewProjection, const Vector3& position) {

    particleModel_ = model;

	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	for (auto& worldTransform : worldTransforms_) {

		worldTransform.Initialize();

		worldTransform.translation_ = position;
	}

	objectColor_.Initialize();

	color_ = {1, 1, 1, 1};

}

void DeathParticle::Update() {

	ImGui::Begin("DeathParticle");
	ImGui::Checkbox("death", &isFinished_);
	ImGui::End();

		// 終了なら何もしない
	if (isFinished_) {

		return;
	}


	// ワールド座標の更新
	for (auto& worldTransform : worldTransforms_) {

		worldTransform.UpdateMatrix();
	}

	for (uint32_t i = 0; i < 8; ++i) {
	
	// 基本となる速度ベクトル
		Vector3 velocity = {kSpeed, 0, 0};

		// 回転角を計算
		float angle = kAngleUint * i;

		// Z軸まわり回転行列
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);

		// 基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, matrixRotation);

		// 移動処理
		worldTransforms_[i].translation_ += velocity;
	
	}

	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
	
		counter_ = kDuration;

		// 終了扱いにする
		isFinished_ = true;
	
	}

	// counter_が0のときに、アルファ値が1.0,存続時間ピッタリのときに0.0にする
	color_.w = std::clamp(1.0f - (counter_ / kDuration), 0.0f, 1.0f);

	// 色変更オブジェクトに色の数値を設定
	objectColor_.SetColor(color_);

	// 色変更オブジェクトをVRAMに転送
	objectColor_.TransferMatrix();

}

void DeathParticle::Draw() {

	// 終了なら何もしない
	if (isFinished_) {

		return;
	}

	for (const auto& worldTransform : worldTransforms_) {

		particleModel_->Draw(worldTransform, *viewProjection_);
	}

}
