#include <Bibim/PCH.h>
#include <Bibim/Matrix4.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   include <d3dx9math.h>

    namespace Bibim
    {
        Matrix4 Matrix4::Inversion(const Matrix4& value)
        {
            D3DXMATRIX result;
            D3DXMatrixInverse(&result, NULL, reinterpret_cast<const D3DXMATRIX*>(&value.M00));
            return Matrix4(static_cast<const float*>(result));
        }
    }

#endif