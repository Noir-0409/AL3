#include "ViewProjection.h"
#include "MathUtilityForText.h"

// 前方宣言
class Player;

class CameraController {

	public:

	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	const ViewProjection& GetViewProjection() const { return cameraViewProjection_; }

	private:

	// カメラのビュープロジェクション
	ViewProjection cameraViewProjection_;

	// 追従対象
	Player* target_ = nullptr;

	// 追従対象とカメラ座標の差
	Vector3 targetOffset_ = {0, 0, -15.0f};

};

