#include <Bibim/PCH.h>
#include <Bibim/Vector4.h>

namespace Bibim
{
    const Vector4 Vector4::Zero  = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 Vector4::UnitX = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 Vector4::UnitY = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
    const Vector4 Vector4::UnitZ = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
    const Vector4 Vector4::UnitW = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    const Vector4 Vector4::One   = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}