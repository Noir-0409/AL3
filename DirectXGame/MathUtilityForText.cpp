#include "MathUtilityForText.h"

// Vector3の足し算
Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {

	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;

	return lhv;
}

const Vector3 operator+(const Vector3& v1, const Vector3& v2) {

	Vector3 temp(v1);
	return temp += v2;
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {

	Vector3 result;
	result.x = v1.x + t * (v2.x - v1.x);
	result.y = v1.y + t * (v2.y - v1.y);
	result.z = v1.z + t * (v2.z - v1.z);
	return result;
}

// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {

	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

Vector3 operator*(float s, const Vector3& v) { return Multiply(s, v); }

Vector3 operator*(const Vector3& v, float s) { return s * v; }