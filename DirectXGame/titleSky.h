#include <WorldTransform.h>
#include <Model.h>
#include <ViewProjection.h>

class TitleSky {

public:

	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();

private:

WorldTransform worldTransform_;

ViewProjection* viewProjection_ = nullptr;

Model* model_ = nullptr;

};