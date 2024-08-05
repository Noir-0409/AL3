#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MapChipField.h"
#include "Player.h"
#include "CameraController.h"
#include "DeathParticle.h"

#include <vector>
#include <Enemy.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

	// ゲームのフェーズ
	enum class Phase {

		kPlay,  // ゲームプレイ
		kDeath, // デス演出

	};

	// ゲームの現在のフェーズ
	Phase phase_;

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// マップチップフィールド
	MapChipField* mapChipField_;

	void GenerateBlocks();

	// 全ての当たり判定を行う
	void CheckAllCollision();

	void ChangePhase();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// テクスチャハンドル
	//uint32_t textureHandle_ = 0;
//	uint32_t playerHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	Model* modelBlock_ = nullptr;
	Model* enemyModel_ = nullptr;
	Model* particleModel_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	
	// ビュープロジェクション
	ViewProjection viewProjection_;

	CameraController* cameraContoller_;

	// 自キャラ
	Player* player_ = nullptr;

	// 敵
	//Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemies_;

	// 縦横ブロック配列
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	DeathParticle* deathParticles_ = nullptr;

};