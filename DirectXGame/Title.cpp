#include "Title.h"
#include "Input.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {

	delete modelTitleSky_;
	delete titleSky_;

}

void TitleScene::Initialize() {

modelTitleSky_ = Model::CreateFromOBJ("titleSky", true);

titleSky_ = new TitleSky();

titleSky_->Initialize(modelTitleSky_, &viewProjection_);

worldTransform_.Initialize();

viewProjection_.Initialize();

}

void TitleScene::Update() {

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {

		finished_ = true;
	}

	titleSky_->Update();

}

void TitleScene::Draw() {

	titleSky_->Draw();





}
