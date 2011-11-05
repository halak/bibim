#pragma once
#ifndef __BIBIM_GAMEASSET_H__
#define __BIBIM_GAMEASSET_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>

    namespace Bibim
    {
#       define BBAbstractAssetClass(classname, parent)      private: \
                                                                typedef classname This; \
                                                                typedef parent Base;
#       define BBAssetClass(classname, parent, a, b, c, d)  private: \
                                                                typedef classname This; \
                                                                typedef parent Base; \
                                                            public: \
                                                                static const int ClassID = BBMakeFOURCC(a, b, c, d); \
                                                                virtual int GetClassID() const { return ClassID; } \
                                                            private:
#       define BBSerializableAssetClass(classname, parent, a, b, c, d)  BBAssetClass(classname, parent, a, b, c, d); \
                                                                        public: \
                                                                            static GameAsset* Create(AssetStreamReader& reader, GameAsset* existingInstance); \
                                                                        private:

        class GameAsset : public SharedObject
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

#endif