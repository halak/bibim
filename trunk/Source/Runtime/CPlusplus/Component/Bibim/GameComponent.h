#pragma once
#ifndef __BIBIM_GAMECOMPONENT_H__
#define __BIBIM_GAMECOMPONENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>

    namespace Bibim
    {
#       define BBAbstractComponentClass(classname, parent)      private: \
                                                                    typedef classname This; \
                                                                    typedef parent Base; \
                                                                protected: \
                                                                    virtual void OnRead(ComponentStreamReader& reader); \
                                                                    virtual void OnCopy(const GameComponent* original, CloningContext& context); \
                                                                private:

#       define BBComponentClass(classname, parent, a, b, c, d)  BBAbstractComponentClass(classname, parent); \
                                                                public: \
                                                                    static const uint32 ClassID = BBMakeFOURCC(a, b, c, d); \
                                                                    virtual uint32 GetClassID() const { return ClassID; } \
                                                                    virtual classname* Clone(CloningContext& context) const; \
                                                                private:

#       define BBImplementsComponent(classname) classname* classname::Clone(CloningContext& /*context*/) const \
                                                { \
                                                    classname* clone = new classname(); \
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

                        GameComponent* Clone() const;
                virtual GameComponent* Clone(CloningContext& context) const = 0;

                inline uint GetID() const;
                inline void SetID(uint value);

            protected:
                GameComponent();
                GameComponent(uint id);

            private:
                uint id;

                friend class CloningContext;
                friend class ComponentStreamReader;
        };
    }

#   include <Bibim/GameComponent.inl>

#endif