#include "GameScene.h"

// アフィン変換行列の作成
Matrix4x4 MakeAffinMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

// 行列の掛け算
Matrix4x4 MatrixMultiply(Matrix4x4& m1, Matrix4x4& m2);
