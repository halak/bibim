#pragma once
#ifndef __BIBIM_UIRENDERERBASE_H__
#define __BIBIM_UIRENDERERBASE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <list>

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
                        virtual void Begin(UIRenderer* /*renderer*/) { }
                        virtual void End(UIRenderer* /*renderer*/) { }

                        inline uint32 GetShaderEffectNameHint() const;
                        inline bool IsMaskEffector() const;

                    protected:
                        inline Effector();
                        inline Effector(uint32 shaderEffectNameHint);
                        inline Effector(bool isMaskEffector);
                        inline Effector(uint32 shaderEffectNameHint, bool isMaskEffector);

                    private:
                        uint32 shaderEffectNameHint;
                        bool isMaskEffector;
                        bool reserved[2];
                };
                typedef SharedPointer<Effector> EffectorPtr;

            public:
                virtual ~UIRendererBase();

            protected:
                UIRendererBase();
        };

#define BBEffectorClass(classname)
//#       define BBEffectorClass(classname)   public: \
//                                                static void* operator new (size_t /*s*/) \
//                                                { \
//                                                    return UIEffectorAllocator<classname>::Instance.Allocate(); \
//                                                } \
//                                                static void operator delete (void* p) \
//                                                { \
//                                                    UIEffectorAllocator<classname>::Instance.Deallocate(p); \
//                                                }
//
//        template <typename T> class UIEffectorAllocator
//        {
//            public:
//                static UIEffectorAllocator Instance;
//
//            public:
//                void* Allocate()
//                {
//                    if (dynamicPool.empty())
//                        dynamicPool.push_back(new byte[sizeof(T)]);
//
//                    void* n = dynamicPool.front();
//                    dynamicPool.pop_front();
//                    return n;
//                }
//
//                void Deallocate(void* item)
//                {
//                    dynamicPool.push_front(item);
//                }
//
//            private:
//                UIEffectorAllocator()
//                {
//                }
//
//            private:
//                //byte fixedMem[sizeof(T)][64];
//                //bool fixedAlloc[64];
//                std::list<void*> dynamicPool;
//        };
    }

#   include <Bibim/UIRendererBase.inl>

#endif