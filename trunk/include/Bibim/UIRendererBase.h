#pragma once
#ifndef __BIBIM_UIRENDERERBASE_H__
#define __BIBIM_UIRENDERERBASE_H__

#include <Bibim/FWD.h>
#include <Bibim/GameModule.h>
#include <Bibim/BlendMode.h>
#include <Bibim/Matrix4.h>
#include <Bibim/String.h>
#include <Bibim/Texture2D.h>
#include <vector>
#include <list>

namespace Bibim
{
    class UIRendererBase : public GameModule
    {
        BBAbstractModuleClass(UIRendererBase, GameModule);
        public:
            class Effector : public SharedObject
            {
                public:
                    virtual ~Effector() { }

                    virtual void Setup(ShaderEffect* /*effect*/) { }
                    virtual void Begin(UIRendererBase* /*renderer*/) { }
                    virtual void End(UIRendererBase* /*renderer*/) { }

                    inline int GetShaderEffectNameHint() const;
                    inline bool IsMaskEffector() const;

                protected:
                    inline Effector();
                    inline Effector(int shaderEffectNameHint);
                    inline Effector(bool isMaskEffector);
                    inline Effector(int shaderEffectNameHint, bool isMaskEffector);

                private:
                    int shaderEffectNameHint;
                    bool isMaskEffector;
            };
            typedef SharedPointer<Effector> EffectorPtr;

        public:
            virtual ~UIRendererBase();

            virtual void Begin();
            virtual void End();

            void BeginBatch();
            void EndBatch();

            void Setup(const Matrix4& worldTransform);
            void Setup(const std::vector<EffectorPtr>& effectors);
            BlendMode Setup(BlendMode blendMode);

            void DrawQuad(const Vector2* p, Color color);
            void DrawQuad(const Vector2* p, Color color, const Vector2* uv,  Texture2D* texture);
            void DrawQuad(const Vector2* p, Color color, const Vector2* uv1, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

            void DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture);
            void DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

            void DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, int alphaChannel, Texture2D* texture);
            void DrawQuad(const Vector2* p, Color color, const RectF& clippingRect, int alphaChannel, Texture2D* texture1, const Vector2* uv2, Texture2D* texture2);

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

        protected:
            UIRendererBase(uint effectFileFormatHint);
            UIRendererBase(uint effectFileFormatHint, GraphicsDevice* graphicsDevice, GameAssetStorage* storage, const String& shaderEffectDirectory);

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

            struct Vertex
            {
                Vector3 Position;
                unsigned long Color;
                Vector3 TexCoord1;
                Vector2 TexCoord2;

                inline Vertex();
                inline Vertex(const Vertex& original);

                inline Vertex(Vector2 position, unsigned long color);
                inline Vertex(Vector2 position, unsigned long color, Vector2 texCoord1);
                inline Vertex(Vector2 position, unsigned long color, Vector2 texCoord1, Vector2 texCoord2);

                inline Vertex(Vector2 position, unsigned long color, Vector2 texCoord1, int component);
                inline Vertex(Vector2 position, unsigned long color, Vector2 texCoord1, int component, Vector2 texCoord2);

                inline Vertex(Vector3 position, unsigned long color);
                inline Vertex(Vector3 position, unsigned long color, Vector2 texCoord1);
                inline Vertex(Vector3 position, unsigned long color, Vector2 texCoord1, Vector2 texCoord2);
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

            virtual void BeginAlphaTextureMode() { }
            virtual void EndAlphaTextureMode() { }
            virtual void BeginOpacityMaskMode() { }
            virtual void EndOpacityMaskMode() { }
            void BeginEffect(PixelMode mode);
            void EndEffect(PixelMode mode);

            void Flush();
            void ReserveCachedQuads(int capacity);

            virtual Vertex* LockVB(int size) = 0;
            virtual void UnlockVB() = 0;
            virtual void DrawQuads(Texture2D* texture, Texture2D* mask, int vertexStart, int numberOfVertices, int numberOfQuads) = 0;

            virtual void OnCreateQuadsCache(int vbSize, int numberOfIndices) = 0;
            virtual void OnEffectBegan(PixelMode mode, ShaderEffect* effect) = 0;
            virtual void OnEffectEnded(PixelMode mode, ShaderEffect* effect) = 0;
            virtual void OnTransformChanged(const Matrix4& newValue) = 0;
            virtual void OnBlendModeChanged(BlendMode newValue) = 0;
            
            virtual void OnGraphicsDeviceChanged(GraphicsDevice* old);

        protected:
            static const int TrianglesPerQuad = 2;
            static const int VerticesPerQuad = 4;
            static const int IndicesPerQuad = 6;

        private:
            void InitializeNormalQuadSets();
            void InitializeBatchQuadSets();

            Vertex* Prepare(Texture2D* texture, Texture2D* mask);

            void UpdateViewProjectionTransform();

            static String MakeNormalEffectFileName(uint hint);

            static PixelMode GetPixelMode(const Texture2D* texture, const Texture2D* mask);

            static const char* GetShaderEffectSuffix(PixelMode mode);

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

            ShaderEffectPtr          effects[NumberOfPixelModes];
            std::vector<EffectorPtr> effectors;
            String shaderEffectBaseURI;

            Vertex* lockedVertices;
            int vbSize;
            QuadSet quadSets[8];

            bool isBatching;

            Point2 lastViewportSize;

            uint effectFileFormatHint;
            String normalEffectFileName;

            friend class UIOpacityMaskEffect;
    };

#   define BBEffectorClass(classname)
//#   define BBEffectorClass(classname)   public: \
//                                            static void* operator new (size_t /*s*/) \
//                                            { \
//                                                return UIEffectorAllocator<classname>::Instance.Allocate(); \
//                                            } \
//                                            static void operator delete (void* p) \
//                                            { \
//                                                UIEffectorAllocator<classname>::Instance.Deallocate(p); \
//                                            }
//
//    template <typename T> class UIEffectorAllocator
//    {
//        public:
//            static UIEffectorAllocator Instance;
//
//        public:
//            void* Allocate()
//            {
//                if (dynamicPool.empty())
//                    dynamicPool.push_back(new byte[sizeof(T)]);
//
//                void* n = dynamicPool.front();
//                dynamicPool.pop_front();
//                return n;
//            }
//
//            void Deallocate(void* item)
//            {
//                dynamicPool.push_front(item);
//            }
//
//        private:
//            UIEffectorAllocator()
//            {
//            }
//
//        private:
//            //byte fixedMem[sizeof(T)][64];
//            //bool fixedAlloc[64];
//            std::list<void*> dynamicPool;
//    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRendererBase::Vertex::Vertex()
    {
    }

    UIRendererBase::Vertex::Vertex(const Vertex& original)
        : Position(original.Position),
          Color(original.Color),
          TexCoord1(original.TexCoord1),
          TexCoord2(original.TexCoord2)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector2 position, unsigned long color)
        : Position(position, 0.0f),
          Color(color)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector2 position, unsigned long color, Vector2 texCoord1)
        : Position(position, 0.0f),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y, 3.0f)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector2 position, unsigned long color, Vector2 texCoord1, Vector2 texCoord2)
        : Position(position.X, position.Y, 0.0f),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y, 3.0f),
          TexCoord2(texCoord2)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector2 position, unsigned long color, Vector2 texCoord1, int component)
        : Position(position, 0.0f),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y, static_cast<float>(component))
    {
    }

    UIRendererBase::Vertex::Vertex(Vector2 position, unsigned long color, Vector2 texCoord1, int component, Vector2 texCoord2)
        : Position(position.X, position.Y, 0.0f),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y, static_cast<float>(component)),
          TexCoord2(texCoord2)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector3 position, unsigned long color)
        : Position(position),
          Color(color)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector3 position, unsigned long color, Vector2 texCoord1)
        : Position(position),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y, 3.0f)
    {
    }

    UIRendererBase::Vertex::Vertex(Vector3 position, unsigned long color, Vector2 texCoord1, Vector2 texCoord2)
        : Position(position),
          Color(color),
          TexCoord1(texCoord1.X, texCoord1.Y, 3.0f),
          TexCoord2(texCoord2)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRendererBase::QuadSet::QuadSet()
        : Count(0),
          StartIndex(0),
          Capacity(0)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIRendererBase::Effector::Effector()
        : shaderEffectNameHint(0x00000000),
          isMaskEffector(false)
    {
    }

    UIRendererBase::Effector::Effector(int shaderEffectNameHint)
        : shaderEffectNameHint(shaderEffectNameHint),
          isMaskEffector(false)
    {
    }

    UIRendererBase::Effector::Effector(bool isMaskEffector)
        : shaderEffectNameHint(0x00000000),
          isMaskEffector(isMaskEffector)
    {
    }

    UIRendererBase::Effector::Effector(int shaderEffectNameHint, bool isMaskEffector)
        : shaderEffectNameHint(shaderEffectNameHint),
          isMaskEffector(isMaskEffector)
    {
    }

    int UIRendererBase::Effector::GetShaderEffectNameHint() const
    {
        return shaderEffectNameHint;
    }

    bool UIRendererBase::Effector::IsMaskEffector() const
    {
        return isMaskEffector;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GraphicsDevice* UIRendererBase::GetGraphicsDevice() const
    {
        return graphicsDevice;
    }

    GameAssetStorage* UIRendererBase::GetStorage() const
    {
        return storage;
    }

    const String& UIRendererBase::GetShaderEffectDirectory() const
    {
        return shaderEffectDirectory;
    }

    float UIRendererBase::GetFieldOfView() const
    {
        return fieldOfView;
    }

    const Matrix4& UIRendererBase::GetViewTransform()
    {
        UpdateViewProjectionTransform();
        return viewTransform;
    }

    const Matrix4& UIRendererBase::GetProjectionTransform()
    {
        UpdateViewProjectionTransform();
        return projectionTransform;
    }

    const Matrix4& UIRendererBase::GetInversedViewTransform()
    {
        UpdateViewProjectionTransform();
        return viewTransformInv;
    }

    const Matrix4& UIRendererBase::GetInversedProjectionTransform()
    {
        UpdateViewProjectionTransform();
        return projectionTransformInv;
    }
}

#endif