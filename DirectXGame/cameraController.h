#include <ViewProjection.h>
#include "MathUtilityForText.h"
//#include "Player.h"

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
	Vector3 targetOffset_ = {0, 0, -15.0f};

	// カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};

};

