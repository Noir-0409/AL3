#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Player {

public:

void Initialize(Model* model,uint32_t playerHandle);

void Update();

void Draw();

private:

// ワールド変換データ
	WorldTransform worldTransform_;

// モデル
	Model* model_;

// プレイヤーのテクスチャハンドル
	uint32_t playerHandle_ = 0u;

};