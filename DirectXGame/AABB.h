#pragma once
#include <Vector3.h>

class AABB {

public:

AABB();

bool IsCollision(const AABB& aabb1, const AABB& aabb2);

Vector3 min_;

Vector3 max_;

private:

};