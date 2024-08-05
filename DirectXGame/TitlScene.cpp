#include "TitlScene.h"
#include <Input.h>

void TitleScene::Intialize() {}

void TitleScene::Update() {

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
	
	finished_ = false;
	
	}

}

void TitleScene::Draw() {}
