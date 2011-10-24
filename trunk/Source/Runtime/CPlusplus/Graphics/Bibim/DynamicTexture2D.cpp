#include <Bibim/PCH.h>
#include <Bibim/DynamicTexture2D.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Assert.h>

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
        : Texture2D(graphicsDevice, width, height, width, height, pixelFormat),
          isLocked(false)
    {
        BBAssert(GetGraphicsDevice()->GetD3DDevice() != nullptr);

        D3DFORMAT d3dFormat = D3DFMT_UNKNOWN;
        switch (pixelFormat)
        {
            case Texture2D::A8R8G8B8Pixels:
                d3dFormat = D3DFMT_A8R8G8B8;
                break;
            case Texture2D::A8Pixels:
                d3dFormat = D3DFMT_A8;
                break;
        }

        IDirect3DTexture9* newD3DTexture = nullptr;
        HRESULT result = D3DXCreateTexture(GetGraphicsDevice()->GetD3DDevice(), width, height, 0, D3DUSAGE_DYNAMIC, d3dFormat, D3DPOOL_DEFAULT, &newD3DTexture);
        if (result == D3D_OK)
        {
            D3DSURFACE_DESC surfaceDesc;
            if (newD3DTexture->GetLevelDesc(0, &surfaceDesc) == D3D_OK)
                Setup(newD3DTexture, width, height, static_cast<int>(surfaceDesc.Width), static_cast<int>(surfaceDesc.Height), pixelFormat);
            else
                Setup(newD3DTexture, width, height, width, height, pixelFormat);
            
            IncreaseRevision();
            SetStatus(CompletedStatus);
        }
        else
        {
            IncreaseRevision();
            SetStatus(FaultStatus);
        }
    }

    DynamicTexture2D::~DynamicTexture2D()
    {
    }

    bool DynamicTexture2D::Lock(LockedInfo& outLockedInfo)
    {
        return Lock(outLockedInfo, Rect(0, 0, GetWidth(), GetHeight()));
    }

    bool DynamicTexture2D::Lock(LockedInfo& outLockedInfo, const Rect& Rect)
    {
        if (IsLocked())
            return false;

        D3DLOCKED_RECT lockInfo = { 0, };
        RECT d3dLockingRect = { Rect.GetLeft(), Rect.GetTop(), Rect.GetRight(), Rect.GetBottom() };

        HRESULT result = GetD3DTexture()->LockRect(0, &lockInfo, &d3dLockingRect, 0x00000000);
        if (result == D3D_OK)
        {
            outLockedInfo.SetData(this, lockInfo.pBits, static_cast<int>(lockInfo.Pitch));
            isLocked = true;
            return true;
        }
        else
            return false;
    }

    void DynamicTexture2D::Unlock(LockedInfo& outLockedInfo)
    {
        BBAssert(outLockedInfo.texture == this);

        if (IsLocked() == false)
            return;

        HRESULT result = GetD3DTexture()->UnlockRect(0);
        BBAssert(result == D3D_OK);

        isLocked = false;
        outLockedInfo.SetData(nullptr, nullptr, 0);
    }
}