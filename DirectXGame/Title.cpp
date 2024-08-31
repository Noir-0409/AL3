#include "Title.h"
#include "Input.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {

	delete modelTitleSky_;

}

void TitleScene::Initialize() {

modelTitleSky_ = Model::CreateFromOBJ("titleSky", true);

//titleSky_->Initialize(modelTitleSky_, &viewProjection_);

}

void TitleScene::Update() {

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {

		finished_ = true;
	}

}

void TitleScene::Draw() {

	//titleSky_->Draw();

}
