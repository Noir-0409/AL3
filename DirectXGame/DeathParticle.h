#include <ViewProjection.h>
#include <Model.h>
#include "MathUtilityForText.h"
#include "Vector4.h"
#include <DeathObject.h>
#include <algorithm>

class DeathParticle {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	private:

	Model* particleModel_ = nullptr;           // パーティクルのモデル
	ViewProjection* viewProjection_ = nullptr; // ビュー・プロジェクションデータ

	// パーティクルの個数
	static inline const uint32_t kNumParticles = 8;

	std::array<WorldTransform, kNumParticles> worldTransforms_;

	// 存続時間
	static inline const float kDuration = 1.0f;

	// 移動の速さ
	static inline const float kSpeed = 0.1f;

	// 分割した1個分の角度
	static inline const float kAngleUint = 2.0f * 3.14f / 8.0f;

	// 終了フラグ
	bool isFinished_ = false;

	// 経過時間カウント
	float counter_ = 0.0f;

	// 色変更オブジェクト
	DeathObject objectColor_;

	// 色の数値
	Vector4 color_;

};