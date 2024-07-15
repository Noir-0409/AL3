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