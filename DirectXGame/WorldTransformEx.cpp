#include "WorldTransform.h"
#include <GameScene.cpp>
#include <myMath2.h>

// スケール、回転、平行移動を合成して行列を計算
void WorldTransform::UpdateMatrix() {

// スケール、回転、平行移動を合成して行列を計算
	matWorld_ = MakeAffinMatrix(scale_, rotation_, translation_);

	TransferMatrix();

}