#pragma once
#include "GameScene.h"
#include "titleSky.h"
#include "ViewProjection.h"

class TitleScene {

public:

	TitleScene();

	~TitleScene();

void Initialize();

void Update();

void Draw();

bool IsFinished() const { return finished_; }

private:

// 終了フラグ
	bool finished_ = false;

	ViewProjection viewProjection_;

	TitleSky* titleSky_ = nullptr;

	Model* modelTitleSky_ = nullptr;

};