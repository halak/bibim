#include <Bibim/PCH.h>
#include <Bibim/DynamicTexture2D.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    DynamicTexture2D::Locker::Locker()
        : texture(),
          buffer(nullptr),
          pitch(0)
    {
    }

    DynamicTexture2D::Locker::~Locker()
    {
        if (texture && texture->IsLocked())
            texture->Unlock(*this);
    }

    void DynamicTexture2D::Locker::SetData(DynamicTexture2DPtr texture, void* buffer, int pitch)
    {
        this->texture = texture;
        this->buffer = buffer;
        this->pitch = pitch;
    }

    void* DynamicTexture2D::Locker::GetBuffer()
    {
        return buffer;
    }

    int DynamicTexture2D::Locker::GetPitch() const
    {
        return pitch;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    DynamicTexture2D::DynamicTexture2D(GraphicsDevice* graphicsDevice, int width, int height, PixelFormat format)
        : Texture2D(graphicsDevice),
          width(width),
          height(height),
          format(format),
          isLocked(false)
    {
    }

    DynamicTexture2D::~DynamicTexture2D()
    {
    }

    bool DynamicTexture2D::Lock(Locker& outLocker)
    {
        return Lock(outLocker, Rectangle(0, 0, GetWidth(), GetHeight()));
    }

    bool DynamicTexture2D::Lock(Locker& outLocker, const Rectangle& rectangle)
    {
        if (IsLocked())
            return false;

        D3DLOCKED_RECT lockInfo = { 0, };
        RECT d3dLockingRect = { rectangle.GetLeft(), rectangle.GetTop(), rectangle.GetRight(), rectangle.GetBottom() };

        HRESULT result = GetD3DTexture()->LockRect(0, &lockInfo, &d3dLockingRect, 0x00000000);
        if (result == D3D_OK)
        {
            outLocker.SetData(This<DynamicTexture2D>(), lockInfo.pBits, static_cast<int>(lockInfo.Pitch));
            isLocked = true;
            return true;
        }
        else
            return false;
    }

    void DynamicTexture2D::Unlock(Locker& outLocker)
    {
        BBAssert(outLocker.texture == this);

        if (IsLocked() == false)
            return;

        HRESULT result = GetD3DTexture()->UnlockRect(0);
        BBAssert(result == D3D_OK);

        isLocked = false;
        outLocker.SetData(nullptr, nullptr, 0);
    }

    bool DynamicTexture2D::IsLocked() const
    {
        return isLocked;
    }

    Texture2D::PixelFormat DynamicTexture2D::GetFormat() const
    {
        return format;
    }

    Texture2D::D3DTextureInfo DynamicTexture2D::CreateD3DTexture()
    {
        D3DFORMAT d3dFormat = D3DFMT_UNKNOWN;
        switch (GetFormat())
        {
            case Texture2D::ARGB32Pixels:
                d3dFormat = D3DFMT_A8R8G8B8;
                break;
            case Texture2D::A8Pixels:
                d3dFormat = D3DFMT_A8;
                break;
        }

        IDirect3DTexture9* newD3DTexture = NULL;
        HRESULT result = D3DXCreateTexture(GetGraphicsDevice()->GetD3DDevice(), width, height, 0, D3DUSAGE_DYNAMIC, d3dFormat, D3DPOOL_DEFAULT, &newD3DTexture);
        if (result == D3D_OK)
        {
            D3DSURFACE_DESC surfaceDesc;
            if (newD3DTexture->GetLevelDesc(0, &surfaceDesc) == D3D_OK)
            {
                return D3DTextureInfo(newD3DTexture, width, height,
                                      static_cast<int>(surfaceDesc.Width), static_cast<int>(surfaceDesc.Height));
            }
            else
                return D3DTextureInfo(newD3DTexture, width, height);
        }
        else
            return D3DTextureInfo();
    }
}