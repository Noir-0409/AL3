#include <WorldTransform.h>
#include <Model.h>
#include "MapChipField.h"

class Goal {

public:

void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

void Update();

void Draw();

const WorldTransform& GetWorldTransform() const { return worldTransform_; }

void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* goalModel_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

};