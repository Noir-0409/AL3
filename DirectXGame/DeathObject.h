#include "Vector4.h"

class DeathObject {

public:

void Initialize();

void Update();

void Draw();

void SetColor(const Vector4& color);

void TransferMatrix();

private:

Vector4 color_;

};