#include "AABB.h"

AABB::AABB() {}

bool IsCollision(const AABB& aabb1, const AABB& aabb2) {

	// X²•ûŒü‚Ì”»’è
	if (aabb1.max_.x < aabb2.min_.x || aabb1.min_.x > aabb2.max_.x) {
		return false;
	}
	// Y²•ûŒü‚Ì”»’è
	if (aabb1.max_.y < aabb2.min_.y || aabb1.min_.y > aabb2.max_.y) {
		return false;
	}
	// Z²•ûŒü‚Ì”»’è
	if (aabb1.max_.z < aabb2.min_.z || aabb1.min_.z > aabb2.max_.z) {
		return false;
	}
	// ‘S‚Ä‚Ì²‚ÅŒğ·‚µ‚Ä‚¢‚éê‡
	return true;
}