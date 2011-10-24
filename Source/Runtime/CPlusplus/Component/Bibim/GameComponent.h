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
                                                                    static const uint32 ClassID = BBMakeFOURCC(a, b, c, d); \
                                                                    virtual uint32 GetClassID() const { return ClassID; } \
                                                                    virtual classname* Clone() const; \
                                                                protected: \
                                                                    virtual classname* Clone(Bibim::CloningContext& context) const; \
                                                                private:

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

        class GameComponent : public SharedObject
        {
            BBAbstractComponentClass(GameComponent, SharedObject);
            BBThisIsNoncopyableClass(GameComponent);
            public:
                static const uint UnspecifiedID;

            public:
                virtual ~GameComponent();

                virtual GameComponent* Clone() const;

                inline uint GetID() const;
                inline void SetID(uint value);

            protected:
                GameComponent();
                GameComponent(uint id);

                virtual GameComponent* Clone(CloningContext& context) const = 0;

            private:
                uint id;

                friend class CloningContext;
                friend class ComponentStreamReader;
        };
    }

#   include <Bibim/GameComponent.inl>

#endif