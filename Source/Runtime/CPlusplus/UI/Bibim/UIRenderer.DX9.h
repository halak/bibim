#pragma once
#ifndef __BIBIM_UIRENDERER_DX9_H__
#define __BIBIM_UIRENDERER_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
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
        class UIRenderer : public GameModule
        {
            BBModuleClass(UIRenderer, GameModule, 'U', 'I', 'R', 'R');
            public:
                class Effector : public SharedObject
                {
                    public:
                        virtual ~Effector() { }

                        virtual void Setup(ShaderEffect* /*effect*/) { }
                        virtual void Begin(UIRenderer* /*renderer*/) { }
                        virtual void End(UIRenderer* /*renderer*/) { }

                        inline uint32 GetEffectName() const;
                        inline bool IsSetupEnabled() const;
                        inline bool IsBeginEndEnabled() const;

                    protected:
                        inline Effector(uint32 effectName, bool setupEnabled, bool beginEndEnabled);

                    private:
                        uint32 effectName;
                        bool setupEnabled;
                        bool beginEndEnabled;
                        char reserved[2];
                };
                typedef SharedPointer<Effector> EffectorPtr;

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
                struct VertexCO // Color Only
                {
                    D3DXVECTOR3 Position;
                    D3DCOLOR Color;

                    inline VertexCO(D3DXVECTOR3 position, D3DCOLOR color);

                    static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
                };

                struct VertexST : VertexCO // Single Textured
                {
                    D3DXVECTOR2 Texture;

                    inline VertexST(D3DXVECTOR3 position, D3DCOLOR color, D3DXVECTOR2 texture);

                    static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
                };

                struct VertexDT : VertexCO // Double Textured
                {
                    D3DXVECTOR2 Texture1;
                    D3DXVECTOR2 Texture2;

                    inline VertexDT(D3DXVECTOR3 position, D3DCOLOR color, D3DXVECTOR2 texture1, D3DXVECTOR2 texture2);

                    static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2;
                };

                struct QuadSetCO
                {
                    int StartIndex;
                    int Count;
                    int Capacity;

                    inline QuadSetCO();
                };

                struct QuadSetST : QuadSetCO
                {
                    Texture2DPtr KeyTexture;
                };

                struct QuadSetDT : QuadSetCO
                {
                    Texture2DPtr KeyTexture;
                    Texture2DPtr KeyMask;
                };

                enum PixelEffectMode
                {
                    NoTextureMode,
                    ColorTextureMode,
                    AlphaTextureMode,
                    ColorAndAlphaTextureMode,
                    PixelEffectModeCount,
                };

            private:
                void InitializeNormalQuadSets();
                void InitializeBatchQuadSets();

                VertexCO* PrepareCO();
                VertexST* PrepareST(Texture2D* texture);
                VertexDT* PrepareDT(Texture2D* texture1, Texture2D* texture2);

                void BeginAlphaTextureMode();
                void EndAlphaTextureMode();
                void BeginEffect(int index, const char* key);
                void EndEffect(int index);

                void Flush();
                void ReserveCachedQuads(int capacity);
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
                BlendMode blendMode;

                ShaderEffectPtr          effects[PixelEffectModeCount];
                std::vector<EffectorPtr> effectors;
                String shaderEffectBaseURI;

                IDirect3DStateBlock9* d3dStateBlock;
                IDirect3DVertexBuffer9* d3dVBCO;
                IDirect3DVertexBuffer9* d3dVBSCT;
                IDirect3DVertexBuffer9* d3dVBSAT;
                IDirect3DVertexBuffer9* d3dVBDT;
                IDirect3DIndexBuffer9* d3dQuadIndices;
                int vbcoSize;
                int vbsctSize;
                int vbsatSize;
                int vbdtSize;
                VertexCO* lockedVBCO;
                VertexST* lockedVBSCT;
                VertexST* lockedVBSAT;
                VertexDT* lockedVBDT;
                QuadSetCO quadSetCO;
                QuadSetST quadSetsSCT[8];
                QuadSetST quadSetsSAT[8];
                QuadSetDT quadSetsDT[8];

                bool isBatching;

                Rect lastViewport;

                static const int TrianglesPerQuad;
                static const int VerticesPerQuad;
                static const int IndicesPerQuad;
        };
    }

#   include <Bibim/UIRenderer.DX9.inl>

#endif