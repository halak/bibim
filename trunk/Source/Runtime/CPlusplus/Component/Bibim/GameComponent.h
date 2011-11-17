#pragma once
#ifndef __BIBIM_GAMECOMPONENT_H__
#define __BIBIM_GAMECOMPONENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/CloningContext.h>

    namespace Bibim
    {
#       define BBAbstractComponentClass(classname, parent)      private: \
                                                                    typedef classname This; \
                                                                    typedef parent Base; \
                                                                protected: \
                                                                    virtual void OnRead(Bibim::ComponentStreamReader& reader); \
                                                                    virtual void OnCopy(const Bibim::GameComponent* original, Bibim::CloningContext& context); \
                                                                private:

#       define BBComponentClass(classname, parent, a, b, c, d)  BBAbstractComponentClass(classname, parent); \
                                                                public: \
                                                                    static const int ClassID = BBMakeFOURCC(a, b, c, d); \
                                                                    virtual int GetClassID() const { return ClassID; } \
                                                                    virtual classname* Clone() const; \
                                                                protected: \
                                                                    virtual classname* Clone(Bibim::CloningContext& context) const; \
                                                                private:
#       define BBSingletonComponentClass(classname, parent, a, b, c, d) BBComponentClass(classname, parent, a, b, c, d); \
                                                                        public: \
                                                                            static const SharedPointer<classname> Instance; \
                                                                        private: \
                                                                            classname();

#       define BBImplementsComponent(classname) classname* classname::Clone() const \
                                                { \
                                                    CloningContext context; \
                                                    return Clone(context); \
                                                } \
                                                classname* classname::Clone(Bibim::CloningContext& context) const \
                                                { \
                                                    classname* clone = new classname(); \
                                                    context.Store(this, clone); \
                                                    clone->OnCopy(this, context); \
                                                    return clone; \
                                                }
#       define BBImplementsSingletonComponent(classname)    classname::classname() { } \
                                                            classname* classname::Clone() const \
                                                            { \
                                                                return const_cast<classname*>(this); \
                                                            } \
                                                            classname* classname::Clone(Bibim::CloningContext& /*context*/) const \
                                                            { \
                                                                return const_cast<classname*>(this); \
                                                            } \
                                                            void classname::OnRead(Bibim::ComponentStreamReader& reader) \
                                                            { \
                                                                Base::OnRead(reader); \
                                                            } \
                                                            void classname::OnCopy(const Bibim::GameComponent* original, Bibim::CloningContext& context) \
                                                            { \
                                                                Base::OnCopy(original, context); \
                                                            } \
                                                            const SharedPointer<classname> classname::Instance = new classname();

        class GameComponent : public SharedObject
        {
            BBAbstractComponentClass(GameComponent, SharedObject);
            BBThisIsNoncopyableClass(GameComponent);
            public:
                virtual ~GameComponent();

                virtual GameComponent* Clone() const;

            protected:
                GameComponent();

                virtual GameComponent* Clone(CloningContext& context) const = 0;

            private:
                friend class CloningContext;
                friend class ComponentStreamReader;
        };
    }

#   include <Bibim/GameComponent.inl>

#endif