#include <Bibim/Config.h>
#include <Bibim/UIRendererBase.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Math.h>
#include <Bibim/ShaderEffect.h>
#include <Bibim/Texture2D.h>
#include <Bibim/Log.h>

namespace Bibim
{
    UIRendererBase::UIRendererBase(uint effectFileFormatHint)
        : graphicsDevice(nullptr),
          storage(nullptr),
          fieldOfView(Math::PiOver4),
          lockedVertices(nullptr),
          vbSize(0),
          isBatching(false),
          lastResolution(-1, -1),
          effectFileFormatHint(effectFileFormatHint),
          normalEffectFileName(MakeNormalEffectFileName(effectFileFormatHint))
    {
    }

    UIRendererBase::UIRendererBase(uint effectFileFormatHint, GraphicsDevice* graphicsDevice, GameAssetStorage* storage, const String& shaderEffectDirectory)
        : graphicsDevice(graphicsDevice),
          storage(storage),
          shaderEffectDirectory(shaderEffectDirectory),
          fieldOfView(Math::PiOver4),
          lockedVertices(nullptr),
          vbSize(0),
          isBatching(false),
          lastResolution(-1, -1),
          effectFileFormatHint(effectFileFormatHint),
          normalEffectFileName(MakeNormalEffectFileName(effectFileFormatHint))
    {
    }

    UIRendererBase::~UIRendererBase()
    {
    }

    void UIRendererBase::Begin()
    {
        if (vbSize == 0)
            ReserveCachedQuads(256);

        worldTransform = Matrix4::Zero;
        InitializeNormalQuadSets();
        Setup(NormalBlend);
        Setup(std::vector<EffectorPtr>());
    }

    void UIRendererBase::End()
    {
        Flush();
        Setup(std::vector<EffectorPtr>());
    }

    void UIRendererBase::BeginBatch()
    {
        Flush();
        isBatching = true;
        InitializeBatchQuadSets();
    }

    void UIRendererBase::EndBatch()
    {
        Flush();
        isBatching = false;
        InitializeNormalQuadSets();
    }


    void UIRendererBase::Setup(const Matrix4& worldTransform)
    {
        if (this->worldTransform != worldTransform)
        {
            Flush();
            this->worldTransform = worldTransform;
            OnTransformChanged(worldTransform);
        }
    }

    void UIRendererBase::Setup(const std::vector<EffectorPtr>& effectors)
    {
        Flush();

        if (effectors.empty() == false)
        {
            this->effectors = effectors;

            if (graphicsDevice->GetCapabilities().IsShaderSupported())
            {
                const int effectNameLength = shaderEffectDirectory.GetLength() + 1 + 4 + effectors.size() * 4;
                char* effectName = BBStackAlloc(char, effectNameLength + 1);
                char* en = &effectName[shaderEffectDirectory.GetLength()];
                String::CopyChars(effectName, shaderEffectDirectory.CStr());
                en[0] = '\\';
                en++;

                if (effectFileFormatHint != 0)
                {
                    en[0] = BBFOURCCFirst(effectFileFormatHint);
                    en[1] = BBFOURCCSecond(effectFileFormatHint);
                    en[2] = BBFOURCCThird(effectFileFormatHint);
                    en[3] = BBFOURCCFourth(effectFileFormatHint);
                    en += 4;
                }
                
                bool usingNormalEffectFile = true;
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
                        usingNormalEffectFile = false;
                    }
                }
                en[0] = '\0';

                if (usingNormalEffectFile)
                    this->shaderEffectBaseURI = shaderEffectDirectory + normalEffectFileName;
                else
                    this->shaderEffectBaseURI = String(effectName, 0, en - effectName);
                    

                BBStackFree(effectName);
            }
        }
        else
        {
            this->effectors.clear();
            this->shaderEffectBaseURI = shaderEffectDirectory + normalEffectFileName;
        }

        for (int i = 0; i < NumberOfPixelModes; i++)
            this->effects[i].Reset();
    }

    BlendMode UIRendererBase::Setup(BlendMode blendMode)
    {
        if (this->blendMode != blendMode)
        {
            const BlendMode old = this->blendMode;

            this->blendMode = blendMode;

            OnBlendModeChanged(blendMode);

            return old;
        }
        else
            return this->blendMode;
    }

    void UIRendererBase::DrawQuad(const Vector2* p, Color color)
    {
        BBAssert(p);

        const unsigned long argb = color.ToARGB();
        Vertex* v = Prepare(nullptr, nullptr);
        v[0] = Vertex(p[0], argb);
        v[1] = Vertex(p[1], argb);
        v[2] = Vertex(p[2], argb);
        v[3] = Vertex(p[3], argb);
    }

    void UIRendererBase::DrawQuad(const Vector2* p, Color color, const Vector2* uv, Texture2D* texture)
    {
        BBAssert(p && uv && texture);

        const unsigned long argb = color.ToARGB();
        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], argb, uv[0]);
        v[1] = Vertex(p[1], argb, uv[1]);
        v[2] = Vertex(p[2], argb, uv[2]);
        v[3] = Vertex(p[3], argb, uv[3]);
    }

    void UIRendererBase::DrawQuad(const Vector2* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && uv1 && texture1 && uv2 && texture2);

        const unsigned long argb = color.ToARGB();
        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], argb, uv1[0], uv2[0]);
        v[1] = Vertex(p[1], argb, uv1[1], uv2[1]);
        v[2] = Vertex(p[2], argb, uv1[2], uv2[2]);
        v[3] = Vertex(p[3], argb, uv1[3], uv2[3]);
    }

    void UIRendererBase::DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture)
    {
        BBAssert(p && texture);

        const unsigned long argb = color.ToARGB();
        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], argb, Vector2(clippingRect.GetLeft(),  clippingRect.GetTop()));
        v[1] = Vertex(p[1], argb, Vector2(clippingRect.GetRight(), clippingRect.GetTop()));
        v[2] = Vertex(p[2], argb, Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom()));
        v[3] = Vertex(p[3], argb, Vector2(clippingRect.GetRight(), clippingRect.GetBottom()));
    }

    void UIRendererBase::DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && texture1 && uv2 && texture2);

        const unsigned long argb = color.ToARGB();
        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], argb, Vector2(clippingRect.GetLeft(),  clippingRect.GetTop()),    uv2[0]);
        v[1] = Vertex(p[1], argb, Vector2(clippingRect.GetRight(), clippingRect.GetTop()),    uv2[1]);
        v[2] = Vertex(p[2], argb, Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom()), uv2[2]);
        v[3] = Vertex(p[3], argb, Vector2(clippingRect.GetRight(), clippingRect.GetBottom()), uv2[3]);
    }

    void UIRendererBase::DrawQuad(const Vector2* p, const Color* c)
    {
        BBAssert(p && c);

        Vertex* v = Prepare(nullptr, nullptr);
        v[0] = Vertex(p[0], c[0].ToARGB());
        v[1] = Vertex(p[1], c[1].ToARGB());
        v[2] = Vertex(p[2], c[2].ToARGB());
        v[3] = Vertex(p[3], c[3].ToARGB());
    }

    void UIRendererBase::DrawQuad(const Vector2* p, const Color* c, const Vector2* uv, Texture2D* texture)
    {
        BBAssert(p && c && uv && texture);

        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], c[0].ToARGB(), uv[0]);
        v[1] = Vertex(p[1], c[1].ToARGB(), uv[1]);
        v[2] = Vertex(p[2], c[2].ToARGB(), uv[2]);
        v[3] = Vertex(p[3], c[3].ToARGB(), uv[3]);
    }

    void UIRendererBase::DrawQuad(const Vector2* p, const Color* c, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && c && uv1 && texture1 && uv2 && texture2);

        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], c[0].ToARGB(), uv1[0], uv2[0]);
        v[1] = Vertex(p[1], c[1].ToARGB(), uv1[1], uv2[1]);
        v[2] = Vertex(p[2], c[2].ToARGB(), uv1[2], uv2[2]);
        v[3] = Vertex(p[3], c[3].ToARGB(), uv1[3], uv2[3]);
    }

    void UIRendererBase::DrawQuad(const Vector3* p, Color color)
    {
        BBAssert(p);

        const unsigned long argb = color.ToARGB();
        Vertex* v = Prepare(nullptr, nullptr);
        v[0] = Vertex(p[0], argb);
        v[1] = Vertex(p[1], argb);
        v[2] = Vertex(p[2], argb);
        v[3] = Vertex(p[3], argb);
    }

    void UIRendererBase::DrawQuad(const Vector3* p, Color color, const Vector2* uv,  Texture2D* texture)
    {
        BBAssert(p && uv && texture);

        const unsigned long argb = color.ToARGB();
        Vertex* v = Prepare(texture, nullptr);
        v[0] = Vertex(p[0], argb, uv[0]);
        v[1] = Vertex(p[1], argb, uv[1]);
        v[2] = Vertex(p[2], argb, uv[2]);
        v[3] = Vertex(p[3], argb, uv[3]);
    }

    void UIRendererBase::DrawQuad(const Vector3* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2)
    {
        BBAssert(p && uv1 && texture1 && uv2 && texture2);

        const unsigned long argb = color.ToARGB();
        Vertex* v = Prepare(texture1, texture2);
        v[0] = Vertex(p[0], argb, uv1[0], uv2[0]);
        v[1] = Vertex(p[1], argb, uv1[1], uv2[1]);
        v[2] = Vertex(p[2], argb, uv1[2], uv2[2]);
        v[3] = Vertex(p[3], argb, uv1[3], uv2[3]);
    }

    void UIRendererBase::SetGraphicsDevice(GraphicsDevice* value)
    {
        if (graphicsDevice != value)
        {
            GraphicsDevice* old = graphicsDevice;

            graphicsDevice = value;

            OnGraphicsDeviceChanged(old);
        }
    }

    void UIRendererBase::SetStorage(GameAssetStorage* value)
    {
        storage = value;
    }

    void UIRendererBase::SetShaderEffectDirectory(const String& value)
    {
        shaderEffectDirectory = value;
    }

    void UIRendererBase::SetFieldOfView(float value)
    {
        value = Math::Clamp(value, 0.0001f, Math::Pi);

        if (fieldOfView != value)
        {
            fieldOfView = value;
            lastResolution = Point2(-1, -1);
        }
    }

    UIRendererBase::Vertex* UIRendererBase::Prepare(Texture2D* texture, Texture2D* mask)
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
            lockedVertices = LockVB(vbSize);

        BBAssertDebug(selectedQuadSet);
        selectedQuadSet->Count++;
        return &lockedVertices[(selectedQuadSet->StartIndex + selectedQuadSet->Count - 1) * VerticesPerQuad];
    }

    void UIRendererBase::Flush()
    {
        if (lockedVertices)
        {
            lockedVertices = nullptr;
            UnlockVB();
        }

        const int count = sizeof(quadSets) / sizeof(quadSets[0]);
        for (int i = 0; i < count; i++)
        {
            QuadSet& item = quadSets[i];
            if (item.Count == 0)
                break;

            BeginEffect(item.Mode);
            DrawQuads(item.KeyTexture,
                      item.KeyMask,
                      item.StartIndex * VerticesPerQuad,
                      item.Count * VerticesPerQuad,
                      item.Count * TrianglesPerQuad);
            EndEffect(item.Mode);
            item.Count = 0;
        }
    }

    void UIRendererBase::BeginEffect(PixelMode mode)
    {
        if (GetGraphicsDevice()->GetCapabilities().IsShaderSupported())
        {
            const int index = static_cast<int>(mode);

            if (effects[index] == nullptr)
            {
                const char* suffix = GetShaderEffectSuffix(mode);
                effects[index] = static_cast<ShaderEffect*>(storage->Load(shaderEffectBaseURI + suffix));
            }

            if (effects[index])
            {
                OnEffectBegan(mode, effects[index]);

                for (std::vector<EffectorPtr>::const_iterator it = effectors.begin(); it != effectors.end(); it++)
                {
                    (*it)->Setup(effects[index]);
                    (*it)->Begin(this);
                }
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

    void UIRendererBase::EndEffect(PixelMode mode)
    {
        if (GetGraphicsDevice()->GetCapabilities().IsShaderSupported() == false)
        {
            if (mode == AlphaTextureOnlyMode || mode == MaskedAlphaTextureMode)
                EndAlphaTextureMode();
        }

        for (std::vector<EffectorPtr>::const_reverse_iterator it = effectors.rbegin(); it != effectors.rend(); it++)
            (*it)->End(this);

        if (GetGraphicsDevice()->GetCapabilities().IsShaderSupported())
        {
            const int index = static_cast<int>(mode);
            if (effects[index])
                OnEffectEnded(mode, effects[index]);
        }
    }

    void UIRendererBase::InitializeNormalQuadSets()
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

    void UIRendererBase::InitializeBatchQuadSets()
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

    void UIRendererBase::ReserveCachedQuads(int capacity)
    {
        BBAssert(capacity >= 0);

        vbSize = sizeof(Vertex) * VerticesPerQuad * capacity;
        OnCreateQuadsCache(vbSize, IndicesPerQuad * capacity);
    }

    void UIRendererBase::OnGraphicsDeviceChanged(GraphicsDevice* /*old*/)
    {
    }

    String UIRendererBase::MakeNormalEffectFileName(uint hint)
    {
        if (hint != 0)
        {
            char buffer[10];
            buffer[0] = '\\';
            buffer[1] = BBFOURCCFirst(hint);
            buffer[2] = BBFOURCCSecond(hint);
            buffer[3] = BBFOURCCThird(hint);
            buffer[4] = BBFOURCCFourth(hint);
            buffer[5] = 'N';
            buffer[6] = 'O';
            buffer[7] = 'R';
            buffer[8] = 'M';
            buffer[9] = '\0';
            return buffer;
        }
        else
            return "\\NORM";
    }

    UIRendererBase::PixelMode UIRendererBase::GetPixelMode(const Texture2D* texture, const Texture2D* mask)
    {
        if (texture)
        {
            if (texture->GetPixelFormat() == Texture2D::A8Pixels)
            {
                if (mask)
                    return MaskedAlphaTextureMode;
                else
                    return AlphaTextureOnlyMode;
            }
            else
            {
                if (mask)
                    return MaskedColorTextureMode;
                else
                    return ColorTextureOnlyMode;
            }
        }
        else
        {
            if (mask)
                return MaskedColorMode;
            else
                return ColorOnlyMode;
        }
    }

    const char* UIRendererBase::GetShaderEffectSuffix(PixelMode mode)
    {
        switch (mode)
        {
            case ColorOnlyMode:
                return "_A";
            case ColorTextureOnlyMode:
                return "_B";
            case AlphaTextureOnlyMode:
                return "_C";
            case MaskedColorMode:
                return "_A";
            case MaskedColorTextureMode:
                return "_B";
            case MaskedAlphaTextureMode:
                return "_C";
            default:
                return nullptr;
        }
    }

    void UIRendererBase::UpdateViewProjectionTransform()
    {
        if (graphicsDevice == nullptr)
        {
            viewTransform = Matrix4::Identity;
            viewTransformInv = Matrix4::Identity;
            projectionTransform = Matrix4::Identity;
            projectionTransformInv = Matrix4::Identity;
            return;
        }

        const Point2 currentResolution = graphicsDevice->GetResolution();
        if (currentResolution != lastResolution)
        {
            const Vector2 viewportSize = Vector2(currentResolution.X, currentResolution.Y);
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
            // projectionTransform = Matrix4::Ortho(viewportSize.X, viewportSize.Y, 0.1f, 10000.0f);

            viewTransformInv = Matrix4::Inversion(viewTransform);
            projectionTransformInv = Matrix4::Inversion(projectionTransform);

            lastResolution = currentResolution;
        }
    }
}