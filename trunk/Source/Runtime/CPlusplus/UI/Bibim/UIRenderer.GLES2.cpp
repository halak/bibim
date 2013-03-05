#include <Bibim/PCH.h>
#include <Bibim/UIRenderer.GLES2.h>
#include <Bibim/Assert.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BlendMode.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Color.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/Math.h>
#include <Bibim/Memory.h>
#include <Bibim/Matrix4.h>
#include <Bibim/ShaderEffect.GLES2.h>
#include <Bibim/Texture2D.GLES2.h>

namespace Bibim
{
    const int UIRenderer::TrianglesPerQuad = 2;
    const int UIRenderer::VerticesPerQuad  = 4;
    const int UIRenderer::IndicesPerQuad   = 6;

    UIRenderer::UIRenderer()
        : graphicsDevice(nullptr),
          storage(nullptr),
          fieldOfView(Math::PiOver4),
          lastViewport(-1, -1, -1, -1)
    {
    }

    UIRenderer::UIRenderer(GraphicsDevice* graphicsDevice, GameAssetStorage* storage, const String& shaderEffectDirectory)
        : graphicsDevice(nullptr),
          storage(storage),
          shaderEffectDirectory(shaderEffectDirectory),
          fieldOfView(Math::PiOver4),
          lastViewport(-1, -1, -1, -1)
    {
        SetGraphicsDevice(graphicsDevice);
    }

    UIRenderer::~UIRenderer()
    {
    }

    void UIRenderer::Begin()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);

        /*
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
        */
        Setup(NormalBlend);
        Setup(std::vector<EffectorPtr>());
    }

    void UIRenderer::End()
    {
        /*
        Flush();
        Setup(std::vector<EffectorPtr>());
        d3dStateBlock->Apply();
        CheckedRelease(d3dStateBlock);
        */
    }

    void UIRenderer::BeginBatch()
    {
    }

    void UIRenderer::EndBatch()
    {
    }

    void UIRenderer::Setup(const Matrix4& worldTransform)
    {
        if (this->worldTransform != worldTransform)
        {
            this->worldTransform = worldTransform;
            mvpTransform = worldTransform * viewTransform * projectionTransform;
        }
    }

    BlendMode UIRenderer::Setup(BlendMode blendMode)
    {
        if (this->blendMode != blendMode)
        {
            const BlendMode old = this->blendMode;

            this->blendMode = blendMode;

            GLenum blendOp = GL_FUNC_ADD;
            GLenum srcBlend = GL_SRC_ALPHA;
            GLenum dstBlend = GL_ONE_MINUS_SRC_ALPHA;
            switch (this->blendMode)
            {
                case NormalBlend:
                    srcBlend = GL_SRC_ALPHA;
                    dstBlend = GL_ONE_MINUS_SRC_ALPHA;
                    break;
                case AdditiveBlend:
                    srcBlend = GL_SRC_ALPHA;
                    dstBlend = GL_ONE;
                    break;
                case LightenBlend:
                    srcBlend = GL_SRC_ALPHA;
                    dstBlend = GL_ONE;
                    break;
                case DarkenBlend:
                    blendOp = GL_FUNC_SUBTRACT;
                    srcBlend = GL_SRC_ALPHA;
                    dstBlend = GL_ONE_MINUS_SRC_ALPHA;
                    break;
                case MultiplyBlend:
                    srcBlend = GL_ZERO;
                    dstBlend = GL_SRC_COLOR;
                    break;
                case ScreenBlend:
                    srcBlend = GL_ONE_MINUS_DST_COLOR;
                    dstBlend = GL_ONE;
                    break;
            }

            glBlendEquation(blendOp);
            glBlendFunc(srcBlend, dstBlend);

            return old;
        }
        else
            return this->blendMode;
    }

    void UIRenderer::Setup(const std::vector<EffectorPtr>& effectors)
    {
        if (effectors.empty() == false)
        {
            this->effectors = effectors;

            if (graphicsDevice->GetCapabilities().IsShaderSupported())
            {
                const int effectNameLength = shaderEffectDirectory.GetLength() + 1 + 3 + effectors.size() * 4;
                char* effectName = BBStackAlloc(char, effectNameLength + 1);
                char* en = &effectName[shaderEffectDirectory.GetLength()];
                String::CopyChars(effectName, shaderEffectDirectory.CStr());
                en[0] = '\\';
                en++;
                en[0] = 'G';
                en[1] = 'L';
                en[2] = '_';
                en+=3;

                bool usingNormalEffect = true;
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
                        usingNormalEffect = false;
                    }
                }
                en[0] = '\0';

                if (usingNormalEffect)
                    this->shaderEffectBaseURI = shaderEffectDirectory + "\\GL_NORM";
                else
                    this->shaderEffectBaseURI = String(effectName, 0, en - effectName);                    

                BBStackFree(effectName);
            }
        }
        else
        {
            this->effectors.clear();
            this->shaderEffectBaseURI = shaderEffectDirectory + "\\GL_NORM";
        }

        for (int i = 0; i < NumberOfPixelModes; i++)
            this->effects[i].Reset();
    }

    void UIRenderer::DrawLines(int count, const Vector2* p, Color color)
    {
        /*
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
        */
    }

    void UIRenderer::DrawLines(int count, const Vector2* p, const Color* c)
    {
        /*
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
        */
    }

    void UIRenderer::DrawTriangles(int count, const Vector2* p, Color color)
    {
        /*
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
        */
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color)
    {
        /*
        BBAssert(p);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(nullptr, nullptr);
        v[0] = Vertex(p[0], d3dColor);
        v[1] = Vertex(p[1], d3dColor);
        v[2] = Vertex(p[2], d3dColor);
        v[3] = Vertex(p[3], d3dColor);
        */
    }

    static Vector4 v4(Vector2 v) { return Vector4(v.X, v.Y, 0.0f, 1.0f); }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const Vector2* uv, Texture2D* texture)
    {
        BBAssert(p && texture);

        struct Vertex
        {
            Vector4 Position;
            unsigned long Color;
            Vector2 TexCoord1;
            Vector2 TexCoord2;
        };

        Vertex v[4] = 
        {
            { v4(p[0]), color.ToARGB(), uv[0] },
            { v4(p[1]), color.ToARGB(), uv[1] },
            { v4(p[2]), color.ToARGB(), uv[2] },
            { v4(p[3]), color.ToARGB(), uv[3] },
        };

        PixelMode pixelMode;
        if (texture->GetPixelFormat() == Texture2D::A8R8G8B8Pixels)
            pixelMode = ColorTextureOnlyMode;
        else
            pixelMode = AlphaTextureOnlyMode;

        BeginEffect(pixelMode);


        GLint program;
        glGetIntegerv(GL_CURRENT_PROGRAM, &program);

        GLuint positionAttribute = glGetAttribLocation(program, "Position");
        GLuint colorAttribute = glGetAttribLocation(program, "Color");
        GLuint texCoordAttribute = glGetAttribLocation(program, "TexCoord1");

        glUniform1i(glGetUniformLocation(program, "MainSampler"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetHandle());

        byte* pos = reinterpret_cast<byte*>(v);
        byte* clr = pos + sizeof(Vector4);
        byte* tex = clr + sizeof(unsigned long);

        glVertexAttribPointer(positionAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), pos);
        glEnableVertexAttribArray(positionAttribute);
        glVertexAttribPointer(colorAttribute, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), clr);
        glEnableVertexAttribArray(colorAttribute);
        glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), tex);
        glEnableVertexAttribArray(texCoordAttribute);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        EndEffect(pixelMode);
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        /*
        BBAssert(p && uv1 && texture1 && uv2 && texture2);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], d3dColor, uv1[0], uv2[0]);
        v[1] = Vertex(p[1], d3dColor, uv1[1], uv2[1]);
        v[2] = Vertex(p[2], d3dColor, uv1[2], uv2[2]);
        v[3] = Vertex(p[3], d3dColor, uv1[3], uv2[3]);
        */
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture)
    {
        BBAssert(p && texture);

        PixelMode pixelMode;
        if (texture->GetPixelFormat() == Texture2D::A8R8G8B8Pixels)
            pixelMode = ColorTextureOnlyMode;
        else
            pixelMode = AlphaTextureOnlyMode;

        BeginEffect(pixelMode);

        Vector4 v[4] = { v4(p[0]), v4(p[1]), v4(p[2]), v4(p[3]) };
        unsigned long c[4]  = { color.ToARGB(), color.ToARGB(), color.ToARGB(), color.ToARGB() };
        Vector2 uv[4]  = { Vector2(clippingRect.GetLeft(),  clippingRect.GetTop()),
        Vector2(clippingRect.GetRight(), clippingRect.GetTop()),
        Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom()),
        Vector2(clippingRect.GetRight(), clippingRect.GetBottom())};

        GLint program;
        glGetIntegerv(GL_CURRENT_PROGRAM, &program);

        GLuint positionAttribute = glGetAttribLocation(program, "Position");
        GLuint colorAttribute = glGetAttribLocation(program, "Color");
        GLuint texCoordAttribute = glGetAttribLocation(program, "TexCoord1");

        glUniform1i(glGetUniformLocation(program, "MainSampler"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetHandle());

        glVertexAttribPointer(positionAttribute, 4, GL_FLOAT, GL_FALSE, 0, v);
        glEnableVertexAttribArray(positionAttribute);
        glVertexAttribPointer(colorAttribute, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, c);
        glEnableVertexAttribArray(colorAttribute);
        glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, 0, uv);
        glEnableVertexAttribArray(texCoordAttribute);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        EndEffect(pixelMode);


        /*
        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], d3dColor, Vector2(clippingRect.GetLeft(),  clippingRect.GetTop()));
        v[1] = Vertex(p[1], d3dColor, Vector2(clippingRect.GetRight(), clippingRect.GetTop()));
        v[2] = Vertex(p[2], d3dColor, Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom()));
        v[3] = Vertex(p[3], d3dColor, Vector2(clippingRect.GetRight(), clippingRect.GetBottom()));
        */
    }

    void UIRenderer::DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        /*
        BBAssert(p && texture1 && uv2 && texture2);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], d3dColor, Vector2(clippingRect.GetLeft(),  clippingRect.GetTop()),    uv2[0]);
        v[1] = Vertex(p[1], d3dColor, Vector2(clippingRect.GetRight(), clippingRect.GetTop()),    uv2[1]);
        v[2] = Vertex(p[2], d3dColor, Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom()), uv2[2]);
        v[3] = Vertex(p[3], d3dColor, Vector2(clippingRect.GetRight(), clippingRect.GetBottom()), uv2[3]);
        */
    }

    void UIRenderer::DrawQuad(const Vector2* p, const Color* c)
    {
        /*
        BBAssert(p && c);

        Vertex* v = Prepare(nullptr, nullptr);
        v[0] = Vertex(p[0], c[0].ToARGB());
        v[1] = Vertex(p[1], c[1].ToARGB());
        v[2] = Vertex(p[2], c[2].ToARGB());
        v[3] = Vertex(p[3], c[3].ToARGB());
        */
    }

    void UIRenderer::DrawQuad(const Vector2* p, const Color* c, const Vector2* uv, Texture2D* texture)
    {
        BBAssert(p && texture);

        BeginEffect(ColorTextureOnlyMode);

        Vector4 v[4] = { v4(p[0]), v4(p[1]), v4(p[2]), v4(p[3]) };

        GLint program;
        glGetIntegerv(GL_CURRENT_PROGRAM, &program);

        GLuint positionAttribute = glGetAttribLocation(program, "Position");
        GLuint colorAttribute = glGetAttribLocation(program, "Color");
        GLuint texCoordAttribute = glGetAttribLocation(program, "TexCoord1");

        glUniform1i(glGetUniformLocation(program, "MainSampler"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetHandle());

        glVertexAttribPointer(positionAttribute, 4, GL_FLOAT, GL_FALSE, 0, v);
        glEnableVertexAttribArray(positionAttribute);
        glVertexAttribPointer(colorAttribute, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, c);
        glEnableVertexAttribArray(colorAttribute);
        glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, 0, uv);
        glEnableVertexAttribArray(texCoordAttribute);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        EndEffect(ColorTextureOnlyMode);
    }

    void UIRenderer::DrawQuad(const Vector2* p, const Color* c, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        /*
        BBAssert(p && c && uv1 && texture1 && uv2 && texture2);

        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], c[0].ToARGB(), uv1[0], uv2[0]);
        v[1] = Vertex(p[1], c[1].ToARGB(), uv1[1], uv2[1]);
        v[2] = Vertex(p[2], c[2].ToARGB(), uv1[2], uv2[2]);
        v[3] = Vertex(p[3], c[3].ToARGB(), uv1[3], uv2[3]);
        */
    }

    void UIRenderer::DrawQuad(const Vector3* p, Color color)
    {
        /*
        BBAssert(p);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(nullptr, nullptr);
        v[0] = Vertex(p[0], d3dColor);
        v[1] = Vertex(p[1], d3dColor);
        v[2] = Vertex(p[2], d3dColor);
        v[3] = Vertex(p[3], d3dColor);
        */
    }

    void UIRenderer::DrawQuad(const Vector3* p, Color color, const Vector2* uv,  Texture2D* texture)
    {
        /*
        BBAssert(p && uv && texture);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], d3dColor, uv[0]);
        v[1] = Vertex(p[1], d3dColor, uv[1]);
        v[2] = Vertex(p[2], d3dColor, uv[2]);
        v[3] = Vertex(p[3], d3dColor, uv[3]);
        */
    }

    void UIRenderer::DrawQuad(const Vector3* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        /*
        BBAssert(p && uv1 && texture1 && uv2 && texture2);

        const D3DCOLOR d3dColor = color.ToARGB();
        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], d3dColor, uv1[0], uv2[0]);
        v[1] = Vertex(p[1], d3dColor, uv1[1], uv2[1]);
        v[2] = Vertex(p[2], d3dColor, uv1[2], uv2[2]);
        v[3] = Vertex(p[3], d3dColor, uv1[3], uv2[3]);
        */
    }

    void UIRenderer::SetGraphicsDevice(GraphicsDevice* value)
    {
        if (graphicsDevice != value)
        {
            graphicsDevice = value;
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

    void UIRenderer::BeginEffect(PixelMode mode)
    {
        const int index = static_cast<int>(mode);

        if (effects[index] == nullptr)
        {
            const char* suffix = GetShaderEffectSuffix(mode);
            effects[index] = static_cast<ShaderEffect*>(storage->Load(shaderEffectBaseURI + suffix));
        }

        if (effects[index])
        {
            GLuint handle = effects[index]->GetHandle();
            glUseProgram(handle);

            for (std::vector<EffectorPtr>::const_iterator it = effectors.begin(); it != effectors.end(); it++)
            {
                (*it)->Setup(effects[index]);
                (*it)->Begin(this);
            }

            glUniformMatrix4fv(glGetUniformLocation(handle, "MVP"), 1, GL_FALSE, mvpTransform);
        }
    }

    void UIRenderer::EndEffect(PixelMode mode)
    {
        for (std::vector<EffectorPtr>::const_reverse_iterator it = effectors.rbegin(); it != effectors.rend(); it++)
            (*it)->End(this);

        glUseProgram(0);
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
            const Vector2 viewportSize = Vector2(currentViewport.Width, currentViewport.Height);
            const Vector2 halfViewportSize = viewportSize * 0.5f;
            const float aspect = viewportSize.X / viewportSize.Y;

            const float distance = Math::Tan(Math::PiOver2 - (fieldOfView * 0.5f)) * halfViewportSize.X / aspect;
            const Vector3 eye = Vector3(halfViewportSize.X, halfViewportSize.Y, -distance);
            const Vector3 at = Vector3(halfViewportSize.X, halfViewportSize.Y, 0.0f);
            const Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

            viewTransform = Matrix4::LookAt(eye, at, up);
            viewTransform = Matrix4::RotationX(Math::Pi) * viewTransform;
            viewTransform = Matrix4::Translation(Vector3(0.0f, -viewportSize.Y, 0.0f)) * viewTransform;

            projectionTransform = Matrix4::PerspectiveFov(fieldOfView, aspect, 0.1f, 10000.0f);

            viewTransformInv = Matrix4::Inversion(viewTransform);
            projectionTransformInv = Matrix4::Inversion(projectionTransform);

            lastViewport = currentViewport;
        }
    }
}