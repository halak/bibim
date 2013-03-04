#include <Bibim/PCH.h>
#include <Bibim/UIRendererBase.h>
#include <Bibim/Texture2D.h>

namespace Bibim
{
    UIRendererBase::UIRendererBase()
    {
    }

    UIRendererBase::~UIRendererBase()
    {
    }

    UIRendererBase::PixelMode UIRendererBase::GetPixelMode(const Texture2D* texture, const Texture2D* mask)
    {
        if (texture)
        {
            if (texture->GetPixelFormat() == Texture2D::A8Pixels)
            {
                if (mask)
                    return MaskedAlphaTextureMode;
                else
                    return AlphaTextureOnlyMode;
            }
            else
            {
                if (mask)
                    return MaskedColorTextureMode;
                else
                    return ColorTextureOnlyMode;
            }
        }
        else
        {
            if (mask)
                return MaskedColorMode;
            else
                return ColorOnlyMode;
        }
    }


    const char* UIRendererBase::GetShaderEffectSuffix(PixelMode mode)
    {
        switch (mode)
        {
            case ColorOnlyMode:
                return "_A";
            case ColorTextureOnlyMode:
                return "_B";
            case AlphaTextureOnlyMode:
                return "_C";
            case MaskedColorMode:
                return "_A";
            case MaskedColorTextureMode:
                return "_B";
            case MaskedAlphaTextureMode:
                return "_C";
            default:
                return nullptr;
        }
    }
}