#pragma once

class TitleScene {

public:

	void Intialize();

	void Update();

	void Draw();

 	bool IsFinished() const { return finished_; }

private:

// 終了フラグ
	bool finished_ = false;

};