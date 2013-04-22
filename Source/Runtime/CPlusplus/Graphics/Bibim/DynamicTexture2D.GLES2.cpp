#include <Bibim/Config.h>
#include <Bibim/DynamicTexture2D.GLES2.h>
#include <Bibim/Assert.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/Log.h>
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

    void DynamicTexture2D::LockedInfo::SetData(DynamicTexture2D* texture, void* buffer, int pitch, Rect rect)
    {
        this->texture = texture;
        this->buffer = buffer;
        this->pitch = pitch;
        this->rect = rect;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    DynamicTexture2D::DynamicTexture2D(GraphicsDevice* graphicsDevice, int width, int height, PixelFormat pixelFormat)
        : Texture2D(graphicsDevice, width, height, width, height, pixelFormat),
          pitch(0),
          isLocked(false),
          dirtyRect(Rect::Empty)
    {
        const int sw = Math::Max(Math::GetNearestPowerOfTwo(width), Math::GetNearestPowerOfTwo(height));  // surface width
        const int sh = sw; // surface height

        const int bytesPerPixel = GetBytesPerPixel(pixelFormat);
        pitch = sw * bytesPerPixel;
        surface.resize(pitch * sh);

        GLuint textureHandle = 0;
        GLint glesFormat = GetGLESPixelFormat(pixelFormat);
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &textureHandle);
        glBindTexture(GL_TEXTURE_2D, textureHandle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, glesFormat, sw, sh, 0, glesFormat, GL_UNSIGNED_BYTE, &surface[0]);

        Setup(textureHandle, width, height, sw, sh, pixelFormat);
        IncreaseRevision();
        SetStatus(CompletedStatus);
    }

    DynamicTexture2D::~DynamicTexture2D()
    {
    }

    bool DynamicTexture2D::Lock(LockedInfo& outLockedInfo)
    {
        return Lock(outLockedInfo, Rect(0, 0, GetWidth(), GetHeight()));
    }

    bool DynamicTexture2D::Lock(LockedInfo& outLockedInfo, const Rect& rect)
    {
        if (IsLocked())
            return false;
        if (Rect::Intersect(rect, Rect(0, 0, GetWidth(), GetHeight())) != rect)
            return false;

        const int bytesPerPixel = GetBytesPerPixel(GetPixelFormat());
        outLockedInfo.SetData(this, &surface[(rect.X * bytesPerPixel) + (rect.Y * pitch)], pitch, rect);
        SetStatus(LoadingStatus);
        isLocked = true;

        return true;
    }

    void DynamicTexture2D::Unlock(LockedInfo& outLockedInfo)
    {
        BBAssert(outLockedInfo.texture == this);

        if (IsLocked() == false)
            return;

        const Rect lockedRect = outLockedInfo.GetRect();

        if (dirtyRect.IsEmpty())
            dirtyRect = lockedRect;
        else
            dirtyRect = Rect::Union(dirtyRect, lockedRect);

        isLocked = false;
        SetStatus(CompletedStatus);
        outLockedInfo.SetData(nullptr, nullptr, 0, Rect::Empty);
    }

    GLuint DynamicTexture2D::GetHandle()
    {
        if (dirtyRect.IsEmpty() == false)
        {
            GLint glesFormat = GetGLESPixelFormat(GetPixelFormat());
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, Base::GetHandle());
            glTexSubImage2D(GL_TEXTURE_2D,
                            0,
                            0,
                            dirtyRect.Y,
                            GetSurfaceWidth(),
                            dirtyRect.Height,
                            glesFormat,
                            GL_UNSIGNED_BYTE,
                            &surface[dirtyRect.Y * pitch]);

            dirtyRect = Rect::Empty;
        }

        return Base::GetHandle();
    }
}