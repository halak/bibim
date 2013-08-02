#include <Bibim/Config.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/RenderTargetTexture2D.GLES2.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/Assert.h>
#include <Bibim/CheckedRelease.h>

namespace Bibim
{
    RenderTargetTexture2D::RenderTargetTexture2D(GraphicsDevice* graphicsDevice, int width, int height)
        : Texture2D(graphicsDevice, width, height, width, height, A8R8G8B8Pixels)
    {
        SetStatus(FaultStatus);
    }

    RenderTargetTexture2D::~RenderTargetTexture2D()
    {
    }
}

#endif