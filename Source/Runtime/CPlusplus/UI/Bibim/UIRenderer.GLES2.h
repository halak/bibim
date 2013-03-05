#pragma once
#ifndef __BIBIM_UIRENDERER_DX9_H__
#define __BIBIM_UIRENDERER_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIRendererBase.h>
#   include <Bibim/BlendMode.h>
#   include <Bibim/GLES2.h>
#   include <Bibim/Matrix4.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
#   include <Bibim/String.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <deque>
#   include <vector>

    namespace Bibim
    {
        class UIRenderer : public UIRendererBase
        {
            BBModuleClass(UIRenderer, GameModule, 'U', 'I', 'R', 'R');
            public:
                UIRenderer();
                UIRenderer(GraphicsDevice* graphicsDevice, GameAssetStorage* storage, const String& shaderEffectDirectory);
                virtual ~UIRenderer();

                void Begin();
                void End();

                void BeginBatch();
                void EndBatch();

                void Setup(const Matrix4& worldTransform);
                void Setup(const std::vector<EffectorPtr>& effectors);
                BlendMode Setup(BlendMode value);

                void DrawLines(int count, const Vector2* p,       Color color);
                void DrawLines(int count, const Vector2* p, const Color* c);

                void DrawTriangles(int count, const Vector2* p, Color color);

                void DrawQuad(const Vector2* p, Color color);
                void DrawQuad(const Vector2* p, Color color, const Vector2* uv,  Texture2D* texture);
                void DrawQuad(const Vector2* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

                void DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture);
                void DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

                void DrawQuad(const Vector2* p, const Color* c);
                void DrawQuad(const Vector2* p, const Color* c, const Vector2* uv,  Texture2D* texture);
                void DrawQuad(const Vector2* p, const Color* c, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

                void DrawQuad(const Vector3* p, Color color);
                void DrawQuad(const Vector3* p, Color color, const Vector2* uv,  Texture2D* texture);
                void DrawQuad(const Vector3* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

                inline GraphicsDevice* GetGraphicsDevice() const;
                void SetGraphicsDevice(GraphicsDevice* value);

                inline GameAssetStorage* GetStorage() const;
                void SetStorage(GameAssetStorage* value);

                inline const String& GetShaderEffectDirectory() const;
                void SetShaderEffectDirectory(const String& value);

                inline float GetFieldOfView() const;
                void SetFieldOfView(float value);

                inline const Matrix4& GetViewTransform();
                inline const Matrix4& GetProjectionTransform();
                inline const Matrix4& GetInversedViewTransform();
                inline const Matrix4& GetInversedProjectionTransform();

            private:
                void BeginEffect(PixelMode mode);
                void EndEffect(PixelMode mode);

                void UpdateViewProjectionTransform();

            private:
                GraphicsDevice* graphicsDevice;
                GameAssetStorage* storage;
                String shaderEffectDirectory;
                float fieldOfView;
                Matrix4 viewTransform;
                Matrix4 viewTransformInv;
                Matrix4 projectionTransform;
                Matrix4 projectionTransformInv;
                Matrix4 worldTransform;
                Matrix4 mvpTransform;
                BlendMode blendMode;

                ShaderEffectPtr          effects[NumberOfPixelModes];
                std::vector<EffectorPtr> effectors;
                String shaderEffectBaseURI;

                Rect lastViewport;

                static const int TrianglesPerQuad;
                static const int VerticesPerQuad;
                static const int IndicesPerQuad;

                friend class UIOpacityMaskEffect;
        };
    }

#   include <Bibim/UIRenderer.GLES2.inl>

#endif