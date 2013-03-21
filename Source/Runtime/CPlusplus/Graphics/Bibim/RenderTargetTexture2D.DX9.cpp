#include <Bibim/PCH.h>
#include <Bibim/RenderTargetTexture2D.DX9.h>
#include <Bibim/GraphicsDevice.DX9.h>
#include <Bibim/Assert.h>
#include <Bibim/CheckedRelease.h>

namespace Bibim
{
    RenderTargetTexture2D::RenderTargetTexture2D(GraphicsDevice* graphicsDevice, int width, int height)
        : Texture2D(graphicsDevice, width, height, width, height, A8R8G8B8Pixels),
          d3dSurface(nullptr)
    {
        BBAssert(GetGraphicsDevice()->GetD3DDevice() != nullptr);

        IDirect3DTexture9* newD3DTexture = nullptr;
        HRESULT result = D3DXCreateTexture(GetGraphicsDevice()->GetD3DDevice(), width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &newD3DTexture);
        if (result == D3D_OK)
        {
            D3DSURFACE_DESC surfaceDesc;
            if (newD3DTexture->GetLevelDesc(0, &surfaceDesc) == D3D_OK)
                Setup(newD3DTexture, width, height, static_cast<int>(surfaceDesc.Width), static_cast<int>(surfaceDesc.Height), A8R8G8B8Pixels);
            else
                Setup(newD3DTexture, width, height, width, height, A8R8G8B8Pixels);

            newD3DTexture->GetSurfaceLevel(0, &d3dSurface);
            
            IncreaseRevision();
            SetStatus(CompletedStatus);
        }
        else
        {
            IncreaseRevision();
            SetStatus(FaultStatus);
        }
    }

    RenderTargetTexture2D::~RenderTargetTexture2D()
    {
        CheckedRelease(d3dSurface);
    }

    void RenderTargetTexture2D::OnGraphicsDeviceLost(GraphicsDeviceBase* g)
    {
        CheckedRelease(d3dSurface);
        Base::OnGraphicsDeviceLost(g);
    }
}