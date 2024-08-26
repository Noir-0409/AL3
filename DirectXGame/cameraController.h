#include "MathUtilityForText.h"
#include <ViewProjection.h>
// #include "Mymath.h"

// 前方宣言
class Player;

class CameraController {

public:
	// 矩形
	struct Rect {

		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};

	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	const ViewProjection& GetViewProjection() const { return cameraViewProjection_; }

	void SetMovableArea(Rect area) { movableArea_ = area; }

private:
	// 追従対象
	Player* target_ = nullptr;

	// カメラのビュープロジェクション
	ViewProjection cameraViewProjection_;

	// 追従対象とカメラ座標の差
	Vector3 targetOffset_ = {0, 0, -22.0f};

	// カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};

	// カメラの目標座標
	Vector3 targetPosition_;

	// 座標補間割合
	static inline const float kInterpolationRate_ = 0.3f;

	// 速度掛け率
	static inline const float kVeloicityBias = 0.5f;

	// 追従対象の各方向へのカメラ移動範囲
	static inline const Rect margin_ = {-8.0f, 8.0f, -8.0f, 8.0f};
};
