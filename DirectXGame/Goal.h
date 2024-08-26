#include <WorldTransform.h>
#include <Model.h>
#include "MapChipField.h"
#include "AB.h"

class Goal {

public:

void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

void Update();

void Draw();

const WorldTransform& GetWorldTransform() const { return worldTransform_; }

void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

// ワールド座標を取得
Vector3 GetWorldPosition();

// AABBを取得
AABB GetAABB();


private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* goalModel_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// キャラクターの当たりサイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

};