#include <Bibim/Config.h>
#if (defined(BIBIM_USE_DIRECTX9))

#include <Bibim/UIRenderer.DX9.h>
#include <Bibim/Assert.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BlendMode.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Color.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.DX9.h>
#include <Bibim/Math.h>
#include <Bibim/Memory.h>
#include <Bibim/Matrix4.h>
#include <Bibim/ShaderEffect.DX9.h>
#include <Bibim/Texture2D.DX9.h>

namespace Bibim
{
    static void CheckedSetRenderState(IDirect3DDevice9* d3dDevice, D3DRENDERSTATETYPE state, DWORD value)
    {
        DWORD oldValue;
        d3dDevice->GetRenderState(state, &oldValue);
        if (oldValue != value)
            d3dDevice->SetRenderState(state, value);
    }

    static void CheckedSetTextureStageState(IDirect3DDevice9* d3dDevice, DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
    {
        DWORD oldValue;
        d3dDevice->GetTextureStageState(stage, type, &oldValue);
        if (oldValue != value)
            d3dDevice->SetTextureStageState(stage, type, value);
    }

    static void CheckedSetSamplerState(IDirect3DDevice9* d3dDevice, DWORD sampler, D3DSAMPLERSTATETYPE type, DWORD value)
    {
        DWORD oldValue;
        d3dDevice->GetSamplerState(sampler, type, &oldValue);
        if (oldValue != value)
            d3dDevice->SetSamplerState(sampler, type, value);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRenderer::UIRenderer()
        : Base(0x00000000),
          d3dStateBlock(nullptr),
          d3dLine(nullptr),
          vb(nullptr),
          ib(nullptr)
    {
    }

    UIRenderer::UIRenderer(GraphicsDevice* graphicsDevice, GameAssetStorage* storage, const String& shaderEffectDirectory)
        : Base(0x00000000, graphicsDevice, storage, shaderEffectDirectory),
          d3dStateBlock(nullptr),
          d3dLine(nullptr),
          vb(nullptr),
          ib(nullptr)
    {
        if (GetGraphicsDevice())
            GetGraphicsDevice()->AddLostEventListener(this);
    }

    UIRenderer::~UIRenderer()
    {
        CheckedRelease(d3dStateBlock);
        CheckedRelease(d3dLine);
        CheckedRelease(vb);
        CheckedRelease(ib);

        if (GetGraphicsDevice())
            GetGraphicsDevice()->RemoveLostEventListener(this);
    }

    void UIRenderer::Begin()
    {
        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();

        if (d3dLine == nullptr)
        {
            if (D3DXCreateLine(d3dDevice, &d3dLine) == D3D_OK)
                d3dLine->SetAntialias(TRUE);
        }

        const D3DXMATRIX d3dViewTransform(GetViewTransform());
        const D3DXMATRIX d3dProjectionTransform(GetProjectionTransform());
        d3dDevice->SetTransform(D3DTS_VIEW, &d3dViewTransform);
        d3dDevice->SetTransform(D3DTS_PROJECTION, &d3dProjectionTransform);

        // d3dDevice->BeginStateBlock();
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHATESTENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHABLENDENABLE, TRUE);
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHAREF, 0x00);
        CheckedSetRenderState(d3dDevice, D3DRS_BLENDOP, D3DBLENDOP_ADD);
        CheckedSetRenderState(d3dDevice, D3DRS_CLIPPING, TRUE);
        CheckedSetRenderState(d3dDevice, D3DRS_CULLMODE, D3DCULL_CCW);
        CheckedSetRenderState(d3dDevice, D3DRS_CLIPPLANEENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_RED);
        CheckedSetRenderState(d3dDevice, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        CheckedSetRenderState(d3dDevice, D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
        CheckedSetRenderState(d3dDevice, D3DRS_ENABLEADAPTIVETESSELLATION, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_FILLMODE, D3DFILL_SOLID);
        CheckedSetRenderState(d3dDevice, D3DRS_FOGENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_LIGHTING, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_RANGEFOGENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_SEPARATEALPHABLENDENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_SHADEMODE, D3DSHADE_FLAT);
        CheckedSetRenderState(d3dDevice, D3DRS_SPECULARENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        CheckedSetRenderState(d3dDevice, D3DRS_SRGBWRITEENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_STENCILENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_VERTEXBLEND, FALSE);

        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_TEXCOORDINDEX, 1);

        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MAXMIPLEVEL, 0);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MIPMAPLODBIAS, 0);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_SRGBTEXTURE, 0);

        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MAXMIPLEVEL, 0);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MIPMAPLODBIAS, 0);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_SRGBTEXTURE, 0);
        // d3dDevice->EndStateBlock(&d3dStateBlock);

        d3dDevice->SetFVF(VertexFVF);

        Base::Begin();
    }

    void UIRenderer::End()
    {
        Base::End();

        // d3dStateBlock->Apply();
        // CheckedRelease(d3dStateBlock);
    }

    void UIRenderer::DrawLines(int count, const Vector2* p, Color color)
    {
        if (count == 0)
            return;
        BBAssert(count > 0 && p);

        Flush();

        const D3DCOLOR d3dColor = color.ToARGB();
        if (d3dLine)
        {
            D3DXVECTOR3* v = BBStackAlloc(D3DXVECTOR3, count);
            for (int i = 0; i < count; i++)
                v[i] = D3DXVECTOR3(p[i].X, p[i].Y, 0.0f);

            d3dLine->Begin();
            d3dLine->DrawTransform(v, count, &d3dMVPTransform, d3dColor);
            d3dLine->End();

            BBStackFree(v);
        }
        else
        {
            DrawDebugLines(count, p, color);
        }
    }

    void UIRenderer::DrawLines(int count, const Vector2* p, const Color* c)
    {
        if (count == 0)
            return;
        BBAssert(count > 0 && p);

        Flush();

        const int numberOfLines = count - 1;
        Vertex* v = nullptr;
        vb->Lock(0, sizeof(Vertex) * count, reinterpret_cast<void**>(&v), D3DLOCK_DISCARD);
        for (int i = 0; i < count; i++)
            v[i] = Vertex(p[i], c[i].ToARGB());
        vb->Unlock();

        DrawPrimitives(D3DPT_LINESTRIP, numberOfLines);
    }

    void UIRenderer::DrawDebugLines(int count, const Vector2* p, Color color)
    {
        if (count == 0)
            return;
        BBAssert(count > 0 && p);

        Flush();

        const D3DCOLOR d3dColor = color.ToARGB();
        const int numberOfLines = count - 1;
        Vertex* v = nullptr;
        vb->Lock(0, sizeof(Vertex) * count, reinterpret_cast<void**>(&v), D3DLOCK_DISCARD);
        for (int i = 0; i < count; i++)
            v[i] = Vertex(p[i], d3dColor);
        vb->Unlock();
        
        DrawPrimitives(D3DPT_LINESTRIP, numberOfLines);
    }

    void UIRenderer::DrawDebugLines(int count, const Vector2* p, const Color* c)
    {
        DrawLines(count, p, c);
    }

    void UIRenderer::DrawTriangles(int count, const Vector2* p, Color color)
    {
        if (count == 0)
            return;
        BBAssert(count > 0 && p);

        Flush();

        count -= (count % 3);

        const D3DCOLOR d3dColor = color.ToARGB();
        const int numberOfTriangles = static_cast<int>(count / 3);
        Vertex* v = nullptr;
        vb->Lock(0, sizeof(Vertex) * count, reinterpret_cast<void**>(&v), D3DLOCK_DISCARD);
        for (int i = 0; i < count; i++)
            v[i] = Vertex(p[i], d3dColor);
        vb->Unlock();

        DrawPrimitives(D3DPT_TRIANGLELIST, numberOfTriangles);
    }

    void UIRenderer::BeginAlphaTextureMode()
    {
        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
    }

    void UIRenderer::EndAlphaTextureMode()
    {
        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
    }

    void UIRenderer::BeginOpacityMaskMode()
    {
        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
    }

    void UIRenderer::EndOpacityMaskMode()
    {
        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    }

    UIRenderer::Vertex* UIRenderer::LockVB(int size)
    {
        void* vertices = nullptr;
        vb->Lock(0, size, &vertices, D3DLOCK_DISCARD);
        return reinterpret_cast<Vertex*>(vertices);
    }

    void UIRenderer::UnlockVB()
    {
        vb->Unlock();
    }

    void UIRenderer::DrawQuads(Texture2D* texture, Texture2D* mask, int vertexStart, int numberOfVertices, int numberOfQuads)
    {
        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();

        if (texture)
            d3dDevice->SetTexture(0, texture->GetHandle());
        else
            d3dDevice->SetTexture(0, nullptr);
        if (mask)
            d3dDevice->SetTexture(1, mask->GetHandle());
        else
            d3dDevice->SetTexture(1, nullptr);
        d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                        vertexStart,
                                        0,
                                        numberOfVertices,
                                        0,
                                        numberOfQuads);
    }

    void UIRenderer::OnCreateQuadsCache(int vbSize, int numberOfIndices)
    {
        CheckedRelease(vb);
        CheckedRelease(ib);

        if (vbSize <= 0 || numberOfIndices <= 0)
            return;

        HRESULT result = D3D_OK;

        const int ibSize = numberOfIndices * sizeof(WORD);
        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();
        result = d3dDevice->CreateVertexBuffer(vbSize, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, VertexFVF, D3DPOOL_DEFAULT, &vb, nullptr);
        result = d3dDevice->CreateIndexBuffer(ibSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, nullptr);
        if (result == D3D_OK)
        {
            WORD* indices = nullptr;
            if (ib->Lock(0, ibSize, reinterpret_cast<void**>(&indices), 0) == D3D_OK)
            {
                for (WORD i = 0, v = 0; i < numberOfIndices; i += IndicesPerQuad, v += VerticesPerQuad)
                {
                    indices[i + 0] = v + 0;
                    indices[i + 1] = v + 1;
                    indices[i + 2] = v + 2;
                    indices[i + 3] = v + 3;
                    indices[i + 4] = v + 2;
                    indices[i + 5] = v + 1;
                }
                ib->Unlock();
            }
        }

        d3dDevice->SetStreamSource(0, vb, 0, sizeof(Vertex));
        d3dDevice->SetIndices(ib);
    }

    void UIRenderer::OnEffectBegan(PixelMode /*mode*/, ShaderEffect* effect)
    {
        ID3DXEffect* d3dEffect = effect->GetHandle();
        d3dEffect->SetMatrix(d3dEffect->GetParameter(NULL, 0), &d3dMVPTransform);
        d3dEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
        d3dEffect->BeginPass(0);
    }

    void UIRenderer::OnEffectEnded(PixelMode /*mode*/, ShaderEffect* effect)
    {
        ID3DXEffect* d3dEffect = effect->GetHandle();
        d3dEffect->EndPass();
        d3dEffect->End();
    }

    void UIRenderer::OnTransformChanged(const Matrix4& newValue)
    {
        const D3DXMATRIX d3dWorldTransform(newValue);
        GetGraphicsDevice()->GetD3DDevice()->SetTransform(D3DTS_WORLD, &d3dWorldTransform);

        const Matrix4 mvpTransform = newValue * GetViewTransform() * GetProjectionTransform();
        d3dMVPTransform = D3DXMATRIX(mvpTransform);
    }

    void UIRenderer::OnBlendModeChanged(BlendMode newValue)
    {
        DWORD blendOp = D3DBLENDOP_ADD;
        DWORD srcBlend = D3DBLEND_SRCALPHA;
        DWORD dstBlend = D3DBLEND_INVSRCALPHA;
        switch (newValue)
        {
            case NormalBlend:
                blendOp = D3DBLENDOP_ADD;
                srcBlend = D3DBLEND_SRCALPHA;
                dstBlend = D3DBLEND_INVSRCALPHA;
                break;
            case AdditiveBlend:
                blendOp = D3DBLENDOP_ADD;
                srcBlend = D3DBLEND_SRCALPHA;
                dstBlend = D3DBLEND_ONE;
                break;
            case LightenBlend:
                blendOp = D3DBLENDOP_MAX;
                srcBlend = D3DBLEND_SRCALPHA;
                dstBlend = D3DBLEND_INVSRCALPHA;
                break;
            case DarkenBlend:
                blendOp = D3DBLENDOP_MIN;
                srcBlend = D3DBLEND_SRCALPHA;
                dstBlend = D3DBLEND_INVSRCALPHA;
                break;
            case MultiplyBlend:
                blendOp = D3DBLENDOP_ADD;
                srcBlend = D3DBLEND_ZERO;
                dstBlend =  D3DBLEND_SRCCOLOR;
                break;
            case ScreenBlend:
                blendOp = D3DBLENDOP_ADD;
                srcBlend = D3DBLEND_INVDESTCOLOR;
                dstBlend = D3DBLEND_ONE;
                break;
        }

        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();
        CheckedSetRenderState(d3dDevice, D3DRS_BLENDOP, blendOp);
        CheckedSetRenderState(d3dDevice, D3DRS_SRCBLEND, srcBlend);
        CheckedSetRenderState(d3dDevice, D3DRS_DESTBLEND, dstBlend);
    }

    void UIRenderer::DrawPrimitivesActually(D3DPRIMITIVETYPE primitiveType, PixelMode pixelMode, int numberOfPrimitives, Texture2D* texture, Texture2D* mask)
    {
        IDirect3DDevice9* d3dDevice = GetGraphicsDevice()->GetD3DDevice();

        BeginEffect(pixelMode);
        if (texture)
            d3dDevice->SetTexture(0, texture->GetHandle());
        else
            d3dDevice->SetTexture(0, nullptr);
        if (mask)
            d3dDevice->SetTexture(1, mask->GetHandle());
        else
            d3dDevice->SetTexture(1, nullptr);
        d3dDevice->DrawPrimitive(primitiveType, 0, numberOfPrimitives);
        EndEffect(pixelMode);
    }

    void UIRenderer::OnGraphicsDeviceChanged(GraphicsDevice* old)
    {
        if (old)
            old->RemoveLostEventListener(this);

        if (GetGraphicsDevice())
            GetGraphicsDevice()->AddLostEventListener(this);
    }

    void UIRenderer::OnGraphicsDeviceLost(GraphicsDeviceBase* g)
    {
        BBAssert(GetGraphicsDevice() == g);
        CheckedRelease(d3dStateBlock);
        CheckedRelease(d3dLine);
        CheckedRelease(vb);
        CheckedRelease(ib);
        ReserveCachedQuads(0);
    }
}

#endif