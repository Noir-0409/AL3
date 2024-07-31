#include "WorldTransform.h"
#include <Model.h>
#include "MapChipField.h"

class Enemy {

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
	    Model* enemyModel_ = nullptr;

		ViewProjection* viewProjection_ = nullptr;

		// マップチップによるフィールド
	    MapChipField* mapChipField_ = nullptr;

		// 歩行の速さ
	    static inline const float kWalkSpeed = 0.05f;

		// 速度
	    Vector3 velocity_ = {};

};