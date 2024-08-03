#include "MathUtilityForText.h"

// Vector3の足し算
Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {

	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;

	return lhv;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2) {

	Vector3 temp(v1);
	return temp -= v2;
}

Vector3& operator-=(Vector3& lhv, const Vector3& rhv) {

	lhv.x -= rhv.x;
	lhv.y -= rhv.y;
	lhv.z -= rhv.z;

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

Matrix4x4 MakeRotateZMatrix(float radian) { 

	Matrix4x4 rotateZMatrix;

	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);

	// Z軸周りの回転行列の生成
	rotateZMatrix.m[0][0] = cosTheta;
	rotateZMatrix.m[0][1] = sinTheta;
	rotateZMatrix.m[0][2] = 0.0f;
	rotateZMatrix.m[0][3] = 0.0f;

	rotateZMatrix.m[1][0] = -sinTheta;
	rotateZMatrix.m[1][1] = cosTheta;
	rotateZMatrix.m[1][2] = 0.0f;
	rotateZMatrix.m[1][3] = 0.0f;

	rotateZMatrix.m[2][0] = 0.0f;
	rotateZMatrix.m[2][1] = 0.0f;
	rotateZMatrix.m[2][2] = 1.0f;
	rotateZMatrix.m[2][3] = 0.0f;

	rotateZMatrix.m[3][0] = 0.0f;
	rotateZMatrix.m[3][1] = 0.0f;
	rotateZMatrix.m[3][2] = 0.0f;
	rotateZMatrix.m[3][3] = 1.0f;

	return rotateZMatrix;

}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {

		// 変換後のベクトル
		Vector3 transformedVector;
		transformedVector.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] +
		                      vector.z * matrix.m[2][0] + matrix.m[3][0];
		transformedVector.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] +
		                      vector.z * matrix.m[2][1] + matrix.m[3][1];
		transformedVector.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] +
		                      vector.z * matrix.m[2][2] + matrix.m[3][2];

		// ベクトルの4番目の成分が1でない場合、正規化する
		float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] +
		          vector.z * matrix.m[2][3] + matrix.m[3][3];
		if (w != 0.0f) {
			transformedVector.x /= w;
			transformedVector.y /= w;
			transformedVector.z /= w;
		}

		return transformedVector;
	
}
