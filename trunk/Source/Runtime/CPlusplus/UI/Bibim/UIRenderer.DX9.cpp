#include <Bibim/PCH.h>
#include <Bibim/UIRenderer.DX9.h>
#include <Bibim/Assert.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BlendMode.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Color.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Math.h>
#include <Bibim/Memory.h>
#include <Bibim/Matrix4.h>
#include <Bibim/ShaderEffect.h>
#include <Bibim/Texture2D.h>

namespace Bibim
{
    UIRenderer::VertexCO::VertexCO(D3DXVECTOR3 position, D3DCOLOR color)
        : Position(position),
          Color(color)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRenderer::VertexST::VertexST(D3DXVECTOR3 position, D3DCOLOR color, D3DXVECTOR2 texture)
        : VertexCO(position, color),
          Texture(texture)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRenderer::VertexDT::VertexDT(D3DXVECTOR3 position, D3DCOLOR color, D3DXVECTOR2 texture1, D3DXVECTOR2 texture2)
        : VertexCO(position, color),
          Texture1(texture1),
          Texture2(texture2)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRenderer::QuadSetCO::QuadSetCO()
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
          d3dVBCO(nullptr),
          d3dVBSCT(nullptr),
          d3dVBSAT(nullptr),
          d3dVBDT(nullptr),
          d3dQuadIndices(nullptr),
          vbcoSize(0),
          vbsctSize(0),
          vbsatSize(0),
          vbdtSize(0),
          lockedVBCO(nullptr),
          lockedVBSCT(nullptr),
          lockedVBSAT(nullptr),
          lockedVBDT(nullptr),
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
          d3dVBCO(nullptr),
          d3dVBSCT(nullptr),
          d3dVBSAT(nullptr),
          d3dVBDT(nullptr),
          d3dQuadIndices(nullptr),
          vbcoSize(0),
          vbsctSize(0),
          vbsatSize(0),
          vbdtSize(0),
          lockedVBCO(nullptr),
          lockedVBSCT(nullptr),
          lockedVBSAT(nullptr),
          lockedVBDT(nullptr),
          isBatching(false),
          lastViewport(-1, -1, -1, -1)
    {
        SetGraphicsDevice(graphicsDevice);
    }

    UIRenderer::~UIRenderer()
    {
        CheckedRelease(d3dStateBlock);
        CheckedRelease(d3dVBCO);
        CheckedRelease(d3dVBSCT);
        CheckedRelease(d3dVBSAT);
        CheckedRelease(d3dVBDT);
        CheckedRelease(d3dQuadIndices);
    }

    void UIRenderer::Begin()
    {
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

        const D3DXMATRIX d3dViewTransform(GetViewTransform());
        const D3DXMATRIX d3dProjectionTransform(GetProjectionTransform());
        d3dDevice->SetTransform(D3DTS_VIEW, &d3dViewTransform);
        d3dDevice->SetTransform(D3DTS_PROJECTION, &d3dProjectionTransform);

        d3dDevice->BeginStateBlock();
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHABLENDENABLE, TRUE);
        CheckedSetRenderState(d3dDevice, D3DRS_ALPHAFUNC, TRUE);
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
        CheckedSetRenderState(d3dDevice, D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
        CheckedSetRenderState(d3dDevice, D3DRS_SPECULARENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        CheckedSetRenderState(d3dDevice, D3DRS_SRGBWRITEENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_STENCILENABLE, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_VERTEXBLEND, FALSE);
        CheckedSetRenderState(d3dDevice, D3DRS_WRAP0, 0);
        CheckedSetRenderState(d3dDevice, D3DRS_SEPARATEALPHABLENDENABLE, FALSE);

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

        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MAXMIPLEVEL, 0);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MIPMAPLODBIAS, 0);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_SRGBTEXTURE, 0);
        d3dDevice->EndStateBlock(&d3dStateBlock);

        d3dDevice->SetIndices(d3dQuadIndices);
        InitializeNormalQuadSets();
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
        }
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
                for (std::vector<EffectorPtr>::const_iterator it = effectors.begin(); it != effectors.end(); it++, en += 4)
                {
                    const uint32 localName = (*it)->GetEffectName();
                    en[0] = BBFOURCCFirst(localName);
                    en[1] = BBFOURCCSecond(localName);
                    en[2] = BBFOURCCThird(localName);
                    en[3] = BBFOURCCFourth(localName);
                }
                effectName[effectNameLength] = '\0';

                this->shaderEffectBaseURI = String(effectName, 0, effectNameLength);

                BBStackFree(effectName);
            }
        }
        else
        {
            this->effectors.clear();
            this->shaderEffectBaseURI = shaderEffectDirectory + "\\NORM";
        }

        for (int i = 0; i < PixelEffectModeCount; i++)
            this->effects[i].Reset();
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color)
    {
        BBAssert(p);

        const D3DCOLOR d3dColor = color.ToARGB();
        VertexCO* v = PrepareCO();
        v[0] = VertexCO(D3DXVECTOR3(p[0].X, p[0].Y, 0.0f), d3dColor);
        v[1] = VertexCO(D3DXVECTOR3(p[1].X, p[1].Y, 0.0f), d3dColor);
        v[2] = VertexCO(D3DXVECTOR3(p[2].X, p[2].Y, 0.0f), d3dColor);
        v[3] = VertexCO(D3DXVECTOR3(p[3].X, p[3].Y, 0.0f), d3dColor);
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const Vector2* uv, Texture2D* texture)
    {
        BBAssert(p && uv && texture);

        const D3DCOLOR d3dColor = color.ToARGB();
        VertexST* v = PrepareST(texture);
        v[0] = VertexST(D3DXVECTOR3(p[0].X, p[0].Y, 0.0f), d3dColor, D3DXVECTOR2(uv[0].X, uv[0].Y));
        v[1] = VertexST(D3DXVECTOR3(p[1].X, p[1].Y, 0.0f), d3dColor, D3DXVECTOR2(uv[1].X, uv[1].Y));
        v[2] = VertexST(D3DXVECTOR3(p[2].X, p[2].Y, 0.0f), d3dColor, D3DXVECTOR2(uv[2].X, uv[2].Y));
        v[3] = VertexST(D3DXVECTOR3(p[3].X, p[3].Y, 0.0f), d3dColor, D3DXVECTOR2(uv[3].X, uv[3].Y));
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && uv1 && texture1 && uv2 && texture2);

        const D3DCOLOR d3dColor = color.ToARGB();
        VertexDT* v = PrepareDT(texture1, texture2);
        v[0] = VertexDT(D3DXVECTOR3(p[0].X, p[0].Y, 0.0f), d3dColor, D3DXVECTOR2(uv1[0].X, uv1[0].Y), D3DXVECTOR2(uv2[0].X, uv2[0].Y));
        v[1] = VertexDT(D3DXVECTOR3(p[1].X, p[1].Y, 0.0f), d3dColor, D3DXVECTOR2(uv1[1].X, uv1[1].Y), D3DXVECTOR2(uv2[1].X, uv2[1].Y));
        v[2] = VertexDT(D3DXVECTOR3(p[2].X, p[2].Y, 0.0f), d3dColor, D3DXVECTOR2(uv1[2].X, uv1[2].Y), D3DXVECTOR2(uv2[2].X, uv2[2].Y));
        v[3] = VertexDT(D3DXVECTOR3(p[3].X, p[3].Y, 0.0f), d3dColor, D3DXVECTOR2(uv1[3].X, uv1[3].Y), D3DXVECTOR2(uv2[3].X, uv2[3].Y));
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture)
    {
        BBAssert(p && texture);

        const D3DCOLOR d3dColor = color.ToARGB();
        VertexST* v = PrepareST(texture);
        v[0] = VertexST(D3DXVECTOR3(p[0].X, p[0].Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRect.GetLeft(),  clippingRect.GetTop()));
        v[1] = VertexST(D3DXVECTOR3(p[1].X, p[1].Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRect.GetRight(), clippingRect.GetTop()));
        v[2] = VertexST(D3DXVECTOR3(p[2].X, p[2].Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRect.GetLeft(),  clippingRect.GetBottom()));
        v[3] = VertexST(D3DXVECTOR3(p[3].X, p[3].Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRect.GetRight(), clippingRect.GetBottom()));
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && texture1 && uv2 && texture2);

        const D3DCOLOR d3dColor = color.ToARGB();
        VertexDT* v = PrepareDT(texture1, texture2);
        v[0] = VertexDT(D3DXVECTOR3(p[0].X, p[0].Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRect.GetLeft(),  clippingRect.GetTop()),   D3DXVECTOR2(uv2[0].X, uv2[0].Y));
        v[1] = VertexDT(D3DXVECTOR3(p[1].X, p[1].Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRect.GetRight(), clippingRect.GetTop()),   D3DXVECTOR2(uv2[1].X, uv2[1].Y));
        v[2] = VertexDT(D3DXVECTOR3(p[2].X, p[2].Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRect.GetLeft(),  clippingRect.GetBottom()), D3DXVECTOR2(uv2[2].X, uv2[2].Y));
        v[3] = VertexDT(D3DXVECTOR3(p[3].X, p[3].Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRect.GetRight(), clippingRect.GetBottom()), D3DXVECTOR2(uv2[3].X, uv2[3].Y));
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color* c)
    {
        BBAssert(p && c);

        VertexCO* v = PrepareCO();
        v[0] = VertexCO(D3DXVECTOR3(p[0].X, p[0].Y, 0.0f), c[0].ToARGB());
        v[1] = VertexCO(D3DXVECTOR3(p[1].X, p[1].Y, 0.0f), c[1].ToARGB());
        v[2] = VertexCO(D3DXVECTOR3(p[2].X, p[2].Y, 0.0f), c[2].ToARGB());
        v[3] = VertexCO(D3DXVECTOR3(p[3].X, p[3].Y, 0.0f), c[3].ToARGB());
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color* c, const Vector2* uv, Texture2D* texture)
    {
        BBAssert(p && c && uv && texture);

        VertexST* v = PrepareST(texture);
        v[0] = VertexST(D3DXVECTOR3(p[0].X, p[0].Y, 0.0f), c[0].ToARGB(), D3DXVECTOR2(uv[0].X, uv[0].Y));
        v[1] = VertexST(D3DXVECTOR3(p[1].X, p[1].Y, 0.0f), c[1].ToARGB(), D3DXVECTOR2(uv[1].X, uv[1].Y));
        v[2] = VertexST(D3DXVECTOR3(p[2].X, p[2].Y, 0.0f), c[2].ToARGB(), D3DXVECTOR2(uv[2].X, uv[2].Y));
        v[3] = VertexST(D3DXVECTOR3(p[3].X, p[3].Y, 0.0f), c[3].ToARGB(), D3DXVECTOR2(uv[3].X, uv[3].Y));
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color* c, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && c && uv1 && texture1 && uv2 && texture2);

        VertexDT* v = PrepareDT(texture1, texture2);
        v[0] = VertexDT(D3DXVECTOR3(p[0].X, p[0].Y, 0.0f), c[0].ToARGB(), D3DXVECTOR2(uv1[0].X, uv1[0].Y), D3DXVECTOR2(uv2[0].X, uv2[0].Y));
        v[1] = VertexDT(D3DXVECTOR3(p[1].X, p[1].Y, 0.0f), c[1].ToARGB(), D3DXVECTOR2(uv1[1].X, uv1[1].Y), D3DXVECTOR2(uv2[1].X, uv2[1].Y));
        v[2] = VertexDT(D3DXVECTOR3(p[2].X, p[2].Y, 0.0f), c[2].ToARGB(), D3DXVECTOR2(uv1[2].X, uv1[2].Y), D3DXVECTOR2(uv2[2].X, uv2[2].Y));
        v[3] = VertexDT(D3DXVECTOR3(p[3].X, p[3].Y, 0.0f), c[3].ToARGB(), D3DXVECTOR2(uv1[3].X, uv1[3].Y), D3DXVECTOR2(uv2[3].X, uv2[3].Y));
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
        quadSetCO.StartIndex = 0;
        quadSetCO.Count = 0;
        quadSetCO.Capacity = vbcoSize / sizeof(VertexCO);
        quadSetsSCT[0].StartIndex = 0;
        quadSetsSCT[0].Count = 0;
        quadSetsSCT[0].Capacity = vbsctSize / sizeof(VertexST);
        quadSetsSAT[0].StartIndex = 0;
        quadSetsSAT[0].Count = 0;
        quadSetsSAT[0].Capacity = vbsatSize / sizeof(VertexST);
        quadSetsDT[0].StartIndex = 0;
        quadSetsDT[0].Count = 0;
        quadSetsDT[0].Capacity = vbdtSize / sizeof(VertexDT);
    }

    void UIRenderer::InitializeBatchQuadSets()
    {
        quadSetCO.StartIndex = 0;
        quadSetCO.Count = 0;
        quadSetCO.Capacity = vbcoSize / sizeof(VertexCO) / VerticesPerQuad;

        const int numberOfQuadSetsSCT = sizeof(quadSetsSCT) / sizeof(quadSetsSCT[0]);
        const int numberOfQuadSetsSAT = sizeof(quadSetsSAT) / sizeof(quadSetsSAT[0]);
        const int numberOfQuadSetsDT = sizeof(quadSetsDT) / sizeof(quadSetsDT[0]);
        const int quadsPerSCT = vbsctSize / sizeof(VertexST) / VerticesPerQuad / numberOfQuadSetsSCT;
        const int quadsPerSAT = vbsatSize / sizeof(VertexST) / VerticesPerQuad / numberOfQuadSetsSAT;
        const int quadsPerDT = vbdtSize / sizeof(VertexDT) / VerticesPerQuad / numberOfQuadSetsDT;

        for (int i = 0; i < numberOfQuadSetsSCT; i++)
        {
            quadSetsSCT[i].StartIndex = quadsPerSCT * i;
            quadSetsSCT[i].Count = 0;
            quadSetsSCT[i].Capacity = quadsPerSCT;
        }

        for (int i = 0; i < numberOfQuadSetsSAT; i++)
        {
            quadSetsSAT[i].StartIndex = quadsPerSAT * i;
            quadSetsSAT[i].Count = 0;
            quadSetsSAT[i].Capacity = quadsPerSAT;
        }

        for (int i = 0; i < numberOfQuadSetsDT; i++)
        {
            quadSetsDT[i].StartIndex = quadsPerDT * i;
            quadSetsDT[i].Count = 0;
            quadSetsDT[i].Capacity = quadsPerDT;
        }
    }

    UIRenderer::VertexCO* UIRenderer::PrepareCO()
    {
        if (quadSetCO.Count >= quadSetCO.Capacity)
            Flush();

        if (lockedVBCO == nullptr)
            d3dVBCO->Lock(0, vbcoSize, reinterpret_cast<void**>(&lockedVBCO), D3DLOCK_DISCARD);

        quadSetCO.Count++;
        return &lockedVBCO[(quadSetCO.StartIndex + quadSetCO.Count - 1) * VerticesPerQuad];
    }

    UIRenderer::VertexST* UIRenderer::PrepareST(Texture2D* texture)
    {
        typedef QuadSetST QuadSetSTArray[8];

        const bool isColorTexture = (texture->GetPixelFormat() == Texture2D::A8R8G8B8Pixels);
        QuadSetST* quadSetsST = isColorTexture ? quadSetsSCT : quadSetsSAT;
        VertexST*& lockedVBST = isColorTexture ? lockedVBSCT : lockedVBSAT;
        IDirect3DVertexBuffer9* d3dVBST = isColorTexture ? d3dVBSCT : d3dVBSAT;
        const int vbstSize = isColorTexture ? vbsctSize : vbsatSize;

        QuadSetST* selectedQuadSet = nullptr;
        if (isBatching)
        {
            const int count = sizeof(quadSetsST) / sizeof(quadSetsST[0]);
            for (int i = 0; i < count; i++)
            {
                if (quadSetsST[i].Count > 0 &&
                    quadSetsST[i].Count < quadSetsST[i].Capacity &&
                    quadSetsST[i].KeyTexture == texture)
                {
                    selectedQuadSet = &quadSetsST[i];
                    break;
                }
                else if (quadSetsST[i].Count == 0)
                {
                    quadSetsST[i].KeyTexture = texture;
                    selectedQuadSet = &quadSetsST[i];
                    break;
                }
            }

            if (selectedQuadSet == nullptr)
            {
                Flush();
                quadSetsST[0].KeyTexture = texture;
                selectedQuadSet = &quadSetsST[0];
            }
        }
        else
        {
            if (quadSetsST[0].Count == 0 ||
                quadSetsST[0].Count >= quadSetsST[0].Capacity ||
                quadSetsST[0].KeyTexture != texture)
            {
                Flush();
                quadSetsST[0].KeyTexture = texture;
                BBAssert(quadSetsST[0].Count == 0);
            }

            selectedQuadSet = &quadSetsST[0];
        }

        if (lockedVBST == nullptr)
            d3dVBST->Lock(0, vbstSize, reinterpret_cast<void**>(&lockedVBST), D3DLOCK_DISCARD);

        selectedQuadSet->Count++;
        return &lockedVBST[(selectedQuadSet->StartIndex + selectedQuadSet->Count - 1) * VerticesPerQuad];
    }

    UIRenderer::VertexDT* UIRenderer::PrepareDT(Texture2D* texture1, Texture2D* texture2)
    {
        QuadSetDT* selectedQuadSet = nullptr;
        if (isBatching)
        {
            const int count = sizeof(quadSetsDT) / sizeof(quadSetsDT[0]);
            for (int i = 0; i < count; i++)
            {
                if (quadSetsDT[i].Count > 0 &&
                    quadSetsDT[i].KeyTexture == texture1 &&
                    quadSetsDT[i].KeyMask == texture2)
                {
                    selectedQuadSet = &quadSetsDT[i];
                    break;
                }
                else if (quadSetsDT[i].Count == 0)
                {
                    quadSetsDT[i].KeyTexture = texture1;
                    quadSetsDT[i].KeyMask = texture2;
                    selectedQuadSet = &quadSetsDT[i];
                    break;
                }
            }

            if (selectedQuadSet == nullptr)
            {
                Flush();
                quadSetsDT[0].KeyTexture = texture1;
                selectedQuadSet = &quadSetsDT[0];
            }
        }
        else
        {
            if (quadSetsDT[0].Count == 0 ||
                quadSetsDT[0].Count >= quadSetsDT[0].Capacity ||
                quadSetsDT[0].KeyTexture != texture1 ||
                quadSetsDT[0].KeyMask != texture2)
            {
                Flush();
                quadSetsDT[0].KeyTexture = texture1;
                quadSetsDT[0].KeyMask = texture2;
                BBAssert(quadSetsDT[0].Count == 0);
            }

            selectedQuadSet = &quadSetsDT[0];
        }

        if (lockedVBDT == nullptr)
            d3dVBDT->Lock(0, vbdtSize, reinterpret_cast<void**>(&lockedVBDT), D3DLOCK_DISCARD);

        selectedQuadSet->Count++;
        return &lockedVBDT[(selectedQuadSet->StartIndex + selectedQuadSet->Count - 1) * VerticesPerQuad];
    }

    void UIRenderer::BeginEffect(int index, const char* key)
    {
        BBAssert(graphicsDevice->GetCapabilities().IsShaderSupported());

        if (effects[index] == nullptr)
            effects[index] = static_cast<ShaderEffect*>(storage->Load(shaderEffectBaseURI + key));

        if (effects[index])
        {
            for (std::vector<EffectorPtr>::const_iterator it = effectors.begin(); it != effectors.end(); it++)
                (*it)->Begin(effects[index]);

            ID3DXEffect* d3dEffect = effects[index]->GetD3DEffect();
            const D3DXMATRIX wtm = worldTransform;
            const D3DXMATRIX vptm = viewTransform * projectionTransform;
            d3dEffect->SetMatrix(d3dEffect->GetParameter(NULL, 0), &wtm);
            d3dEffect->SetMatrix(d3dEffect->GetParameter(NULL, 1), &vptm);
            d3dEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
            d3dEffect->BeginPass(0);
        }
    }

    void UIRenderer::EndEffect(int index)
    {
        BBAssert(graphicsDevice->GetCapabilities().IsShaderSupported());

        if (effects[index])
        {
            ID3DXEffect* d3dEffect = effects[index]->GetD3DEffect();
            d3dEffect->EndPass();
            d3dEffect->End();
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

        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
    }

    void UIRenderer::EndAlphaTextureMode()
    {
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        CheckedSetSamplerState(d3dDevice, 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        CheckedSetTextureStageState(d3dDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
    }

    void UIRenderer::Flush()
    {
        if (lockedVBCO)
        {
            lockedVBCO = nullptr;
            d3dVBCO->Unlock();
        }

        if (lockedVBSCT)
        {
            lockedVBSCT = nullptr;
            d3dVBSCT->Unlock();
        }

        if (lockedVBSAT)
        {
            lockedVBSAT = nullptr;
            d3dVBSAT->Unlock();
        }
        
        if (lockedVBDT)
        {
            lockedVBDT = nullptr;
            d3dVBDT->Unlock();
        }
 
        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

        if (quadSetCO.Count > 0)
        {
            if (graphicsDevice->GetCapabilities().IsShaderSupported())
                BeginEffect(NoTextureMode, "0");

            d3dDevice->SetStreamSource(0, d3dVBCO, 0, sizeof(VertexCO));
            d3dDevice->SetFVF(VertexCO::FVF);
            d3dDevice->SetTexture(0, nullptr);
            d3dDevice->SetTexture(1, nullptr);
            d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                            0,
                                            0,
                                            quadSetCO.Count * VerticesPerQuad,
                                            0,
                                            quadSetCO.Count * TrianglesPerQuad);
            quadSetCO.Count = 0;
            
            if (graphicsDevice->GetCapabilities().IsShaderSupported())
                EndEffect(NoTextureMode);
        }

        if (quadSetsSCT[0].Count > 0)
        {
            if (graphicsDevice->GetCapabilities().IsShaderSupported())
                BeginEffect(ColorTextureMode, "1");

            const int count = sizeof(quadSetsSCT) / sizeof(quadSetsSCT[0]);
            d3dDevice->SetStreamSource(0, d3dVBSCT, 0, sizeof(VertexST));
            d3dDevice->SetFVF(VertexST::FVF);
            d3dDevice->SetTexture(1, nullptr);
            for (int i = 0; i < count; i++)
            {
                if (quadSetsSCT[i].Count == 0)
                    break;

                d3dDevice->SetTexture(0, quadSetsSCT[i].KeyTexture->GetD3DTexture());
                d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                quadSetsSCT[i].StartIndex * VerticesPerQuad,
                                                0,
                                                quadSetsSCT[i].Count * VerticesPerQuad,
                                                0,
                                                quadSetsSCT[i].Count * TrianglesPerQuad);

                quadSetsSCT[i].Count = 0;
            }

            if (graphicsDevice->GetCapabilities().IsShaderSupported())
                EndEffect(ColorTextureMode);
        }

        if (quadSetsSAT[0].Count > 0)
        {
            if (graphicsDevice->GetCapabilities().IsShaderSupported())
                BeginEffect(AlphaTextureMode, "2");
            else
                BeginAlphaTextureMode();

            const int count = sizeof(quadSetsSAT) / sizeof(quadSetsSAT[0]);
            d3dDevice->SetStreamSource(0, d3dVBSAT, 0, sizeof(VertexST));
            d3dDevice->SetFVF(VertexST::FVF);
            d3dDevice->SetTexture(1, nullptr);
            for (int i = 0; i < count; i++)
            {
                if (quadSetsSAT[i].Count == 0)
                    break;

                d3dDevice->SetTexture(0, quadSetsSAT[i].KeyTexture->GetD3DTexture());
                d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                quadSetsSAT[i].StartIndex * VerticesPerQuad,
                                                0,
                                                quadSetsSAT[i].Count * VerticesPerQuad,
                                                0,
                                                quadSetsSAT[i].Count * TrianglesPerQuad);

                quadSetsSAT[i].Count = 0;
            }

            if (graphicsDevice->GetCapabilities().IsShaderSupported() == false)
                EndAlphaTextureMode();
            else
                EndEffect(AlphaTextureMode);
        }

        if (quadSetsDT[0].Count > 0)
        {
            if (graphicsDevice->GetCapabilities().IsShaderSupported())
                BeginEffect(ColorAndAlphaTextureMode, "3");

            const int count = sizeof(d3dVBDT) / sizeof(quadSetsDT[0]);
            d3dDevice->SetStreamSource(0, d3dVBDT, 0, sizeof(VertexDT));
            d3dDevice->SetFVF(VertexDT::FVF);
            for (int i = 0; i < count; i++)
            {
                if (quadSetsDT[i].Count == 0)
                    break;

                d3dDevice->SetTexture(0, quadSetsDT[i].KeyTexture->GetD3DTexture());
                d3dDevice->SetTexture(1, quadSetsDT[i].KeyMask->GetD3DTexture());
                d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                quadSetsDT[i].StartIndex * VerticesPerQuad,
                                                0,
                                                quadSetsDT[i].Count * VerticesPerQuad,
                                                0,
                                                quadSetsDT[i].Count * TrianglesPerQuad);

                quadSetsDT[i].Count = 0;
            }

            if (graphicsDevice->GetCapabilities().IsShaderSupported())
                EndEffect(ColorAndAlphaTextureMode);
        }
    }

    void UIRenderer::ReserveCachedQuads(int capacity)
    {
        BBAssert(capacity >= 0);

        CheckedRelease(d3dVBCO);
        CheckedRelease(d3dVBSCT);
        CheckedRelease(d3dVBSAT);
        CheckedRelease(d3dVBDT);
        CheckedRelease(d3dQuadIndices);

        HRESULT result = D3D_OK;

        const int ibSize = sizeof(WORD) * IndicesPerQuad * capacity;
        vbcoSize = sizeof(VertexCO) * VerticesPerQuad * capacity;
        vbsctSize = sizeof(VertexST) * VerticesPerQuad * capacity;
        vbsatSize = sizeof(VertexST) * VerticesPerQuad * capacity;
        vbdtSize = sizeof(VertexDT) * VerticesPerQuad * capacity;

        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

        static const DWORD vbUsage = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
        static const D3DPOOL vbPool = D3DPOOL_DEFAULT;
        result = d3dDevice->CreateVertexBuffer(vbcoSize, vbUsage, VertexCO::FVF, vbPool, &d3dVBCO, nullptr);
        result = d3dDevice->CreateVertexBuffer(vbsctSize, vbUsage, VertexST::FVF, vbPool, &d3dVBSCT, nullptr);
        result = d3dDevice->CreateVertexBuffer(vbsatSize, vbUsage, VertexST::FVF, vbPool, &d3dVBSAT, nullptr);
        result = d3dDevice->CreateVertexBuffer(vbdtSize, vbUsage, VertexDT::FVF, vbPool, &d3dVBDT, nullptr);
        result = d3dDevice->CreateIndexBuffer(ibSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &d3dQuadIndices, nullptr);
        if (result == D3D_OK)
        {
            WORD* indices = nullptr;
            if (d3dQuadIndices->Lock(0, ibSize, reinterpret_cast<void**>(&indices), 0) == D3D_OK)
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
                d3dQuadIndices->Unlock();
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

            D3DXMATRIX d3dViewTransformInv;
            D3DXMATRIX d3dProjectionTransformInv;
            D3DXMatrixInverse(&d3dViewTransformInv, nullptr, &d3dViewTransform);
            D3DXMatrixInverse(&d3dProjectionTransformInv, nullptr, &d3dProjectionTransform);

            viewTransform = Matrix4(d3dViewTransform);
            viewTransformInv = Matrix4(d3dViewTransformInv);
            projectionTransform = Matrix4(d3dProjectionTransform);
            projectionTransformInv = Matrix4(d3dProjectionTransformInv);

            lastViewport = currentViewport;
        }
    }
}