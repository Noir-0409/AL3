#include "WorldTransform.h"
#include <Model.h>
#include "MapChipField.h"
#include "AB.h"

class Player;

class Enemy {

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

	void OnCollision(const Player* player);

	private:

		// ワールド変換データ
	    WorldTransform worldTransform_;
	    // モデル
	    Model* enemyModel_ = nullptr;

		ViewProjection* viewProjection_ = nullptr;

		// マップチップによるフィールド
	    MapChipField* mapChipField_ = nullptr;

		// 歩行の速さ
	    static inline const float kWalkSpeed = 0.04f;

		// 速度
	    Vector3 velocity_ = {};

		// 最初の角度
	    static inline const float kWalkMotionAngleStart = 0.0f;

		// 最後の角度
	    static inline const float kWalkMotionAngleEnd = 0.3f;

		// アニメーションの周期となる時間
	    static inline const float kWalkMotionTime =1.0f;

		// 経過時間
	    float walkTimer_ = 0.0f;
		
		// キャラクターの当たりサイズ
	    static inline const float kWidth = 0.8f;
	    static inline const float kHeight = 0.8f;


};