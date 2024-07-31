#include "GameScene.h"
#include "TextureManager.h"
#include "myMath.h"
#include <cassert>

GameScene::GameScene() {}



GameScene::~GameScene() {

	delete model_;

	delete modelBlock_;

	delete enemyModel_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}



	worldTransformBlocks_.clear();

	delete debugCamera_;

	// マップチップフィールドの解放
	delete mapChipField_;

	// 敵の解放
	for (Enemy* enemy : enemies_) {
	
		delete enemy;
	
	}

	enemies_.clear();

}

void GameScene::GenerateBlocks() {

	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更
	// 列数を設定
	worldTransformBlocks_.resize(numBlockVirtical);

	for (uint32_t i = 0; i < numBlockVirtical; ++i) {

		// 1列の要素数を設定
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {

			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {

				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ =
				    mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	 modelBlock_ = Model::CreateFromOBJ("block", true);
	model_ = Model::CreateFromOBJ("player",true);
	 enemyModel_ = Model::CreateFromOBJ("enemy", true);
	//textureHandle_ = TextureManager::Load("./Resources/block/block.png");
//	playerHandle_ = TextureManager::Load("./Resources./2.png");

	// 3Dモデルの生成
	//model_ = Model::Create();
	//modelBlock_ = Model::Create();

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/map.csv");

	// 自キャラの生成
	player_ = new Player();

	//enemy_ = new Enemy();

	//for (int32_t i = 0; i < 3; ++i) {
	//
	//Enemy* newEnemy = new Enemy();
	//
	//// 一体ずつ違う座標をセット
	//Vector3 enemyPosition;

	//newEnemy->Initialize(enemyModel_, &viewProjection_, enemyPosition);

	//enemies_.push_back(newEnemy);
	//
	//}

	Vector3 basePosition = {25.0f, 1.0f, 0.0f}; // 基準となる位置
	Vector3 offset = {3.0f, 3.0f, 0.0f};         // 各敵の間隔

	for (int32_t i = 0; i < 3; ++i) {
		Enemy* newEnemy = new Enemy();

		// 一体ずつ違う座標をセット
		Vector3 enemyPosition = basePosition + offset * static_cast<float>(i);

		newEnemy->Initialize(enemyModel_, &viewProjection_, enemyPosition);

		enemies_.push_back(newEnemy);
	}

	// 座標をマップチップ番号で固定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(10, 18);

	Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(20, 18);

	// 自キャラの初期化
	//player_->Initialize(model_, playerHandle_, &viewProjection_, playerPosition);
	player_->Initialize(model_, &viewProjection_, playerPosition);

	player_->SetMapChipField(mapChipField_);

	// 敵の初期化
	//enemy_->Initialize(enemyModel_, &viewProjection_, enemyPosition);

	//enemies_->SetMapChipField(mapChipField_);

	// カメラコントローラーの初期化
	// 生成
	cameraContoller_ = new CameraController();
	// 初期化
	cameraContoller_->Initialize();

	// 追従対象をセット
	cameraContoller_->SetTarget(player_);

	// リセット(瞬間合わせ)
	cameraContoller_->Reset();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	GenerateBlocks();

}

void GameScene::Update() {

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		if (isDebugCameraActive_ == true)
			isDebugCameraActive_ = false;
		else
			isDebugCameraActive_ = true;
	}
#endif

	// カメラ処理
	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();

		

	} else {

		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
		
		viewProjection_.matView = cameraContoller_->GetViewProjection().matView;
		viewProjection_.matProjection = cameraContoller_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();

	}

	// 自キャラの更新
	player_->Update();

	//enemy_->Update();

	 for (Enemy* enemy : enemies_) {
		enemy->Update();
	}

	// 縦横ブロック更新
	for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

			// アフィン変換行列の作成
			worldTransformBlockYoko->UpdateMatrix();
		}
	}

	// カメラコントローラーの更新
	cameraContoller_->Update();

	CameraController::Rect cameraArea_ = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	cameraContoller_->SetMovableArea(cameraArea_);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 3Dモデル描画
	//	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	// 自キャラの描画
		player_->Draw();

		// 敵の描画
		//enemy_->Draw();

		for (Enemy* enemy : enemies_) {
		enemy->Draw();
	    }


	// 縦横ブロック描画
	for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

			modelBlock_->Draw(*worldTransformBlockYoko, viewProjection_ );
		}
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


