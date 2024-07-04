#include <ViewProjection.h>
#include "Player.h"

class CamereController {

public:

void Initialize();

void Update();

void SetTarget(Player* target) { target_ = target; }

void Reset();

private:

// ビュープロジェクション
	ViewProjection viewProjection_;

	Player* target_ = nullptr;

	// 追従対象とカメラ座標の差(オフセット)
	Vector3 targetOffset = {0, 0, -15.0f};

};

// 前方宣言
class Player;