#include "WorldTransform.h"
#include <Model.h>
#include <array>

class Bullet {

public:

void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

void Update();

void Draw();

private:

	Model* bulletModel_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	static inline const uint32_t kNumBullet = 1;

	std::array<WorldTransform, kNumBullet> worldTransforms_;

};