#pragma once
#ifndef __BIBIM_UIRENDERER_DX9_H__
#define __BIBIM_UIRENDERER_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIRendererBase.h>
#   include <Bibim/BlendMode.h>
#   include <Bibim/Matrix4.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
#   include <Bibim/String.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <deque>
#   include <vector>
#   include <d3dx9.h>

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

                void DrawLines(int count, const Vector2* p, Color color);
                void DrawLines(int count, const Vector2* p, Color* c);

                void DrawTriangles(int count, const Vector2* p, Color color);

                void DrawQuad(const Vector2* p, Color color);
                void DrawQuad(const Vector2* p, Color color, const Vector2* uv,  Texture2D* texture);
                void DrawQuad(const Vector2* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

                void DrawQuad(const Vector2* p, Color color, const RectF& clippingRect,  Texture2D* texture);
                void DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

                void DrawQuad(const Vector2* p, Color* c);
                void DrawQuad(const Vector2* p, Color* c, const Vector2* uv,  Texture2D* texture);
                void DrawQuad(const Vector2* p, Color* c, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

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
                struct Vertex
                {
                    D3DXVECTOR3 Position;
                    D3DCOLOR Color;
                    D3DXVECTOR2 TexCoord1;
                    D3DXVECTOR2 TexCoord2;

                    inline Vertex(Vector2 position, D3DCOLOR color);
                    inline Vertex(Vector2 position, D3DCOLOR color, Vector2 texCoord1);
                    inline Vertex(Vector2 position, D3DCOLOR color, Vector2 texCoord1, Vector2 texCoord2);

                    static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2;
                };

                enum PixelMode
                {
                    ColorOnlyMode,
                    ColorTextureOnlyMode,
                    AlphaTextureOnlyMode,
                    MaskedColorMode,
                    MaskedColorTextureMode,
                    MaskedAlphaTextureMode,
                    NumberOfPixelModes,
                };

                struct QuadSet
                {
                    int Count;
                    Texture2DPtr KeyTexture;
                    Texture2DPtr KeyMask;
                    PixelMode Mode;
                    int StartIndex;
                    int Capacity;

                    inline QuadSet();
                };

            private:
                void InitializeNormalQuadSets();
                void InitializeBatchQuadSets();

                static PixelMode GetPixelMode(const Texture2D* texture, const Texture2D* mask);
                Vertex* Prepare(Texture2D* texture, Texture2D* mask);

                void BeginAlphaTextureMode();
                void EndAlphaTextureMode();
                void BeginEffect(PixelMode mode);
                void EndEffect(PixelMode mode);
                void BeginOpacityMaskMode();
                void EndOpacityMaskMode();

                void Flush();
                void ReserveCachedQuads(int capacity);
                void UpdateViewProjectionTransform();

                inline void DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives);
                inline void DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives, Texture2D* texture);
                inline void DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives, Texture2D* texture, Texture2D* mask);
                void DrawPrimitivesActually(D3DPRIMITIVETYPE primitiveType, PixelMode pixelMode, int numberOfPrimitives, Texture2D* texture, Texture2D* mask);

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
                D3DXMATRIX d3dMVPTransform;
                BlendMode blendMode;

                ShaderEffectPtr          effects[NumberOfPixelModes];
                std::vector<EffectorPtr> effectors;
                String shaderEffectBaseURI;

                IDirect3DStateBlock9* d3dStateBlock;
                IDirect3DVertexBuffer9* vb;
                IDirect3DIndexBuffer9*  ib;
                Vertex* lockedVertices;
                int vbSize;

                QuadSet quadSets[8];

                bool isBatching;

                Rect lastViewport;

                static const int TrianglesPerQuad;
                static const int VerticesPerQuad;
                static const int IndicesPerQuad;

                friend class UIOpacityMaskEffect;
        };
    }

#   include <Bibim/UIRenderer.DX9.inl>

#endif