#pragma once
#include "Vector3.h"

class AABB {
public:
	Vector3 min;
	Vector3 max;

	static bool IsCollision(const AABB& aabb1, const AABB& aabb2);
};