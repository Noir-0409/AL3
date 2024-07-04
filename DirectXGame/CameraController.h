#include <ViewProjection.h>

class CamereController {

public:

void Initialize();

void Update();

private:

// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

};