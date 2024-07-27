#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MapChipField.h"
#include "MathUtilityForText.h"

/// <summary>
/// 自キャラ
/// </summary>
/// 

class MapChipField;

class Player {

public:

	// 左右
	enum class LRDirection {

		kRight,
		kLeft,

	};

	// マップとの当たり判定情報
	struct CollisionMapInfo {

		bool ceiling = false;
		bool landing = false;
		bool hitwall = false;
		Vector3 move;

	};

	// 角
	enum Corner {

		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner // 要素数
		
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(
	    Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const Vector3& GetVelocity() const { return velocity_; }

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void InpuMove();

	void CheckMapCollision(CollisionMapInfo& info);

	void CheckMapCollisionUp(CollisionMapInfo& info);

	void CheckMapCollisionDown(CollisionMapInfo& info);

	//void CheckMapCollisionLeft(CollisionMapInfo& info);

	//void CheckMapCollisionRight(CollisionMapInfo& info);

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	void CollisionMove(const CollisionMapInfo& info);

	// 接地状態の切り替え
	void InputLanding(const CollisionMapInfo& info);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	// 加速度
	static inline const float kAcceleration = 0.07f;

	// 速度減衰率
	static inline const float kAttenuation = 0.3f;

	// 最大速度
	static inline const float kLimitRunSpeed = 0.1f;

	LRDirection lrDirection_ = LRDirection::kRight;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;

	// 旋回タイマー
	float turnTimer_ = 0.0f;

	// 旋回時間
	static inline const float kTimeTurn = 0.3f;

	// 接地状態フラグ
	bool onGround_ = true;

	// 重力加速度
	static inline const float kGravityAcceleration = 0.98f;

	// 最大落下速度
	static inline const float kLimitFallSpeed = 1.0f; 

	// ジャンプ初速
	static inline const float kJumpAcceleration = 20.0f;

	Vector3 velocity_ = {};

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// キャラクターの当たりサイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	static inline const float kBlank =0.04f;

	// 着地時の速度減衰率
	static inline const float kAttenuationLanding = 0.1f;

	// ずらすための定数
	static inline const float kShift = 0.01f;

};
