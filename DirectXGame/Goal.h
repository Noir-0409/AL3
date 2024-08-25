#include <WorldTransform.h>
#include <Model.h>
#include "MapChipField.h"

class Goal {

public:

void Initialize();

void Update();

void Draw();

private:

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* enemyModel_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;

};