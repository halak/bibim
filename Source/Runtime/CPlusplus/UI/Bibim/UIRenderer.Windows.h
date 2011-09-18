#pragma once
#ifndef __BIBIM_UIRENDERER_WINDOWS_H__
#define __BIBIM_UIRENDERER_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Matrix4.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <deque>
#   include <d3dx9.h>

    namespace Bibim
    {
        class UIRenderer : public GameModule
        {
            BBGameModuleClass('U', 'I', 'R', 'R');
            public:
                UIRenderer();
                UIRenderer(GraphicsDevice* graphicsDevice);
                virtual ~UIRenderer();

                void Begin();
                void End();

                void EnterStringRenderMode();
                void LeaveStringRenderMode();

                void Draw(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, const RectF& clippingRect, Texture2D* texture, Color color);
                void Draw(int count, const Vector2* points, Color color);

                inline GraphicsDevice* GetGraphicsDevice() const;
                void SetGraphicsDevice(GraphicsDevice* value);

                inline float GetFieldOfView() const;
                void SetFieldOfView(float value);

                inline const Matrix4& GetViewTransform();
                inline const Matrix4& GetProjectionTransform();
                inline const Matrix4& GetInversedViewTransform();
                inline const Matrix4& GetInversedProjectionTransform();

            private:
                int PrepareCache(const RectF bounds, Texture2D* texture);

            private:
                struct Vertex
                {
                    D3DXVECTOR3 Position;
                    D3DCOLOR    Color;
                    D3DXVECTOR2 Texture;

                    inline Vertex();
                    inline Vertex(D3DXVECTOR3 position);
                    inline Vertex(D3DXVECTOR3 position, D3DCOLOR color);
                    inline Vertex(D3DXVECTOR3 position, D3DCOLOR color, D3DXVECTOR2 texture);

                    static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
                    static const DWORD NoTexturedFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
                };

                struct AlphaTexturedVertex : Vertex
                {
                    D3DXVECTOR2 AlphaTexture;

                    inline AlphaTexturedVertex();
                    inline AlphaTexturedVertex(D3DXVECTOR3 position);
                    inline AlphaTexturedVertex(D3DXVECTOR3 position, D3DCOLOR color);
                    inline AlphaTexturedVertex(D3DXVECTOR3 position, D3DCOLOR color, D3DXVECTOR2 texture, D3DXVECTOR2 alphaTexture);

                    static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2;
                };

                struct QuadSet
                {
                    int StartIndex;
                    int Count;
                    Texture2DPtr Texture;
                    void* Effect;
                    RectF Bounds;

                    inline QuadSet();
                };

            private:
                void Flush();
                void FlushAndLock();
                void ReserveCachedQuads(int capacity);
                void UpdateViewProjectionTransform();

            private:
                GraphicsDevice* graphicsDevice;
                float fieldOfView;
                Matrix4 viewTransform;
                Matrix4 viewTransformInv;
                Matrix4 projectionTransform;
                Matrix4 projectionTransformInv;

                IDirect3DVertexBuffer9* vb;
                IDirect3DIndexBuffer9* ib;
                QuadSet cachedQuadSets[8];
                int numberOfActiveQuadSets;
                
                Vertex* lockedVertices;
                int vbSize;
                int capacityPerQuad;

                Rect lastViewport;

                static const unsigned short TrianglesPerQuad;
                static const unsigned short VerticesPerQuad;
                static const unsigned short IndicesPerQuad;

            private:
                 struct OldRenderState
                 {
                     D3DRENDERSTATETYPE State;
                     DWORD Value;

                     OldRenderState(D3DRENDERSTATETYPE state, DWORD value);
                 };

                 struct OldTextureStageState
                 {
                     DWORD Stage;
                     D3DTEXTURESTAGESTATETYPE Type;
                     DWORD Value;

                     OldTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value);
                 };

                 struct OldSamplerState
                 {
                     DWORD Sampler;
                     D3DSAMPLERSTATETYPE Type;
                     DWORD Value;

                     OldSamplerState(DWORD sampler, D3DSAMPLERSTATETYPE type, DWORD value);
                 };

                 std::deque<OldRenderState>       oldRenderStates;
                 std::deque<OldTextureStageState> oldTextureStageStates;
                 std::deque<OldSamplerState>      oldSamplerStates;
        };
    }

#   include <Bibim/UIRenderer.Windows.inl>

#endif