#include "titleSky.h"

void TitleSky::Initialize(Model* model, ViewProjection* viewProjection) {

worldTransform_.Initialize();
	model_ = model;
	viewProjection_ = viewProjection;

}

void TitleSky::Update() {}

void TitleSky::Draw() {

	//model_->Draw(worldTransform_, *viewProjection_);

}
