#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>

class Skydome {

public:

void Initialize();

void Update();

void Draw();

private:

// ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	// モデル
	Model* model_ = nullptr;

};