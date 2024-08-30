#include <WorldTransform.h>
#include <Model.h>

class TitleSky {

public:

	void Initialize();

	void Update();

	void Draw();

private:

WorldTransform worldTransform_;

Model* model_ = nullptr;

};