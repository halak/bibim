#include <Bibim/PCH.h>
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
    UIRenderer::Vertex::Vertex(Vector2 position, D3DCOLOR color)
        : Position(position.X, position.Y, 0.0f),
          Color(color)
    {
    }

    UIRenderer::Vertex::Vertex(Vector2 position, D3DCOLOR color, Vector2 texCoord1)
        : Position(position.X, position.Y, 0.0f),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y)
    {
    }

    UIRenderer::Vertex::Vertex(Vector2 position, D3DCOLOR color, Vector2 texCoord1, Vector2 texCoord2)
        : Position(position.X, position.Y, 0.0f),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y),
          TexCoord2(texCoord2.X, texCoord2.Y)
    {
    }

    UIRenderer::Vertex::Vertex(Vector3 position, D3DCOLOR color)
        : Position(position.X, position.Y, position.Z),
          Color(color)
    {
    }

    UIRenderer::Vertex::Vertex(Vector3 position, D3DCOLOR color, Vector2 texCoord1)
        : Position(position.X, position.Y, position.Z),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y)
    {
    }

    UIRenderer::Vertex::Vertex(Vector3 position, D3DCOLOR color, Vector2 texCoord1, Vector2 texCoord2)
        : Position(position.X, position.Y, position.Z),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y),
          TexCoord2(texCoord2.X, texCoord2.Y)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRenderer::QuadSet::QuadSet()
        : StartIndex(0),
          Count(0),
          Capacity(0)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

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

    const int UIRenderer::TrianglesPerQuad = 2;
    const int UIRenderer::VerticesPerQuad  = 4;
    const int UIRenderer::IndicesPerQuad   = 6;

    UIRenderer::UIRenderer()
        : graphicsDevice(nullptr),
          storage(nullptr),
          fieldOfView(Math::PiOver4),
          d3dStateBlock(nullptr),
          d3dLine(nullptr),
          vb(nullptr),
          ib(nullptr),
          lockedVertices(nullptr),
          vbSize(0),
          isBatching(false),
          lastViewport(-1, -1, -1, -1)
    {
    }

    UIRenderer::UIRenderer(GraphicsDevice* graphicsDevice, GameAssetStorage* storage, const String& shaderEffectDirectory)
        : graphicsDevice(nullptr),
          storage(storage),
          shaderEffectDirectory(shaderEffectDirectory),
          fieldOfView(Math::PiOver4),
          d3dStateBlock(nullptr),
          d3dLine(nullptr),
          vb(nullptr),
          ib(nullptr),
          lockedVertices(nullptr),
          vbSize(0),
          isBatching(false),
          lastViewport(-1, -1, -1, -1)
    {
        SetGraphicsDevice(graphicsDevice);
    }

    UIRenderer::~UIRenderer()
    {
        CheckedRelease(d3dStateBlock);
        CheckedRelease(d3dLine);
        CheckedRelease(vb);
        CheckedRelease(ib);
    }

    void UIRenderer::Begin()
    {
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

        if (d3dLine == nullptr)
        {
            if (D3DXCreateLine(d3dDevice, &d3dLine) == D3D_OK)
                d3dLine->SetAntialias(TRUE);
        }

        const D3DXMATRIX d3dViewTransform(GetViewTransform());
        const D3DXMATRIX d3dProjectionTransform(GetProjectionTransform());
        d3dDevice->SetTransform(D3DTS_VIEW, &d3dViewTransform);
        d3dDevice->SetTransform(D3DTS_PROJECTION, &d3dProjectionTransform);

        d3dDevice->BeginStateBlock();
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHATESTENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHABLENDENABLE, TRUE);
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHAREF, 0x00);
        CheckedSetRenderState(d3dDevice, D3DRS_BLENDOP, D3DBLENDOP_ADD);
        CheckedSetRenderState(d3dDevice, D3DRS_CLIPPING, TRUE);
        CheckedSetRenderState(d3dDevice, D3DRS_CULLMODE, D3DCULL_NONE);
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

        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MAXMIPLEVEL, 0);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_MIPMAPLODBIAS, 0);
        CheckedSetSamplerState(d3dDevice, 1, D3DSAMP_SRGBTEXTURE, 0);
        d3dDevice->EndStateBlock(&d3dStateBlock);

        d3dDevice->SetFVF(Vertex::FVF);
        d3dDevice->SetStreamSource(0, vb, 0, sizeof(Vertex));
        d3dDevice->SetIndices(ib);
        InitializeNormalQuadSets();
        Setup(NormalBlend);
        Setup(std::vector<EffectorPtr>());
    }

    void UIRenderer::End()
    {
        Flush();
        Setup(std::vector<EffectorPtr>());
        d3dStateBlock->Apply();
        CheckedRelease(d3dStateBlock);
    }

    void UIRenderer::BeginBatch()
    {
        Flush();
        isBatching = true;
        InitializeBatchQuadSets();
    }

    void UIRenderer::EndBatch()
    {
        Flush();
        isBatching = false;
        InitializeNormalQuadSets();
    }

    void UIRenderer::Setup(const Matrix4& worldTransform)
    {
        if (this->worldTransform != worldTransform)
        {
            Flush();

            const D3DXMATRIX d3dWorldTransform(worldTransform);
            graphicsDevice->GetD3DDevice()->SetTransform(D3DTS_WORLD, &d3dWorldTransform);
            this->worldTransform = worldTransform;

            Matrix4 mvpTransform = worldTransform * viewTransform * projectionTransform;
            this->d3dMVPTransform = D3DXMATRIX(mvpTransform);
        }
    }

    BlendMode UIRenderer::Setup(BlendMode blendMode)
    {
        if (this->blendMode != blendMode)
        {
            const BlendMode old = this->blendMode;

            this->blendMode = blendMode;

            DWORD blendOp = D3DBLENDOP_ADD;
            DWORD srcBlend = D3DBLEND_SRCALPHA;
            DWORD dstBlend = D3DBLEND_INVSRCALPHA;
            switch (this->blendMode)
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

            IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
            CheckedSetRenderState(d3dDevice, D3DRS_BLENDOP, blendOp);
            CheckedSetRenderState(d3dDevice, D3DRS_SRCBLEND, srcBlend);
            CheckedSetRenderState(d3dDevice, D3DRS_DESTBLEND, dstBlend);

            return old;
        }
        else
            return this->blendMode;
    }

    void UIRenderer::Setup(const std::vector<EffectorPtr>& effectors)
    {
        Flush();

        if (effectors.empty() == false)
        {
            this->effectors = effectors;

            if (graphicsDevice->GetCapabilities().IsShaderSupported())
            {
                const int effectNameLength = shaderEffectDirectory.GetLength() + 1 + effectors.size() * 4;
                char* effectName = BBStackAlloc(char, effectNameLength + 1);
                char* en = &effectName[shaderEffectDirectory.GetLength()];
                String::CopyChars(effectName, shaderEffectDirectory.CStr());
                en[0] = '\\';
                en++;
                for (std::vector<EffectorPtr>::const_iterator it = effectors.begin(); it != effectors.end(); it++)
                {
                    const int nameHint = (*it)->GetShaderEffectNameHint();
                    if (nameHint != 0)
                    {
                        en[0] = BBFOURCCFirst(nameHint);
                        en[1] = BBFOURCCSecond(nameHint);
                        en[2] = BBFOURCCThird(nameHint);
                        en[3] = BBFOURCCFourth(nameHint);
                        en += 4;
                    }
                }
                en[0] = '\0';

                if (en - effectName - shaderEffectDirectory.GetLength() > 1)
                    this->shaderEffectBaseURI = String(effectName, 0, en - effectName);
                else
                    this->shaderEffectBaseURI = shaderEffectDirectory + "\\NORM";

                BBStackFree(effectName);
            }
        }
        else
        {
            this->effectors.clear();
            this->shaderEffectBaseURI = shaderEffectDirectory + "\\NORM";
        }

        for (int i = 0; i < NumberOfPixelModes; i++)
            this->effects[i].Reset();
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
            const int numberOfLines = count - 1;
            Vertex* v = nullptr;
            vb->Lock(0, sizeof(Vertex) * count, reinterpret_cast<void**>(&v), D3DLOCK_DISCARD);
            for (int i = 0; i < count; i++)
                v[i] = Vertex(p[i], d3dColor);
            vb->Unlock();

            DrawPrimitives(D3DPT_LINESTRIP, numberOfLines);
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

    void UIRenderer::DrawQuad(const Vector2* p, Color color)
    {
        BBAssert(p);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(nullptr, nullptr);
        v[0] = Vertex(p[0], d3dColor);
        v[1] = Vertex(p[1], d3dColor);
        v[2] = Vertex(p[2], d3dColor);
        v[3] = Vertex(p[3], d3dColor);
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const Vector2* uv, Texture2D* texture)
    {
        BBAssert(p && uv && texture);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], d3dColor, uv[0]);
        v[1] = Vertex(p[1], d3dColor, uv[1]);
        v[2] = Vertex(p[2], d3dColor, uv[2]);
        v[3] = Vertex(p[3], d3dColor, uv[3]);
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && uv1 && texture1 && uv2 && texture2);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], d3dColor, uv1[0], uv2[0]);
        v[1] = Vertex(p[1], d3dColor, uv1[1], uv2[1]);
        v[2] = Vertex(p[2], d3dColor, uv1[2], uv2[2]);
        v[3] = Vertex(p[3], d3dColor, uv1[3], uv2[3]);
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture)
    {
        BBAssert(p && texture);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], d3dColor, Vector2(clippingRect.GetLeft(),  clippingRect.GetTop()));
        v[1] = Vertex(p[1], d3dColor, Vector2(clippingRect.GetRight(), clippingRect.GetTop()));
        v[2] = Vertex(p[2], d3dColor, Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom()));
        v[3] = Vertex(p[3], d3dColor, Vector2(clippingRect.GetRight(), clippingRect.GetBottom()));
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && texture1 && uv2 && texture2);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], d3dColor, Vector2(clippingRect.GetLeft(),  clippingRect.GetTop()),    uv2[0]);
        v[1] = Vertex(p[1], d3dColor, Vector2(clippingRect.GetRight(), clippingRect.GetTop()),    uv2[1]);
        v[2] = Vertex(p[2], d3dColor, Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom()), uv2[2]);
        v[3] = Vertex(p[3], d3dColor, Vector2(clippingRect.GetRight(), clippingRect.GetBottom()), uv2[3]);
    }

    void UIRenderer::DrawQuad(const Vector2* p, const Color* c)
    {
        BBAssert(p && c);

        Vertex* v = Prepare(nullptr, nullptr);
        v[0] = Vertex(p[0], c[0].ToARGB());
        v[1] = Vertex(p[1], c[1].ToARGB());
        v[2] = Vertex(p[2], c[2].ToARGB());
        v[3] = Vertex(p[3], c[3].ToARGB());
    }

    void UIRenderer::DrawQuad(const Vector2* p, const Color* c, const Vector2* uv, Texture2D* texture)
    {
        BBAssert(p && c && uv && texture);

        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], c[0].ToARGB(), uv[0]);
        v[1] = Vertex(p[1], c[1].ToARGB(), uv[1]);
        v[2] = Vertex(p[2], c[2].ToARGB(), uv[2]);
        v[3] = Vertex(p[3], c[3].ToARGB(), uv[3]);
    }

    void UIRenderer::DrawQuad(const Vector2* p, const Color* c, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && c && uv1 && texture1 && uv2 && texture2);

        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], c[0].ToARGB(), uv1[0], uv2[0]);
        v[1] = Vertex(p[1], c[1].ToARGB(), uv1[1], uv2[1]);
        v[2] = Vertex(p[2], c[2].ToARGB(), uv1[2], uv2[2]);
        v[3] = Vertex(p[3], c[3].ToARGB(), uv1[3], uv2[3]);
    }

    void UIRenderer::DrawQuad(const Vector3* p, Color color)
    {
        BBAssert(p);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(nullptr, nullptr);
        v[0] = Vertex(p[0], d3dColor);
        v[1] = Vertex(p[1], d3dColor);
        v[2] = Vertex(p[2], d3dColor);
        v[3] = Vertex(p[3], d3dColor);
    }

    void UIRenderer::DrawQuad(const Vector3* p, Color color, const Vector2* uv,  Texture2D* texture)
    {
        BBAssert(p && uv && texture);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], d3dColor, uv[0]);
        v[1] = Vertex(p[1], d3dColor, uv[1]);
        v[2] = Vertex(p[2], d3dColor, uv[2]);
        v[3] = Vertex(p[3], d3dColor, uv[3]);
    }

    void UIRenderer::DrawQuad(const Vector3* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && uv1 && texture1 && uv2 && texture2);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], d3dColor, uv1[0], uv2[0]);
        v[1] = Vertex(p[1], d3dColor, uv1[1], uv2[1]);
        v[2] = Vertex(p[2], d3dColor, uv1[2], uv2[2]);
        v[3] = Vertex(p[3], d3dColor, uv1[3], uv2[3]);
    }

    void UIRenderer::SetGraphicsDevice(GraphicsDevice* value)
    {
        if (graphicsDevice != value)
        {
            graphicsDevice = value;
            ReserveCachedQuads(256);
        }
    }

    void UIRenderer::SetStorage(GameAssetStorage* value)
    {
        storage = value;
    }

    void UIRenderer::SetShaderEffectDirectory(const String& value)
    {
        shaderEffectDirectory = value;
    }

    void UIRenderer::SetFieldOfView(float value)
    {
        value = Math::Clamp(value, 0.0001f, Math::Pi);

        if (fieldOfView != value)
        {
            fieldOfView = value;
            lastViewport = Rect(-1, -1, -1, -1);
        }
    }

    void UIRenderer::InitializeNormalQuadSets()
    {
        const int count = sizeof(quadSets) / sizeof(quadSets[0]);
        quadSets[0].KeyTexture.Reset();
        quadSets[0].KeyMask.Reset();
        quadSets[0].StartIndex = 0;
        quadSets[0].Count = 0;
        quadSets[0].Capacity = vbSize / sizeof(Vertex) / VerticesPerQuad;
        for (int i = 1; i < count; i++)
        {
            quadSets[i].KeyTexture.Reset();
            quadSets[i].KeyMask.Reset();
            quadSets[i].StartIndex = 0;
            quadSets[i].Count = 0;
            quadSets[i].Capacity = 0;
        }
    }

    void UIRenderer::InitializeBatchQuadSets()
    {
        const int count = sizeof(quadSets) / sizeof(quadSets[0]);
        const int capacityPerQuadSet = vbSize / sizeof(Vertex) / VerticesPerQuad / 8;
        for (int i = 0, startIndex = 0; i < count; i++, startIndex += capacityPerQuadSet)
        {
            quadSets[i].KeyTexture.Reset();
            quadSets[i].KeyMask.Reset();
            quadSets[i].StartIndex = startIndex;
            quadSets[i].Count = 0;
            quadSets[i].Capacity = capacityPerQuadSet;
        }
    }

    UIRenderer::Vertex* UIRenderer::Prepare(Texture2D* texture, Texture2D* mask)
    {
        QuadSet* selectedQuadSet = nullptr;
        if (isBatching)
        {
            const int count = sizeof(quadSets) / sizeof(quadSets[0]);
            for (int i = 0; i < count; i++)
            {
                QuadSet& item = quadSets[i];

                if (item.Count > 0 &&
                    item.Count < item.Capacity &&
                    item.KeyTexture == texture &&
                    item.KeyMask == mask)
                {
                    selectedQuadSet = &item;
                    break;
                }
                else if (item.Count == 0)
                {
                    item.Mode = GetPixelMode(texture, mask);
                    item.KeyTexture = texture;
                    item.KeyMask = mask;
                    selectedQuadSet = &item;
                    break;
                }
            }

            if (selectedQuadSet == nullptr)
            {
                Flush();
                quadSets[0].Mode = GetPixelMode(texture, mask);
                quadSets[0].KeyTexture = texture;
                quadSets[0].KeyMask = mask;
                selectedQuadSet = &quadSets[0];
            }
        }
        else
        {
            if (quadSets[0].Count == 0 ||
                quadSets[0].Count >= quadSets[0].Capacity ||
                quadSets[0].KeyTexture != texture ||
                quadSets[0].KeyMask != mask)
            {
                Flush();
                quadSets[0].Mode = GetPixelMode(texture, mask);
                quadSets[0].KeyTexture = texture;
                quadSets[0].KeyMask = mask;
            }

            selectedQuadSet = &quadSets[0];
        }

        if (lockedVertices == nullptr)
            vb->Lock(0, vbSize, reinterpret_cast<void**>(&lockedVertices), D3DLOCK_DISCARD);

        BBAssertDebug(selectedQuadSet);
        selectedQuadSet->Count++;
        return &lockedVertices[(selectedQuadSet->StartIndex + selectedQuadSet->Count - 1) * VerticesPerQuad];
    }

    void UIRenderer::BeginEffect(PixelMode mode)
    {
        if (graphicsDevice->GetCapabilities().IsShaderSupported())
        {
            const int index = static_cast<int>(mode);

            if (effects[index] == nullptr)
            {
                const char* suffix = GetShaderEffectSuffix(mode);
                effects[index] = static_cast<ShaderEffect*>(storage->Load(shaderEffectBaseURI + suffix));
            }

            if (effects[index])
            {
                for (std::vector<EffectorPtr>::const_iterator it = effectors.begin(); it != effectors.end(); it++)
                {
                    (*it)->Setup(effects[index]);
                    (*it)->Begin(this);
                }

                ID3DXEffect* d3dEffect = effects[index]->GetD3DEffect();
                d3dEffect->SetMatrix(d3dEffect->GetParameter(NULL, 0), &d3dMVPTransform);
                d3dEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
                d3dEffect->BeginPass(0);
            }
        }
        else
        {
            for (std::vector<EffectorPtr>::const_iterator it = effectors.begin(); it != effectors.end(); it++)
                (*it)->Begin(this);

            if (mode == AlphaTextureOnlyMode || mode == MaskedAlphaTextureMode)
                BeginAlphaTextureMode();
        }
    }

    void UIRenderer::EndEffect(PixelMode mode)
    {
        if (graphicsDevice->GetCapabilities().IsShaderSupported() == false)
        {
            if (mode == AlphaTextureOnlyMode || mode == MaskedAlphaTextureMode)
                EndAlphaTextureMode();
        }

        for (std::vector<EffectorPtr>::const_reverse_iterator it = effectors.rbegin(); it != effectors.rend(); it++)
            (*it)->End(this);

        if (graphicsDevice->GetCapabilities().IsShaderSupported())
        {
            const int index = static_cast<int>(mode);

            if (effects[index])
            {
                ID3DXEffect* d3dEffect = effects[index]->GetD3DEffect();
                d3dEffect->EndPass();
                d3dEffect->End();
            }
        }
    }

    void UIRenderer::BeginAlphaTextureMode()
    {
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
    }

    void UIRenderer::EndAlphaTextureMode()
    {
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
    }

    
        //Flush();

        //IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
        ////CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        ////CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        ////CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        ////CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        ////CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        ////CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        ////CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);

        ////CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        ////CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        ////CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        ////CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
        ////CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_TEXCOORDINDEX, 1);

        //if (color.A >= 128)
        //{
        //    double a = (double)(color.A - 128) / 127.0;
        //    color.A = (byte)(a * 255);

        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_ADD);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_CURRENT);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);

        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLOROP, D3DTOP_MODULATE);
        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_TEXCOORDINDEX, 1);
        //}
        //else
        //{
        //    double a = (double)color.A / 127.0;
        //    color.A = 255 - (byte)(a * 255);

        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_SUBTRACT);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_CURRENT);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);

        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLOROP, D3DTOP_MODULATE);
        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_TEXCOORDINDEX, 1);
        //}

        //// Draw
        //{
        //    const D3DCOLOR d3dColor = color.ToARGB();
        //    const MaskVertex v[4] = 
        //    {
        //        MaskVertex(D3DXVECTOR3(p[0].X, p[0].Y, 0.0f), d3dColor, D3DXVECTOR2(uv2[0].X, uv2[0].Y), D3DXVECTOR2(uv1[0].X, uv1[0].Y)),
        //        MaskVertex(D3DXVECTOR3(p[1].X, p[1].Y, 0.0f), d3dColor, D3DXVECTOR2(uv2[1].X, uv2[1].Y), D3DXVECTOR2(uv1[1].X, uv1[1].Y)),
        //        MaskVertex(D3DXVECTOR3(p[2].X, p[2].Y, 0.0f), d3dColor, D3DXVECTOR2(uv2[2].X, uv2[2].Y), D3DXVECTOR2(uv1[2].X, uv1[2].Y)),
        //        MaskVertex(D3DXVECTOR3(p[3].X, p[3].Y, 0.0f), d3dColor, D3DXVECTOR2(uv2[3].X, uv2[3].Y), D3DXVECTOR2(uv1[3].X, uv1[3].Y)),
        //    };
        //    d3dDevice->SetFVF(MaskVertex::FVF);
        //    d3dDevice->SetTexture(0, maskTexture->GetD3DTexture());
        //    d3dDevice->SetTexture(1, texture->GetD3DTexture());
        //    d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(MaskVertex));
        //    d3dDevice->SetTexture(0, nullptr);
        //    d3dDevice->SetTexture(1, nullptr);
        //    d3dDevice->SetStreamSource(0, vb, 0, sizeof(VertexCO));
        //}

        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
        //CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLOROP, D3DTOP_DISABLE);

        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        //CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
    //}

    void UIRenderer::BeginOpacityMaskMode()
    {
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
    }

    void UIRenderer::EndOpacityMaskMode()
    {
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
        CheckedSetTextureStageState(d3dDevice, 1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    }

    void UIRenderer::Flush()
    {
        if (lockedVertices)
        {
            lockedVertices = nullptr;
            vb->Unlock();
        }
 
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

        const int count = sizeof(quadSets) / sizeof(quadSets[0]);
        for (int i = 0; i < count; i++)
        {
            QuadSet& item = quadSets[i];
            if (item.Count == 0)
                break;

            BeginEffect(item.Mode);
            if (item.KeyTexture)
                d3dDevice->SetTexture(0, item.KeyTexture->GetD3DTexture());
            else
                d3dDevice->SetTexture(0, nullptr);
            if (item.KeyMask)
                d3dDevice->SetTexture(1, item.KeyMask->GetD3DTexture());
            else
                d3dDevice->SetTexture(1, nullptr);
            d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                            item.StartIndex * VerticesPerQuad,
                                            0,
                                            item.Count * VerticesPerQuad,
                                            0,
                                            item.Count * TrianglesPerQuad);
            EndEffect(item.Mode);
            item.Count = 0;
        }
    }

    void UIRenderer::ReserveCachedQuads(int capacity)
    {
        BBAssert(capacity >= 0);

        CheckedRelease(vb);
        CheckedRelease(ib);

        HRESULT result = D3D_OK;

        vbSize = sizeof(Vertex) * VerticesPerQuad * capacity;
        const int ibSize = sizeof(WORD) * IndicesPerQuad * capacity;

        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
        static const DWORD vbUsage = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
        static const D3DPOOL vbPool = D3DPOOL_DEFAULT;
        result = d3dDevice->CreateVertexBuffer(vbSize, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_DEFAULT, &vb, nullptr);
        result = d3dDevice->CreateIndexBuffer(ibSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, nullptr);
        if (result == D3D_OK)
        {
            WORD* indices = nullptr;
            if (ib->Lock(0, ibSize, reinterpret_cast<void**>(&indices), 0) == D3D_OK)
            {
                const int numberOfIndices = IndicesPerQuad * capacity;
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
    }
    
    void UIRenderer::UpdateViewProjectionTransform()
    {
        if (graphicsDevice == nullptr)
        {
            viewTransform = Matrix4::Identity;
            viewTransformInv = Matrix4::Identity;
            projectionTransform = Matrix4::Identity;
            projectionTransformInv = Matrix4::Identity;
            return;
        }

        const Rect currentViewport = graphicsDevice->GetViewport();
        if (currentViewport != lastViewport)
        {
            const D3DXVECTOR2 viewportSize = D3DXVECTOR2(static_cast<float>(currentViewport.Width), static_cast<float>(currentViewport.Height));
            const D3DXVECTOR2 halfViewportSize = D3DXVECTOR2(viewportSize.x * 0.5f, viewportSize.y * 0.5f);
            const float aspect = viewportSize.x / viewportSize.y;

            D3DXMATRIX d3dViewTransform;
            D3DXMATRIX d3dProjectionTransform;

            const float distance = Math::Tan(Math::PiOver2 - (fieldOfView * 0.5f)) * halfViewportSize.x / aspect;
            const D3DXVECTOR3 eye = D3DXVECTOR3(halfViewportSize.x, halfViewportSize.y, -distance);
            const D3DXVECTOR3 at = D3DXVECTOR3(halfViewportSize.x, halfViewportSize.y, 0.0f);
            const D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
            D3DXMatrixLookAtLH(&d3dViewTransform, &eye, &at, &up);
            D3DXMATRIX t;
            D3DXMATRIX r;
            D3DXMatrixTranslation(&t, 0.0f, -viewportSize.y, 0.0f);
            D3DXMatrixRotationX(&r, Math::Pi);
            D3DXMATRIX viewResult;
            D3DXMatrixMultiply(&d3dViewTransform, &r, &d3dViewTransform);
            D3DXMatrixMultiply(&d3dViewTransform, &t, &d3dViewTransform);

            D3DXMatrixPerspectiveFovLH(&d3dProjectionTransform, fieldOfView, aspect, 0.1f, 10000.0f);

            viewTransform = Matrix4(d3dViewTransform);
            viewTransformInv = Matrix4::Inversion(viewTransform);
            projectionTransform = Matrix4(d3dProjectionTransform);
            projectionTransformInv = Matrix4::Inversion(projectionTransform);

            lastViewport = currentViewport;
        }
    }

    void UIRenderer::DrawPrimitivesActually(D3DPRIMITIVETYPE primitiveType, PixelMode pixelMode, int numberOfPrimitives, Texture2D* texture, Texture2D* mask)
    {
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

        BeginEffect(pixelMode);
        if (texture)
            d3dDevice->SetTexture(0, texture->GetD3DTexture());
        else
            d3dDevice->SetTexture(0, nullptr);
        if (mask)
            d3dDevice->SetTexture(1, mask->GetD3DTexture());
        else
            d3dDevice->SetTexture(1, nullptr);
        d3dDevice->DrawPrimitive(primitiveType, 0, numberOfPrimitives);
        EndEffect(pixelMode);
    }
}