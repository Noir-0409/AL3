#include <Vector3.h>
#include <Matrix4x4.h>
#include <cmath>

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

// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
