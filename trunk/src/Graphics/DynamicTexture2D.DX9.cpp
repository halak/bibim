#include <Bibim/Config.h>
#if (defined(BIBIM_USE_DIRECTX9))

#include <Bibim/DynamicTexture2D.DX9.h>
#include <Bibim/Assert.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/GraphicsDevice.DX9.h>
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
          d3dSystemMemoryTexture(nullptr),
          d3dLockableTexture(nullptr),
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

        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();
        IDirect3DTexture9* newD3DTexture = nullptr;
        HRESULT result = D3D_OK;

        int sw = width;  // surface width
        int sh = height; // surface height
        if (GetGraphicsDevice()->GetD3DCaps().TextureCaps & D3DPTEXTURECAPS_POW2)
        {
            sw = Math::GetNearestPowerOfTwo(sw);
            sh = Math::GetNearestPowerOfTwo(sh);
        }

        if (GetGraphicsDevice()->GetD3DCaps().TextureCaps & D3DPTEXTURECAPS_SQUAREONLY)
        {
            if (sw > sh)
                sh = sw;
            else
                sw = sh;
        }

        if (GetGraphicsDevice()->GetD3DCaps().Caps2 & D3DCAPS2_DYNAMICTEXTURES)
        {
            result = d3dDevice->CreateTexture(sw, sh, 1, D3DUSAGE_DYNAMIC, d3dFormat, D3DPOOL_DEFAULT, &newD3DTexture, nullptr);
            d3dLockableTexture = newD3DTexture;
        }
        else
        {
            result = d3dDevice->CreateTexture(sw, sh, 1, 0, d3dFormat, D3DPOOL_SYSTEMMEM, &d3dSystemMemoryTexture, nullptr);
            result = d3dDevice->CreateTexture(sw, sh, 1, 0, d3dFormat, D3DPOOL_DEFAULT, &newD3DTexture, nullptr);
            d3dLockableTexture = d3dSystemMemoryTexture;
        }

        if (result == D3D_OK)
        {
            D3DSURFACE_DESC surfaceDesc;
            if (newD3DTexture->GetLevelDesc(0, &surfaceDesc) == D3D_OK)
                Setup(newD3DTexture, width, height, static_cast<int>(surfaceDesc.Width), static_cast<int>(surfaceDesc.Height), pixelFormat);
            else
                Setup(newD3DTexture, width, height, sw, sh, pixelFormat);
            
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
        CheckedRelease(d3dSystemMemoryTexture);
    }

    bool DynamicTexture2D::Lock(LockedInfo& outLockedInfo)
    {
        return Lock(outLockedInfo, Rect(0, 0, GetWidth(), GetHeight()));
    }

    bool DynamicTexture2D::Lock(LockedInfo& outLockedInfo, const Rect& rect)
    {
        if (IsLocked() || d3dLockableTexture == nullptr)
            return false;

        D3DLOCKED_RECT lockInfo = { 0, };
        RECT d3dLockingRect = { rect.GetLeft(), rect.GetTop(), rect.GetRight(), rect.GetBottom() };

        HRESULT result = d3dLockableTexture->LockRect(0, &lockInfo, &d3dLockingRect, 0x00000000);
        if (result == D3D_OK)
        {
            outLockedInfo.SetData(this, lockInfo.pBits, static_cast<int>(lockInfo.Pitch), rect);
            SetStatus(LoadingStatus);
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

        HRESULT result = d3dLockableTexture->UnlockRect(0);
        BBAssert(result == D3D_OK);

        if (d3dSystemMemoryTexture)
        {
            BBAssertDebug(d3dSystemMemoryTexture == d3dLockableTexture);
            GetGraphicsDevice()->GetD3DDevice()->UpdateTexture(d3dSystemMemoryTexture, GetHandle());
        }

        isLocked = false;
        SetStatus(CompletedStatus);
        outLockedInfo.SetData(nullptr, nullptr, 0, Rect::Empty);
    }

    void DynamicTexture2D::OnGraphicsDeviceLost(GraphicsDeviceBase* g)
    {
        CheckedRelease(d3dSystemMemoryTexture);
        Base::OnGraphicsDeviceLost(g);
    }
}

#endif