#pragma once
#ifndef __BIBIM_UIRENDERER_DX9_H__
#define __BIBIM_UIRENDERER_DX9_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_USE_DIRECTX9))

#include <Bibim/UIRendererBase.h>
#include <Bibim/GraphicsDevice.h>
#include <d3dx9.h>

namespace Bibim
{
    class UIRenderer : public UIRendererBase, public GraphicsDevice::LostEventListener
    {
        BBModuleClass(UIRenderer, UIRendererBase, 'U', 'I', 'R', 'R');
        public:
            UIRenderer();
            UIRenderer(GraphicsDevice* graphicsDevice, GameAssetStorage* storage, const String& shaderEffectDirectory);
            virtual ~UIRenderer();

            virtual void Begin();
            virtual void End();

            void DrawLines(int count, const Vector2* p,       Color color);
            void DrawLines(int count, const Vector2* p, const Color* c);

            void DrawDebugLines(int count, const Vector2* p,       Color color);
            void DrawDebugLines(int count, const Vector2* p, const Color* c);

            void DrawTriangles(int count, const Vector2* p, Color color);

        private:
            virtual void BeginAlphaTextureMode();
            virtual void EndAlphaTextureMode();
            virtual void BeginOpacityMaskMode();
            virtual void EndOpacityMaskMode();

            virtual Vertex* LockVB(int size);
            virtual void UnlockVB();
            virtual void DrawQuads(Texture2D* texture, Texture2D* mask, int vertexStart, int numberOfVertices, int numberOfQuads);

            virtual void OnCreateQuadsCache(int vbSize, int numberOfIndices);
            virtual void OnEffectBegan(PixelMode mode, ShaderEffect* effect);
            virtual void OnEffectEnded(PixelMode mode, ShaderEffect* effect);
            virtual void OnTransformChanged(const Matrix4& newValue);
            virtual void OnBlendModeChanged(BlendMode newValue);

            inline void DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives);
            inline void DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives, Texture2D* texture);
            inline void DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives, Texture2D* texture, Texture2D* mask);
            void DrawPrimitivesActually(D3DPRIMITIVETYPE primitiveType, PixelMode pixelMode, int numberOfPrimitives, Texture2D* texture, Texture2D* mask);

            virtual void OnGraphicsDeviceChanged(GraphicsDevice* old);
            virtual void OnGraphicsDeviceLost(GraphicsDeviceBase* g);

        private:
            D3DXMATRIX d3dMVPTransform;

            IDirect3DStateBlock9* d3dStateBlock;
            IDirect3DVertexBuffer9* vb;
            IDirect3DIndexBuffer9*  ib;
            ID3DXLine* d3dLine;

            static const DWORD VertexFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void UIRenderer::DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives)
    {
        DrawPrimitivesActually(primitiveType, ColorOnlyMode, numberOfPrimitives, nullptr, nullptr);
    }

    void UIRenderer::DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives, Texture2D* texture)
    {
        DrawPrimitivesActually(primitiveType, ColorTextureOnlyMode, numberOfPrimitives, texture, nullptr);
    }

    void UIRenderer::DrawPrimitives(D3DPRIMITIVETYPE primitiveType, int numberOfPrimitives, Texture2D* texture, Texture2D* mask)
    {
        DrawPrimitivesActually(primitiveType, MaskedColorTextureMode, numberOfPrimitives, texture, mask);
    }
}

#endif
#endif