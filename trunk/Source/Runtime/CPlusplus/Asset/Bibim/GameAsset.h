#pragma once
#ifndef __BIBIM_GAMEASSET_H__
#define __BIBIM_GAMEASSET_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>

    extern "C" 
    {
#       include <lua.h>
    }
#   pragma warning(push)
#   pragma warning(disable:4996)
#   pragma warning(disable:4100)
#   include <lua_tinker.h>
#   pragma warning(pop)

    namespace Bibim
    {
#       define BBAbstractAssetClass(classname, parent)      private: \
                                                                typedef classname This; \
                                                                typedef parent Base; \
                                                            protected: \
                                                                virtual void to_lua(lua_State *L) { type2lua(L, this); } \
                                                            private:
#       define BBAssetClass(classname, parent, a, b, c, d)  private: \
                                                                typedef classname This; \
                                                                typedef parent Base; \
                                                            public: \
                                                                static const int ClassID = BBMakeFOURCC(a, b, c, d); \
                                                                virtual int GetClassID() const { return ClassID; } \
                                                            protected: \
                                                                virtual void to_lua(lua_State *L) { type2lua(L, this); } \
                                                            private:
#       define BBSerializableAssetClass(classname, parent, a, b, c, d)  BBAssetClass(classname, parent, a, b, c, d); \
                                                                        public: \
                                                                            static Bibim::GameAsset* Create(Bibim::AssetStreamReader& reader, Bibim::GameAsset* existingInstance); \
                                                                        private:

        class GameAsset : public SharedObject, public lua_tinker::lua_value
        {
            BBAbstractAssetClass(GameAsset, SharedObject);
            BBThisIsNoncopyableClass(GameAsset);
            public:
                typedef AssetStreamReader StreamReader;

            public:
                enum Status
                {
                    EmptyStatus = 0,
                    LoadingStatus = 1,
                    CompletedStatus = 2,
                    FaultStatus = 3,
                };

            public:
                virtual ~GameAsset();

                inline Status GetStatus() const;
                inline int GetRevision() const;

            protected:
                GameAsset(); // call in derived classes, GameAssetStorage

                inline void SetStatus(Status value);
                inline void IncreaseRevision();

            private:
                Status status;
                int revision;

                friend class GameAssetStorage;
        };
    }

#   include <Bibim/GameAsset.inl>

    template<> inline void lua_tinker::push(lua_State* L, Bibim::GameAsset* value)
	{
        push(L, static_cast<lua_tinker::lua_value*>(value));
	}

#endif