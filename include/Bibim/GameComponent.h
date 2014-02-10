#pragma once
#ifndef __BIBIM_GAMECOMPONENT_H__
#define __BIBIM_GAMECOMPONENT_H__

#include <Bibim/FWD.h>
#include <Bibim/SharedObject.h>
#include <Bibim/CloningContext.h>

extern "C" 
{
#   include <lua.h>
#   include <lauxlib.h>
}
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4100)
#include <lua_tinker.h>
#pragma warning(pop)

namespace Bibim
{
#   define BBAbstractComponentClass(classname, parent)     BBAbstractObjectClass(classname, parent) \
                                                           protected: \
                                                               virtual void OnRead(Bibim::ComponentStreamReader& reader); \
                                                               virtual void OnCopy(const Bibim::GameComponent* original, Bibim::CloningContext& context); \
                                                           private:

#   define BBComponentClass(classname, parent, a, b, c, d) BBObjectClass(classname, parent, a, b, c, d) \
                                                           protected: \
                                                               virtual void OnRead(Bibim::ComponentStreamReader& reader); \
                                                               virtual void OnCopy(const Bibim::GameComponent* original, Bibim::CloningContext& context); \
                                                            public: \
                                                                virtual classname* Clone() const; \
                                                            protected: \
                                                                virtual classname* Clone(Bibim::CloningContext& context) const; \
                                                            private:
#   define BBSingletonComponentClass(classname, parent, a, b, c, d) BBComponentClass(classname, parent, a, b, c, d); \
                                                                    public: \
                                                                        static const SharedPointer<classname> Instance; \
                                                                    private: \
                                                                        classname();

#   define BBImplementsComponent(classname) classname* classname::Clone() const \
                                            { \
                                                Bibim::CloningContext context; \
                                                return Clone(context); \
                                            } \
                                            classname* classname::Clone(Bibim::CloningContext& context) const \
                                            { \
                                                classname* clone = new classname(); \
                                                context.Store(this, clone); \
                                                clone->OnCopy(this, context); \
                                                return clone; \
                                            }
#   define BBImplementsSingletonComponent(classname)    classname::classname() { } \
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

    class GameComponent : public SharedObject, public lua_tinker::lua_value
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

BBBindLua(Bibim::GameComponent);

#endif