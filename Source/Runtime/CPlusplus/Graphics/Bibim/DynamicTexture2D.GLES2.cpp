#include <Bibim/PCH.h>
#include <Bibim/DynamicTexture2D.GLES2.h>
#include <Bibim/Assert.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Math.h>

namespace Bibim
{
    DynamicTexture2D::LockedInfo::LockedInfo()
        : texture(),
          buffer(nullptr),
          pitch(0)
    {
    }

    DynamicTexture2D::LockedInfo::~LockedInfo()
    {
        if (texture && texture->IsLocked())
            texture->Unlock(*this);
    }

    void DynamicTexture2D::LockedInfo::SetData(DynamicTexture2D* texture, void* buffer, int pitch)
    {
        this->texture = texture;
        this->buffer = buffer;
        this->pitch = pitch;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    DynamicTexture2D::DynamicTexture2D(GraphicsDevice* graphicsDevice, int width, int height, PixelFormat pixelFormat)
        : Texture2D(graphicsDevice, width, height, width, height, pixelFormat)
    {
        SetStatus(FaultStatus);
    }

    DynamicTexture2D::~DynamicTexture2D()
    {
    }

    bool DynamicTexture2D::Lock(LockedInfo& /*outLockedInfo*/)
    {
        return false;
    }

    bool DynamicTexture2D::Lock(LockedInfo& /*outLockedInfo*/, const Rect& /*rect*/)
    {
        return false;
    }

    void DynamicTexture2D::Unlock(LockedInfo& /*outLockedInfo*/)
    {
    }
}