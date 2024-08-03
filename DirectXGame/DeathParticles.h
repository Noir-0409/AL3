#include <Model.h>
#include <array>

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

	// パーティクルの個数
	static inline const uint32_t kNumParticles = 8;

	std::array<WorldTransform, kNumParticles> worldTransforms_;

private:
	Model* particleModel_ = nullptr;           // パーティクルのモデル
	ViewProjection* viewProjection_ = nullptr; // ビュー・プロジェクションデータ
};