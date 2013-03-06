#pragma once
#ifndef __BIBIM_UIRENDERER_DX9_H__
#define __BIBIM_UIRENDERER_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIRendererBase.h>
#   include <Bibim/BlendMode.h>
#   include <Bibim/GLES2.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
#   include <Bibim/String.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        class UIRenderer : public UIRendererBase
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

                void DrawTriangles(int count, const Vector2* p, Color color);

            private:
                virtual Vertex* LockVB(int size);
                virtual void UnlockVB();
                virtual void DrawQuads(Texture2D* texture, Texture2D* mask, int vertexStart, int numberOfVertices, int numberOfQuads);

                virtual void OnCreateQuadsCache(int vbSize, int numberOfIndices);
                virtual void OnEffectBegan(PixelMode mode, ShaderEffect* effect);
                virtual void OnEffectEnded(PixelMode mode, ShaderEffect* effect);
                virtual void OnTransformChanged(const Matrix4& newValue);
                virtual void OnBlendModeChanged(BlendMode newValue);

                inline void DrawArrays(GLenum primitiveType, int numberOfVertices);
                inline void DrawArrays(GLenum primitiveType, int numberOfVertices, Texture2D* texture);
                inline void DrawArrays(GLenum primitiveType, int numberOfVertices, Texture2D* texture, Texture2D* mask);
                void DrawArraysActually(GLenum primitiveType, PixelMode pixelMode, int numberOfVertices, Texture2D* texture, Texture2D* mask);

            private:
                Matrix4 mvpTransform;
                std::vector<Vertex> vb;
                std::vector<ushort> ib;

                friend class UIOpacityMaskEffect;
        };
    }

#   include <Bibim/UIRenderer.GLES2.inl>

#endif