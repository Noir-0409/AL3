#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t playerHandle) {

// NULLポインタチェック
	assert(model);

	playerHandle=playerHandle

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

}

void Player::Update() {}

void Player::Draw() {}
