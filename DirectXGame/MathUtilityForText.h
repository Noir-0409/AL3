#include <Vector3.h>

// Vector3の足し算
Vector3& operator+=(Vector3& lhv, const Vector3& rhv);

const Vector3 operator+(const Vector3& v1, const Vector3& v2);

Vector3& operator-=(Vector3& lhv, const Vector3& rhv);

const Vector3 operator-(const Vector3& v1, const Vector3& v2);

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);

Vector3 operator*(float s, const Vector3& v); 

Vector3 operator*(const Vector3& v, float s);

struct AABB {

	Vector3 min;
	Vector3 max;
};

bool IsCollision(const AABB& aabb1, const AABB& aabb2);